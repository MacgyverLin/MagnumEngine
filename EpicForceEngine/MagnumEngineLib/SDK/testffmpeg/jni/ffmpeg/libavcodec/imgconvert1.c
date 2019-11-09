/*
 * Misc image conversion routines
 * Copyright (c) 2001, 2002, 2003 Fabrice Bellard.
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file imgconvert1.c
 * misc image conversion routines
 */

/* TODO:
 * - write 'ffimg' program to test all the image related stuff
 * - move all api to slice based system
 * - integrate deinterlacing, postprocessing and scaling in the conversion process
 */

#include "avcodec.h"
#include "dsputil.h"
#include "colorspace.h"
#include "internal.h"
#include "imgconvert.h"
#include "libavutil/pixdesc.h"

#define xglue(x, y) x ## y
#define glue(x, y) xglue(x, y)

#define FF_COLOR_RGB      0 /**< RGB color space */
#define FF_COLOR_GRAY     1 /**< gray color space */
#define FF_COLOR_YUV      2 /**< YUV color space. 16 <= Y <= 235, 16 <= U, V <= 240 */
#define FF_COLOR_YUV_JPEG 3 /**< YUV color space. 0 <= Y <= 255, 0 <= U, V <= 255 */

#define FF_PIXEL_PLANAR   0 /**< each channel has one component in AVPicture */
#define FF_PIXEL_PACKED   1 /**< only one components containing all the channels */
#define FF_PIXEL_PALETTE  2  /**< one components containing indexes for a palette */

typedef struct PixFmtInfo {
    const char *name;
    uint8_t nb_channels;     /**< number of channels (including alpha) */
    uint8_t color_type;      /**< color type (see FF_COLOR_xxx constants) */
    uint8_t pixel_type;      /**< pixel storage type (see FF_PIXEL_xxx constants) */
    uint8_t is_alpha : 1;    /**< true if alpha can be specified */
    uint8_t x_chroma_shift;  /**< X chroma subsampling factor is 2 ^ shift */
    uint8_t y_chroma_shift;  /**< Y chroma subsampling factor is 2 ^ shift */
    uint8_t depth;           /**< bit depth of the color components */
} PixFmtInfo;

/* this table gives more information about formats */
static const PixFmtInfo pix_fmt_info[PIX_FMT_NB] = {
    /* YUV formats */
    [PIX_FMT_YUV420P] = {
        .name = "yuv420p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 1,
    },
    [PIX_FMT_YUV422P] = {
        .name = "yuv422p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUV444P] = {
        .name = "yuv444p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUYV422] = {
        .name = "yuyv422",
        .nb_channels = 1,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 0,
    },
    [PIX_FMT_UYVY422] = {
        .name = "uyvy422",
        .nb_channels = 1,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUV410P] = {
        .name = "yuv410p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 2, .y_chroma_shift = 2,
    },
    [PIX_FMT_YUV411P] = {
        .name = "yuv411p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 2, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUV440P] = {
        .name = "yuv440p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 1,
    },

    /* YUV formats with alpha plane */
    [PIX_FMT_YUVA420P] = {
        .name = "yuva420p",
        .nb_channels = 4,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 1,
    },

    /* JPEG YUV */
    [PIX_FMT_YUVJ420P] = {
        .name = "yuvj420p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV_JPEG,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 1,
    },
    [PIX_FMT_YUVJ422P] = {
        .name = "yuvj422p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV_JPEG,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUVJ444P] = {
        .name = "yuvj444p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV_JPEG,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_YUVJ440P] = {
        .name = "yuvj440p",
        .nb_channels = 3,
        .color_type = FF_COLOR_YUV_JPEG,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 1,
    },

    /* RGB formats */
    [PIX_FMT_RGB24] = {
        .name = "rgb24",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR24] = {
        .name = "bgr24",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB32] = {
        .name = "rgb32",
        .nb_channels = 4, .is_alpha = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB565] = {
        .name = "rgb565",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 5,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB555] = {
        .name = "rgb555",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 5,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },

    /* gray / mono formats */
    [PIX_FMT_GRAY16BE] = {
        .name = "gray16be",
        .nb_channels = 1,
        .color_type = FF_COLOR_GRAY,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 16,
    },
    [PIX_FMT_GRAY16LE] = {
        .name = "gray16le",
        .nb_channels = 1,
        .color_type = FF_COLOR_GRAY,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 16,
    },
    [PIX_FMT_GRAY8] = {
        .name = "gray",
        .nb_channels = 1,
        .color_type = FF_COLOR_GRAY,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
    },
    [PIX_FMT_MONOWHITE] = {
        .name = "monow",
        .nb_channels = 1,
        .color_type = FF_COLOR_GRAY,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 1,
    },
    [PIX_FMT_MONOBLACK] = {
        .name = "monob",
        .nb_channels = 1,
        .color_type = FF_COLOR_GRAY,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 1,
    },

    /* paletted formats */
    [PIX_FMT_PAL8] = {
        .name = "pal8",
        .nb_channels = 4, .is_alpha = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PALETTE,
        .depth = 8,
    },
    [PIX_FMT_XVMC_MPEG2_MC] = {
        .name = "xvmcmc",
    },
    [PIX_FMT_XVMC_MPEG2_IDCT] = {
        .name = "xvmcidct",
    },
    [PIX_FMT_UYYVYY411] = {
        .name = "uyyvyy411",
        .nb_channels = 1,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 2, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR32] = {
        .name = "bgr32",
        .nb_channels = 4, .is_alpha = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR565] = {
        .name = "bgr565",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 5,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR555] = {
        .name = "bgr555",
        .nb_channels = 3,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 5,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB8] = {
        .name = "rgb8",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB4] = {
        .name = "rgb4",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 4,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB4_BYTE] = {
        .name = "rgb4_byte",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR8] = {
        .name = "bgr8",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR4] = {
        .name = "bgr4",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 4,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_BGR4_BYTE] = {
        .name = "bgr4_byte",
        .nb_channels = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_NV12] = {
        .name = "nv12",
        .nb_channels = 2,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 1,
    },
    [PIX_FMT_NV21] = {
        .name = "nv12",
        .nb_channels = 2,
        .color_type = FF_COLOR_YUV,
        .pixel_type = FF_PIXEL_PLANAR,
        .depth = 8,
        .x_chroma_shift = 1, .y_chroma_shift = 1,
    },

    [PIX_FMT_BGR32_1] = {
        .name = "bgr32_1",
        .nb_channels = 4, .is_alpha = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
    [PIX_FMT_RGB32_1] = {
        .name = "rgb32_1",
        .nb_channels = 4, .is_alpha = 1,
        .color_type = FF_COLOR_RGB,
        .pixel_type = FF_PIXEL_PACKED,
        .depth = 8,
        .x_chroma_shift = 0, .y_chroma_shift = 0,
    },
};

/* XXX: totally non optimized */

static void yuyv422_to_yuv420p(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    const uint8_t *p, *p1;
    uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = src->data[0];
    lum1 = dst->data[0];
    cb1 = dst->data[1];
    cr1 = dst->data[2];

    for(;height >= 1; height -= 2) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            lum[0] = p[0];
            cb[0] = p[1];
            lum[1] = p[2];
            cr[0] = p[3];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        if (w) {
            lum[0] = p[0];
            cb[0] = p[1];
            cr[0] = p[3];
            cb++;
            cr++;
        }
        p1 += src->linesize[0];
        lum1 += dst->linesize[0];
        if (height>1) {
            p = p1;
            lum = lum1;
            for(w = width; w >= 2; w -= 2) {
                lum[0] = p[0];
                lum[1] = p[2];
                p += 4;
                lum += 2;
            }
            if (w) {
                lum[0] = p[0];
            }
            p1 += src->linesize[0];
            lum1 += dst->linesize[0];
        }
        cb1 += dst->linesize[1];
        cr1 += dst->linesize[2];
    }
}

