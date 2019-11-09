#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

JNIEXPORT jstring JNICALL Java_ffmpeg_test_FFmpegTest_test(JNIEnv *env, jobject obj, jstring what) {
  const jbyte *l_what;
  char  *result;

  // Register all formats and codecs
  av_register_all();

  AVFormatContext *pFormatCtx;
  AVCodecContext *pCodecCtx;

  l_what = (*env)->GetStringUTFChars(env, what, NULL);
  if (l_what == NULL) {
    return NULL; /* OutOfMemoryError already thrown */
  }

  result = malloc(strlen(l_what) + 9);
  if (result == NULL) {
    return NULL;
  }
  sprintf(result, "FFmpeg: %s", l_what);

  return (*env)->NewStringUTF(env, result);
}