static void uyvy422_to_yuv420p(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    const uint8_t *p, *p1;
    uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = src->data[0];

    lum1 = dst->data[0];
    cb1 = dst->data[1];
    cr1 = dst->data[2];

    for(;height >= 1; height -= 2) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            lum[0] = p[1];
            cb[0] = p[0];
            lum[1] = p[3];
            cr[0] = p[2];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        if (w) {
            lum[0] = p[1];
            cb[0] = p[0];
            cr[0] = p[2];
            cb++;
            cr++;
        }
        p1 += src->linesize[0];
        lum1 += dst->linesize[0];
        if (height>1) {
            p = p1;
            lum = lum1;
            for(w = width; w >= 2; w -= 2) {
                lum[0] = p[1];
                lum[1] = p[3];
                p += 4;
                lum += 2;
            }
            if (w) {
                lum[0] = p[1];
            }
            p1 += src->linesize[0];
            lum1 += dst->linesize[0];
        }
        cb1 += dst->linesize[1];
        cr1 += dst->linesize[2];
    }
}


static void uyvy422_to_yuv422p(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    const uint8_t *p, *p1;
    uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = src->data[0];
    lum1 = dst->data[0];
    cb1 = dst->data[1];
    cr1 = dst->data[2];
    for(;height > 0; height--) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            lum[0] = p[1];
            cb[0] = p[0];
            lum[1] = p[3];
            cr[0] = p[2];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        p1 += src->linesize[0];
        lum1 += dst->linesize[0];
        cb1 += dst->linesize[1];
        cr1 += dst->linesize[2];
    }
}


static void yuyv422_to_yuv422p(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    const uint8_t *p, *p1;
    uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = src->data[0];
    lum1 = dst->data[0];
    cb1 = dst->data[1];
    cr1 = dst->data[2];
    for(;height > 0; height--) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            lum[0] = p[0];
            cb[0] = p[1];
            lum[1] = p[2];
            cr[0] = p[3];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        p1 += src->linesize[0];
        lum1 += dst->linesize[0];
        cb1 += dst->linesize[1];
        cr1 += dst->linesize[2];
    }
}

static void yuv422p_to_yuyv422(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    uint8_t *p, *p1;
    const uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = dst->data[0];
    lum1 = src->data[0];
    cb1 = src->data[1];
    cr1 = src->data[2];
    for(;height > 0; height--) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            p[0] = lum[0];
            p[1] = cb[0];
            p[2] = lum[1];
            p[3] = cr[0];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        p1 += dst->linesize[0];
        lum1 += src->linesize[0];
        cb1 += src->linesize[1];
        cr1 += src->linesize[2];
    }
}

static void yuv422p_to_uyvy422(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    uint8_t *p, *p1;
    const uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = dst->data[0];
    lum1 = src->data[0];
    cb1 = src->data[1];
    cr1 = src->data[2];
    for(;height > 0; height--) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 2; w -= 2) {
            p[1] = lum[0];
            p[0] = cb[0];
            p[3] = lum[1];
            p[2] = cr[0];
            p += 4;
            lum += 2;
            cb++;
            cr++;
        }
        p1 += dst->linesize[0];
        lum1 += src->linesize[0];
        cb1 += src->linesize[1];
        cr1 += src->linesize[2];
    }
}

static void uyyvyy411_to_yuv411p(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    const uint8_t *p, *p1;
    uint8_t *lum, *cr, *cb, *lum1, *cr1, *cb1;
    int w;

    p1 = src->data[0];
    lum1 = dst->data[0];
    cb1 = dst->data[1];
    cr1 = dst->data[2];
    for(;height > 0; height--) {
        p = p1;
        lum = lum1;
        cb = cb1;
        cr = cr1;
        for(w = width; w >= 4; w -= 4) {
            cb[0] = p[0];
            lum[0] = p[1];
            lum[1] = p[2];
            cr[0] = p[3];
            lum[2] = p[4];
            lum[3] = p[5];
            p += 6;
            lum += 4;
            cb++;
            cr++;
        }
        p1 += src->linesize[0];
        lum1 += dst->linesize[0];
        cb1 += dst->linesize[1];
        cr1 += dst->linesize[2];
    }
}


static void yuv420p_to_yuyv422(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int w, h;
    uint8_t *line1, *line2, *linesrc = dst->data[0];
    uint8_t *lum1, *lum2, *lumsrc = src->data[0];
    uint8_t *cb1, *cb2 = src->data[1];
    uint8_t *cr1, *cr2 = src->data[2];

    for(h = height / 2; h--;) {
        line1 = linesrc;
        line2 = linesrc + dst->linesize[0];

        lum1 = lumsrc;
        lum2 = lumsrc + src->linesize[0];

        cb1 = cb2;
        cr1 = cr2;

        for(w = width / 2; w--;) {
                *line1++ = *lum1++; *line2++ = *lum2++;
                *line1++ =          *line2++ = *cb1++;
                *line1++ = *lum1++; *line2++ = *lum2++;
                *line1++ =          *line2++ = *cr1++;
        }

        linesrc += dst->linesize[0] * 2;
        lumsrc += src->linesize[0] * 2;
        cb2 += src->linesize[1];
        cr2 += src->linesize[2];
    }
}

static void yuv420p_to_uyvy422(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int w, h;
    uint8_t *line1, *line2, *linesrc = dst->data[0];
    uint8_t *lum1, *lum2, *lumsrc = src->data[0];
    uint8_t *cb1, *cb2 = src->data[1];
    uint8_t *cr1, *cr2 = src->data[2];

    for(h = height / 2; h--;) {
        line1 = linesrc;
        line2 = linesrc + dst->linesize[0];

        lum1 = lumsrc;
        lum2 = lumsrc + src->linesize[0];

        cb1 = cb2;
        cr1 = cr2;

        for(w = width / 2; w--;) {
                *line1++ =          *line2++ = *cb1++;
                *line1++ = *lum1++; *line2++ = *lum2++;
                *line1++ =          *line2++ = *cr1++;
                *line1++ = *lum1++; *line2++ = *lum2++;
        }

        linesrc += dst->linesize[0] * 2;
        lumsrc += src->linesize[0] * 2;
        cb2 += src->linesize[1];
        cr2 += src->linesize[2];
    }
}

/* XXX: add jpeg quantize code */

#define TRANSP_INDEX (6*6*6)

/* this is maybe slow, but allows for extensions */
static inline unsigned char gif_clut_index(uint8_t r, uint8_t g, uint8_t b)
{
    return (((r) / 47) % 6) * 6 * 6 + (((g) / 47) % 6) * 6 + (((b) / 47) % 6);
}

static void build_rgb_palette(uint8_t *palette, int has_alpha)
{
    uint32_t *pal;
    static const uint8_t pal_value[6] = { 0x00, 0x33, 0x66, 0x99, 0xcc, 0xff };
    int i, r, g, b;

    pal = (uint32_t *)palette;
    i = 0;
    for(r = 0; r < 6; r++) {
        for(g = 0; g < 6; g++) {
            for(b = 0; b < 6; b++) {
                pal[i++] = (0xff << 24) | (pal_value[r] << 16) |
                    (pal_value[g] << 8) | pal_value[b];
            }
        }
    }
    if (has_alpha)
        pal[i++] = 0;
    while (i < 256)
        pal[i++] = 0xff000000;
}

/* copy bit n to bits 0 ... n - 1 */
static inline unsigned int bitcopy_n(unsigned int a, int n)
{
    int mask;
    mask = (1 << n) - 1;
    return (a & (0xff & ~mask)) | ((-((a >> n) & 1)) & mask);
}

/* rgb555 handling */

#define RGB_NAME rgb555

#define RGB_IN(r, g, b, s)\
{\
    unsigned int v = ((const uint16_t *)(s))[0];\
    r = bitcopy_n(v >> (10 - 3), 3);\
    g = bitcopy_n(v >> (5 - 3), 3);\
    b = bitcopy_n(v << 3, 3);\
}


#define RGB_OUT(d, r, g, b)\
{\
    ((uint16_t *)(d))[0] = ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);\
}

#define BPP 2

#include "imgconvert1_template.c"

/* rgb565 handling */

#define RGB_NAME rgb565

#define RGB_IN(r, g, b, s)\
{\
    unsigned int v = ((const uint16_t *)(s))[0];\
    r = bitcopy_n(v >> (11 - 3), 3);\
    g = bitcopy_n(v >> (5 - 2), 2);\
    b = bitcopy_n(v << 3, 3);\
}

#define RGB_OUT(d, r, g, b)\
{\
    ((uint16_t *)(d))[0] = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);\
}

#define BPP 2

#include "imgconvert1_template.c"

/* bgr24 handling */

#define RGB_NAME bgr24

#define RGB_IN(r, g, b, s)\
{\
    b = (s)[0];\
    g = (s)[1];\
    r = (s)[2];\
}

#define RGB_OUT(d, r, g, b)\
{\
    (d)[0] = b;\
    (d)[1] = g;\
    (d)[2] = r;\
}

#define BPP 3

#include "imgconvert1_template.c"

#undef RGB_IN
#undef RGB_OUT
#undef BPP

/* rgb24 handling */

#define RGB_NAME rgb24
#define FMT_RGB24

#define RGB_IN(r, g, b, s)\
{\
    r = (s)[0];\
    g = (s)[1];\
    b = (s)[2];\
}

#define RGB_OUT(d, r, g, b)\
{\
    (d)[0] = r;\
    (d)[1] = g;\
    (d)[2] = b;\
}

#define BPP 3

#include "imgconvert1_template.c"

/* rgb32 handling */

#define RGB_NAME rgb32
#define FMT_RGB32

#define RGB_IN(r, g, b, s)\
{\
    unsigned int v = ((const uint32_t *)(s))[0];\
    r = (v >> 16) & 0xff;\
    g = (v >> 8) & 0xff;\
    b = v & 0xff;\
}

#define RGBA_IN(r, g, b, a, s)\
{\
    unsigned int v = ((const uint32_t *)(s))[0];\
    a = (v >> 24) & 0xff;\
    r = (v >> 16) & 0xff;\
    g = (v >> 8) & 0xff;\
    b = v & 0xff;\
}

#define RGBA_OUT(d, r, g, b, a)\
{\
    ((uint32_t *)(d))[0] = (a << 24) | (r << 16) | (g << 8) | b;\
}

#define BPP 4

#include "imgconvert1_template.c"


//===========================================================

static void mono_to_gray(AVPicture *dst, const AVPicture *src,
                         int width, int height, int xor_mask)
{
    const unsigned char *p;
    unsigned char *q;
    int v, dst_wrap, src_wrap;
    int y, w;

    p = src->data[0];
    src_wrap = src->linesize[0] - ((width + 7) >> 3);

    q = dst->data[0];
    dst_wrap = dst->linesize[0] - width;
    for(y=0;y<height;y++) {
        w = width;
        while (w >= 8) {
            v = *p++ ^ xor_mask;
            q[0] = -(v >> 7);
            q[1] = -((v >> 6) & 1);
            q[2] = -((v >> 5) & 1);
            q[3] = -((v >> 4) & 1);
            q[4] = -((v >> 3) & 1);
            q[5] = -((v >> 2) & 1);
            q[6] = -((v >> 1) & 1);
            q[7] = -((v >> 0) & 1);
            w -= 8;
            q += 8;
        }
        if (w > 0) {
            v = *p++ ^ xor_mask;
            do {
                q[0] = -((v >> 7) & 1);
                q++;
                v <<= 1;
            } while (--w);
        }
        p += src_wrap;
        q += dst_wrap;
    }
}

static void monowhite_to_gray(AVPicture *dst, const AVPicture *src,
                               int width, int height)
{
    mono_to_gray(dst, src, width, height, 0xff);
}

static void monoblack_to_gray(AVPicture *dst, const AVPicture *src,
                               int width, int height)
{
    mono_to_gray(dst, src, width, height, 0x00);
}

static void gray_to_mono(AVPicture *dst, const AVPicture *src,
                         int width, int height, int xor_mask)
{
    int n;
    const uint8_t *s;
    uint8_t *d;
    int j, b, v, n1, src_wrap, dst_wrap, y;

    s = src->data[0];
    src_wrap = src->linesize[0] - width;

    d = dst->data[0];
    dst_wrap = dst->linesize[0] - ((width + 7) >> 3);

    for(y=0;y<height;y++) {
        n = width;
        while (n >= 8) {
            v = 0;
            for(j=0;j<8;j++) {
                b = s[0];
                s++;
                v = (v << 1) | (b >> 7);
            }
            d[0] = v ^ xor_mask;
            d++;
            n -= 8;
        }
        if (n > 0) {
            n1 = n;
            v = 0;
            while (n > 0) {
                b = s[0];
                s++;
                v = (v << 1) | (b >> 7);
                n--;
            }
            d[0] = (v << (8 - (n1 & 7))) ^ xor_mask;
            d++;
        }
        s += src_wrap;
        d += dst_wrap;
    }
}

static void gray_to_monowhite(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    gray_to_mono(dst, src, width, height, 0xff);
}

static void gray_to_monoblack(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    gray_to_mono(dst, src, width, height, 0x00);
}

static void gray_to_gray16(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int x, y, src_wrap, dst_wrap;
    uint8_t *s, *d;
    s = src->data[0];
    src_wrap = src->linesize[0] - width;
    d = dst->data[0];
    dst_wrap = dst->linesize[0] - width * 2;
    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            *d++ = *s;
            *d++ = *s++;
        }
        s += src_wrap;
        d += dst_wrap;
    }
}

static void gray16_to_gray(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int x, y, src_wrap, dst_wrap;
    uint8_t *s, *d;
    s = src->data[0];
    src_wrap = src->linesize[0] - width * 2;
    d = dst->data[0];
    dst_wrap = dst->linesize[0] - width;
    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            *d++ = *s;
            s += 2;
        }
        s += src_wrap;
        d += dst_wrap;
    }
}

static void gray16be_to_gray(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    gray16_to_gray(dst, src, width, height);
}

static void gray16le_to_gray(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    AVPicture tmpsrc = *src;
    tmpsrc.data[0]++;
    gray16_to_gray(dst, &tmpsrc, width, height);
}

static void gray16_to_gray16(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int x, y, src_wrap, dst_wrap;
    uint16_t *s, *d;
    s = (uint16_t*)src->data[0];
    src_wrap = (src->linesize[0] - width * 2)/2;
    d = (uint16_t*)dst->data[0];
    dst_wrap = (dst->linesize[0] - width * 2)/2;
    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            *d++ = bswap_16(*s++);
        }
        s += src_wrap;
        d += dst_wrap;
    }
}


typedef struct ConvertEntry {
    void (*convert)(AVPicture *dst,
                    const AVPicture *src, int width, int height);
} ConvertEntry;

/* Add each new conversion function in this table. In order to be able
   to convert from any format to any format, the following constraints
   must be satisfied:

   - all FF_COLOR_RGB formats must convert to and from PIX_FMT_RGB24

   - all FF_COLOR_GRAY formats must convert to and from PIX_FMT_GRAY8

   - all FF_COLOR_RGB formats with alpha must convert to and from PIX_FMT_RGB32

   - PIX_FMT_YUV444P and PIX_FMT_YUVJ444P must convert to and from
     PIX_FMT_RGB24.

   - PIX_FMT_422 must convert to and from PIX_FMT_422P.

   The other conversion functions are just optimizations for common cases.
*/
static const ConvertEntry convert_table[PIX_FMT_NB][PIX_FMT_NB] = {
    [PIX_FMT_YUV420P] = {
        [PIX_FMT_YUYV422] = {
            .convert = yuv420p_to_yuyv422,
        },
        [PIX_FMT_RGB555] = {
            .convert = yuv420p_to_rgb555
        },
        [PIX_FMT_RGB565] = {
            .convert = yuv420p_to_rgb565
        },
        [PIX_FMT_BGR24] = {
            .convert = yuv420p_to_bgr24
        },
        [PIX_FMT_RGB24] = {
            .convert = yuv420p_to_rgb24
        },
        [PIX_FMT_RGB32] = {
            .convert = yuv420p_to_rgb32
        },
        [PIX_FMT_UYVY422] = {
            .convert = yuv420p_to_uyvy422,
        },
    },
    [PIX_FMT_YUV422P] = {
        [PIX_FMT_YUYV422] = {
            .convert = yuv422p_to_yuyv422,
        },
        [PIX_FMT_UYVY422] = {
            .convert = yuv422p_to_uyvy422,
        },
    },
    [PIX_FMT_YUV444P] = {
        [PIX_FMT_RGB24] = {
            .convert = yuv444p_to_rgb24
        },
    },
    [PIX_FMT_YUVJ420P] = {
        [PIX_FMT_RGB555] = {
            .convert = yuvj420p_to_rgb555
        },
        [PIX_FMT_RGB565] = {
            .convert = yuvj420p_to_rgb565
        },
        [PIX_FMT_BGR24] = {
            .convert = yuvj420p_to_bgr24
        },
        [PIX_FMT_RGB24] = {
            .convert = yuvj420p_to_rgb24
        },
        [PIX_FMT_RGB32] = {
            .convert = yuvj420p_to_rgb32
        },
    },
    [PIX_FMT_YUVJ444P] = {
        [PIX_FMT_RGB24] = {
            .convert = yuvj444p_to_rgb24
        },
    },
    [PIX_FMT_YUYV422] = {
        [PIX_FMT_YUV420P] = {
            .convert = yuyv422_to_yuv420p,
        },
        [PIX_FMT_YUV422P] = {
            .convert = yuyv422_to_yuv422p,
        },
    },
    [PIX_FMT_UYVY422] = {
        [PIX_FMT_YUV420P] = {
            .convert = uyvy422_to_yuv420p,
        },
        [PIX_FMT_YUV422P] = {
            .convert = uyvy422_to_yuv422p,
        },
    },
    [PIX_FMT_RGB24] = {
        [PIX_FMT_YUV420P] = {
            .convert = rgb24_to_yuv420p
        },
        [PIX_FMT_RGB565] = {
            .convert = rgb24_to_rgb565
        },
        [PIX_FMT_RGB555] = {
            .convert = rgb24_to_rgb555
        },
        [PIX_FMT_RGB32] = {
            .convert = rgb24_to_rgb32
        },
        [PIX_FMT_BGR24] = {
            .convert = rgb24_to_bgr24
        },
        [PIX_FMT_GRAY8] = {
            .convert = rgb24_to_gray
        },
        [PIX_FMT_PAL8] = {
            .convert = rgb24_to_pal8
        },
        [PIX_FMT_YUV444P] = {
            .convert = rgb24_to_yuv444p
        },
        [PIX_FMT_YUVJ420P] = {
            .convert = rgb24_to_yuvj420p
        },
        [PIX_FMT_YUVJ444P] = {
            .convert = rgb24_to_yuvj444p
        },
    },
    [PIX_FMT_RGB32] = {
        [PIX_FMT_RGB24] = {
            .convert = rgb32_to_rgb24
        },
        [PIX_FMT_BGR24] = {
            .convert = rgb32_to_bgr24
        },
        [PIX_FMT_RGB565] = {
            .convert = rgb32_to_rgb565
        },
        [PIX_FMT_RGB555] = {
            .convert = rgb32_to_rgb555
        },
        [PIX_FMT_PAL8] = {
            .convert = rgb32_to_pal8
        },
        [PIX_FMT_YUV420P] = {
            .convert = rgb32_to_yuv420p
        },
        [PIX_FMT_GRAY8] = {
            .convert = rgb32_to_gray
        },
    },
    [PIX_FMT_BGR24] = {
        [PIX_FMT_RGB32] = {
            .convert = bgr24_to_rgb32
        },
        [PIX_FMT_RGB24] = {
            .convert = bgr24_to_rgb24
        },
        [PIX_FMT_YUV420P] = {
            .convert = bgr24_to_yuv420p
        },
        [PIX_FMT_GRAY8] = {
            .convert = bgr24_to_gray
        },
    },
    [PIX_FMT_RGB555] = {
        [PIX_FMT_RGB24] = {
            .convert = rgb555_to_rgb24
        },
        [PIX_FMT_RGB32] = {
            .convert = rgb555_to_rgb32
        },
        [PIX_FMT_YUV420P] = {
            .convert = rgb555_to_yuv420p
        },
        [PIX_FMT_GRAY8] = {
            .convert = rgb555_to_gray
        },
    },
    [PIX_FMT_RGB565] = {
        [PIX_FMT_RGB32] = {
            .convert = rgb565_to_rgb32
        },
        [PIX_FMT_RGB24] = {
            .convert = rgb565_to_rgb24
        },
        [PIX_FMT_YUV420P] = {
            .convert = rgb565_to_yuv420p
        },
        [PIX_FMT_GRAY8] = {
            .convert = rgb565_to_gray
        },
    },
    [PIX_FMT_GRAY16BE] = {
        [PIX_FMT_GRAY8] = {
            .convert = gray16be_to_gray
        },
        [PIX_FMT_GRAY16LE] = {
            .convert = gray16_to_gray16
        },
    },
    [PIX_FMT_GRAY16LE] = {
        [PIX_FMT_GRAY8] = {
            .convert = gray16le_to_gray
        },
        [PIX_FMT_GRAY16BE] = {
            .convert = gray16_to_gray16
        },
    },
    [PIX_FMT_GRAY8] = {
        [PIX_FMT_RGB555] = {
            .convert = gray_to_rgb555
        },
        [PIX_FMT_RGB565] = {
            .convert = gray_to_rgb565
        },
        [PIX_FMT_RGB24] = {
            .convert = gray_to_rgb24
        },
        [PIX_FMT_BGR24] = {
            .convert = gray_to_bgr24
        },
        [PIX_FMT_RGB32] = {
            .convert = gray_to_rgb32
        },
        [PIX_FMT_MONOWHITE] = {
            .convert = gray_to_monowhite
        },
        [PIX_FMT_MONOBLACK] = {
            .convert = gray_to_monoblack
        },
        [PIX_FMT_GRAY16LE] = {
            .convert = gray_to_gray16
        },
        [PIX_FMT_GRAY16BE] = {
            .convert = gray_to_gray16
        },
    },
    [PIX_FMT_MONOWHITE] = {
        [PIX_FMT_GRAY8] = {
            .convert = monowhite_to_gray
        },
    },
    [PIX_FMT_MONOBLACK] = {
        [PIX_FMT_GRAY8] = {
            .convert = monoblack_to_gray
        },
    },
    [PIX_FMT_PAL8] = {
        [PIX_FMT_RGB555] = {
            .convert = pal8_to_rgb555
        },
        [PIX_FMT_RGB565] = {
            .convert = pal8_to_rgb565
        },
        [PIX_FMT_BGR24] = {
            .convert = pal8_to_bgr24
        },
        [PIX_FMT_RGB24] = {
            .convert = pal8_to_rgb24
        },
        [PIX_FMT_RGB32] = {
            .convert = pal8_to_rgb32
        },
    },
    [PIX_FMT_UYYVYY411] = {
        [PIX_FMT_YUV411P] = {
            .convert = uyyvyy411_to_yuv411p,
        },
    },

};

/* return true if yuv planar */
static inline int is_yuv_planar(const PixFmtInfo *ps)
{
    return (ps->color_type == FF_COLOR_YUV ||
            ps->color_type == FF_COLOR_YUV_JPEG) &&
        ps->pixel_type == FF_PIXEL_PLANAR;
}

static uint8_t y_ccir_to_jpeg[256];
static uint8_t y_jpeg_to_ccir[256];
static uint8_t c_ccir_to_jpeg[256];
static uint8_t c_jpeg_to_ccir[256];

/* init various conversion tables */
static void img_convert_init(void)
{
    int i;
    uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;

    for(i=0;i<256;i++) ff_cropTbl[i + MAX_NEG_CROP] = i;
    for(i=0;i<MAX_NEG_CROP;i++) {
        ff_cropTbl[i] = 0;
        ff_cropTbl[i + MAX_NEG_CROP + 256] = 255;
    }


    for(i = 0;i < 256; i++) {
        y_ccir_to_jpeg[i] = Y_CCIR_TO_JPEG(i);
        y_jpeg_to_ccir[i] = Y_JPEG_TO_CCIR(i);
        c_ccir_to_jpeg[i] = C_CCIR_TO_JPEG(i);
        c_jpeg_to_ccir[i] = C_JPEG_TO_CCIR(i);
    }
}

/* apply to each pixel the given table */
static void img_apply_table(uint8_t *dst, int dst_wrap,
                            const uint8_t *src, int src_wrap,
                            int width, int height, const uint8_t *table1)
{
    int n;
    const uint8_t *s;
    uint8_t *d;
    const uint8_t *table;

    table = table1;
    for(;height > 0; height--) {
        s = src;
        d = dst;
        n = width;
        while (n >= 4) {
            d[0] = table[s[0]];
            d[1] = table[s[1]];
            d[2] = table[s[2]];
            d[3] = table[s[3]];
            d += 4;
            s += 4;
            n -= 4;
        }
        while (n > 0) {
            d[0] = table[s[0]];
            d++;
            s++;
            n--;
        }
        dst += dst_wrap;
        src += src_wrap;
    }
}

/* XXX: use generic filter ? */
/* XXX: in most cases, the sampling position is incorrect */

/* 4x1 -> 1x1 */
static void shrink41(uint8_t *dst, int dst_wrap,
                     const uint8_t *src, int src_wrap,
                     int width, int height)
{
    int w;
    const uint8_t *s;
    uint8_t *d;

    for(;height > 0; height--) {
        s = src;
        d = dst;
        for(w = width;w > 0; w--) {
            d[0] = (s[0] + s[1] + s[2] + s[3] + 2) >> 2;
            s += 4;
            d++;
        }
        src += src_wrap;
        dst += dst_wrap;
    }
}

/* 2x1 -> 1x1 */
static void shrink21(uint8_t *dst, int dst_wrap,
                     const uint8_t *src, int src_wrap,
                     int width, int height)
{
    int w;
    const uint8_t *s;
    uint8_t *d;

    for(;height > 0; height--) {
        s = src;
        d = dst;
        for(w = width;w > 0; w--) {
            d[0] = (s[0] + s[1]) >> 1;
            s += 2;
            d++;
        }
        src += src_wrap;
        dst += dst_wrap;
    }
}

/* 1x2 -> 1x1 */
static void shrink12(uint8_t *dst, int dst_wrap,
                     const uint8_t *src, int src_wrap,
                     int width, int height)
{
    int w;
    uint8_t *d;
    const uint8_t *s1, *s2;

    for(;height > 0; height--) {
        s1 = src;
        s2 = s1 + src_wrap;
        d = dst;
        for(w = width;w >= 4; w-=4) {
            d[0] = (s1[0] + s2[0]) >> 1;
            d[1] = (s1[1] + s2[1]) >> 1;
            d[2] = (s1[2] + s2[2]) >> 1;
            d[3] = (s1[3] + s2[3]) >> 1;
            s1 += 4;
            s2 += 4;
            d += 4;
        }
        for(;w > 0; w--) {
            d[0] = (s1[0] + s2[0]) >> 1;
            s1++;
            s2++;
            d++;
        }
        src += 2 * src_wrap;
        dst += dst_wrap;
    }
}

static void grow21_line(uint8_t *dst, const uint8_t *src,
                        int width)
{
    int w;
    const uint8_t *s1;
    uint8_t *d;

    s1 = src;
    d = dst;
    for(w = width;w >= 4; w-=4) {
        d[1] = d[0] = s1[0];
        d[3] = d[2] = s1[1];
        s1 += 2;
        d += 4;
    }
    for(;w >= 2; w -= 2) {
        d[1] = d[0] = s1[0];
        s1 ++;
        d += 2;
    }
    /* only needed if width is not a multiple of two */
    /* XXX: veryfy that */
    if (w) {
        d[0] = s1[0];
    }
}

static void grow41_line(uint8_t *dst, const uint8_t *src,
                        int width)
{
    int w, v;
    const uint8_t *s1;
    uint8_t *d;

    s1 = src;
    d = dst;
    for(w = width;w >= 4; w-=4) {
        v = s1[0];
        d[0] = v;
        d[1] = v;
        d[2] = v;
        d[3] = v;
        s1 ++;
        d += 4;
    }
}

/* 1x1 -> 2x1 */
static void grow21(uint8_t *dst, int dst_wrap,
                   const uint8_t *src, int src_wrap,
                   int width, int height)
{
    for(;height > 0; height--) {
        grow21_line(dst, src, width);
        src += src_wrap;
        dst += dst_wrap;
    }
}

/* 1x1 -> 1x2 */
static void grow12(uint8_t *dst, int dst_wrap,
                   const uint8_t *src, int src_wrap,
                   int width, int height)
{
    for(;height > 0; height-=2) {
        memcpy(dst, src, width);
        dst += dst_wrap;
        memcpy(dst, src, width);
        dst += dst_wrap;
        src += src_wrap;
    }
}

/* 1x1 -> 2x2 */
static void grow22(uint8_t *dst, int dst_wrap,
                   const uint8_t *src, int src_wrap,
                   int width, int height)
{
    for(;height > 0; height--) {
        grow21_line(dst, src, width);
        if (height%2)
            src += src_wrap;
        dst += dst_wrap;
    }
}

/* 1x1 -> 4x1 */
static void grow41(uint8_t *dst, int dst_wrap,
                   const uint8_t *src, int src_wrap,
                   int width, int height)
{
    for(;height > 0; height--) {
        grow41_line(dst, src, width);
        src += src_wrap;
        dst += dst_wrap;
    }
}

/* 1x1 -> 4x4 */
static void grow44(uint8_t *dst, int dst_wrap,
                   const uint8_t *src, int src_wrap,
                   int width, int height)
{
    for(;height > 0; height--) {
        grow41_line(dst, src, width);
        if ((height & 3) == 1)
            src += src_wrap;
        dst += dst_wrap;
    }
}

/* 1x2 -> 2x1 */
static void conv411(uint8_t *dst, int dst_wrap,
                    const uint8_t *src, int src_wrap,
                    int width, int height)
{
    int w, c;
    const uint8_t *s1, *s2;
    uint8_t *d;

    width>>=1;

    for(;height > 0; height--) {
        s1 = src;
        s2 = src + src_wrap;
        d = dst;
        for(w = width;w > 0; w--) {
            c = (s1[0] + s2[0]) >> 1;
            d[0] = c;
            d[1] = c;
            s1++;
            s2++;
            d += 2;
        }
        src += src_wrap * 2;
        dst += dst_wrap;
    }
}

/* XXX: always use linesize. Return -1 if not supported */
int img_convert(AVPicture *dst, int dst_pix_fmt,
                const AVPicture *src, int src_pix_fmt,
                int src_width, int src_height)
{
    static int initialized;
    int i, ret, dst_width, dst_height, int_pix_fmt;
    const PixFmtInfo *src_pix, *dst_pix;
    const ConvertEntry *ce;
    AVPicture tmp1, *tmp = &tmp1;

    if (src_pix_fmt < 0 || src_pix_fmt >= PIX_FMT_NB ||
        dst_pix_fmt < 0 || dst_pix_fmt >= PIX_FMT_NB)
        return -1;
    if (src_width <= 0 || src_height <= 0)
        return 0;

    if (!initialized) {
        initialized = 1;
        img_convert_init();
    }

    dst_width = src_width;
    dst_height = src_height;

    dst_pix = &pix_fmt_info[dst_pix_fmt];
    src_pix = &pix_fmt_info[src_pix_fmt];
    if (src_pix_fmt == dst_pix_fmt) {
        /* no conversion needed: just copy */
        av_picture_copy(dst, src, dst_pix_fmt, dst_width, dst_height);
        return 0;
    }

    ce = &convert_table[src_pix_fmt][dst_pix_fmt];
    if (ce->convert) {
        /* specific conversion routine */

        ce->convert(dst, src, dst_width, dst_height);
        return 0;
    }


    /* gray to YUV */
    if (is_yuv_planar(dst_pix) &&
        src_pix_fmt == PIX_FMT_GRAY8) {
        int w, h, y;
        uint8_t *d;

        if (dst_pix->color_type == FF_COLOR_YUV_JPEG) {
            ff_img_copy_plane(dst->data[0], dst->linesize[0],
                     src->data[0], src->linesize[0],
                     dst_width, dst_height);
        } else {
            img_apply_table(dst->data[0], dst->linesize[0],
                            src->data[0], src->linesize[0],
                            dst_width, dst_height,
                            y_jpeg_to_ccir);
        }
        /* fill U and V with 128 */
        w = dst_width;
        h = dst_height;
        w >>= dst_pix->x_chroma_shift;
        h >>= dst_pix->y_chroma_shift;
        for(i = 1; i <= 2; i++) {
            d = dst->data[i];
            for(y = 0; y< h; y++) {
                memset(d, 128, w);
                d += dst->linesize[i];
            }
        }
        return 0;
    }

    /* YUV to gray */
    if (is_yuv_planar(src_pix) &&
        dst_pix_fmt == PIX_FMT_GRAY8) {
        if (src_pix->color_type == FF_COLOR_YUV_JPEG) {
            ff_img_copy_plane(dst->data[0], dst->linesize[0],
                     src->data[0], src->linesize[0],
                     dst_width, dst_height);
        } else {
            img_apply_table(dst->data[0], dst->linesize[0],
                            src->data[0], src->linesize[0],
                            dst_width, dst_height,
                            y_ccir_to_jpeg);
        }
        return 0;
    }

    /* YUV to YUV planar */
    if (is_yuv_planar(dst_pix) && is_yuv_planar(src_pix)) {
        int x_shift, y_shift, w, h, xy_shift;
        void (*resize_func)(uint8_t *dst, int dst_wrap,
                            const uint8_t *src, int src_wrap,
                            int width, int height);

        /* compute chroma size of the smallest dimensions */
        w = dst_width;
        h = dst_height;
        if (dst_pix->x_chroma_shift >= src_pix->x_chroma_shift)
            w >>= dst_pix->x_chroma_shift;
        else
            w >>= src_pix->x_chroma_shift;
        if (dst_pix->y_chroma_shift >= src_pix->y_chroma_shift)
            h >>= dst_pix->y_chroma_shift;
        else
            h >>= src_pix->y_chroma_shift;

        x_shift = (dst_pix->x_chroma_shift - src_pix->x_chroma_shift);
        y_shift = (dst_pix->y_chroma_shift - src_pix->y_chroma_shift);
        xy_shift = ((x_shift & 0xf) << 4) | (y_shift & 0xf);
        /* there must be filters for conversion at least from and to
           YUV444 format */
        switch(xy_shift) {
        case 0x00:
            resize_func = ff_img_copy_plane;
            break;
        case 0x10:
            resize_func = shrink21;
            break;
        case 0x20:
            resize_func = shrink41;
            break;
        case 0x01:
            resize_func = shrink12;
            break;
        case 0x11:
            resize_func = ff_shrink22;
            break;
        case 0x22:
            resize_func = ff_shrink44;
            break;
        case 0xf0:
            resize_func = grow21;
            break;
        case 0x0f:
            resize_func = grow12;
            break;
        case 0xe0:
            resize_func = grow41;
            break;
        case 0xff:
            resize_func = grow22;
            break;
        case 0xee:
            resize_func = grow44;
            break;
        case 0xf1:
            resize_func = conv411;
            break;
        default:
            /* currently not handled */
            goto no_chroma_filter;
        }

        ff_img_copy_plane(dst->data[0], dst->linesize[0],
                       src->data[0], src->linesize[0],
                       dst_width, dst_height);

        for(i = 1;i <= 2; i++)
            resize_func(dst->data[i], dst->linesize[i],
                        src->data[i], src->linesize[i],
                        dst_width>>dst_pix->x_chroma_shift, dst_height>>dst_pix->y_chroma_shift);
        /* if yuv color space conversion is needed, we do it here on
           the destination image */
        if (dst_pix->color_type != src_pix->color_type) {
            const uint8_t *y_table, *c_table;
            if (dst_pix->color_type == FF_COLOR_YUV) {
                y_table = y_jpeg_to_ccir;
                c_table = c_jpeg_to_ccir;
            } else {
                y_table = y_ccir_to_jpeg;
                c_table = c_ccir_to_jpeg;
            }
            img_apply_table(dst->data[0], dst->linesize[0],
                            dst->data[0], dst->linesize[0],
                            dst_width, dst_height,
                            y_table);

            for(i = 1;i <= 2; i++)
                img_apply_table(dst->data[i], dst->linesize[i],
                                dst->data[i], dst->linesize[i],
                                dst_width>>dst_pix->x_chroma_shift,
                                dst_height>>dst_pix->y_chroma_shift,
                                c_table);
        }
        return 0;
    }
 no_chroma_filter:

    /* try to use an intermediate format */
    if (src_pix_fmt == PIX_FMT_YUYV422 ||
        dst_pix_fmt == PIX_FMT_YUYV422) {
        /* specific case: convert to YUV422P first */
        int_pix_fmt = PIX_FMT_YUV422P;
    } else if (src_pix_fmt == PIX_FMT_UYVY422 ||
        dst_pix_fmt == PIX_FMT_UYVY422) {
        /* specific case: convert to YUV422P first */
        int_pix_fmt = PIX_FMT_YUV422P;
    } else if (src_pix_fmt == PIX_FMT_UYYVYY411 ||
        dst_pix_fmt == PIX_FMT_UYYVYY411) {
        /* specific case: convert to YUV411P first */
        int_pix_fmt = PIX_FMT_YUV411P;
    } else if ((src_pix->color_type == FF_COLOR_GRAY &&
                src_pix_fmt != PIX_FMT_GRAY8) ||
               (dst_pix->color_type == FF_COLOR_GRAY &&
                dst_pix_fmt != PIX_FMT_GRAY8)) {
        /* gray8 is the normalized format */
        int_pix_fmt = PIX_FMT_GRAY8;
    } else if ((is_yuv_planar(src_pix) &&
                src_pix_fmt != PIX_FMT_YUV444P &&
                src_pix_fmt != PIX_FMT_YUVJ444P)) {
        /* yuv444 is the normalized format */
        if (src_pix->color_type == FF_COLOR_YUV_JPEG)
            int_pix_fmt = PIX_FMT_YUVJ444P;
        else
            int_pix_fmt = PIX_FMT_YUV444P;
    } else if ((is_yuv_planar(dst_pix) &&
                dst_pix_fmt != PIX_FMT_YUV444P &&
                dst_pix_fmt != PIX_FMT_YUVJ444P)) {
        /* yuv444 is the normalized format */
        if (dst_pix->color_type == FF_COLOR_YUV_JPEG)
            int_pix_fmt = PIX_FMT_YUVJ444P;
        else
            int_pix_fmt = PIX_FMT_YUV444P;
    } else {
        /* the two formats are rgb or gray8 or yuv[j]444p */
        if (src_pix->is_alpha && dst_pix->is_alpha)
            int_pix_fmt = PIX_FMT_RGB32;
        else
            int_pix_fmt = PIX_FMT_RGB24;
    }
    if (src_pix_fmt == int_pix_fmt)
        return -1;
    if (avpicture_alloc(tmp, int_pix_fmt, dst_width, dst_height) < 0)
        return -1;
    ret = -1;
    if (img_convert(tmp, int_pix_fmt,
                    src, src_pix_fmt, src_width, src_height) < 0)
        goto fail1;
    if (img_convert(dst, dst_pix_fmt,
                    tmp, int_pix_fmt, dst_width, dst_height) < 0)
        goto fail1;
    ret = 0;
 fail1:
    avpicture_free(tmp);
    return ret;
}

