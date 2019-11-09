#include "GXContext.h"
#include "gldef.h"

GXContext::Quad::Quad()
{
}

GXContext::Quad::~Quad()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *flatVS =
"attribute vec3 inputPosition;\
varying vec4 varyingColor0;\
\
uniform mat4 worldTransform;\
uniform mat4 viewTransform;\
uniform mat4 projTransform;\
uniform vec4 color;\
\
void main()\
{\
	gl_Position			= vec4(inputPosition, 1.00000) * worldTransform * viewTransform * projTransform;\
	varyingColor0		= color;\
}";

const char *flatPS =
"varying vec4 varyingColor0;\
\
void main()\
{\
	gl_FragData[0]		= varyingColor0;\
}";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *flatTexVS =
"attribute vec3 inputPosition;\
attribute vec2 inputTexCoord0;\
varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform mat4 worldTransform;\
uniform mat4 viewTransform;\
uniform mat4 projTransform;\
uniform vec4 color;\
\
void main()\
{\
	gl_Position			= vec4(inputPosition, 1.00000) * worldTransform * viewTransform * projTransform;\
	varyingColor0		= color;\
	varyingTexCoord0	= inputTexCoord0;\
}";

const char *flatTexPS =
"varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform sampler2D diffuseMapSampler; \
\
void main()\
{\
	vec4 diffuseColor	= texture2D(diffuseMapSampler, varyingTexCoord0);\
	gl_FragData[0]		= vec4( varyingColor0.rgb * diffuseColor.rgb, 1.00000); \
}";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *smoothVS =
"attribute vec3 inputPosition;\
attribute vec4 inputColor;\
varying vec4 varyingColor0;\
\
uniform mat4 worldTransform;\
uniform mat4 viewTransform;\
uniform mat4 projTransform;\
\
void main()\
{\
	gl_Position			= vec4(inputPosition, 1.00000) * worldTransform * viewTransform * projTransform;\
	varyingColor0		= inputColor;\
}";

const char *smoothPS =
"varying vec4 varyingColor0;\
\
void main()\
{\
	gl_FragData[0]		= varyingColor0;\
}";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *smoothTexVS =
"attribute vec3 inputPosition;\
attribute vec4 inputColor;\
attribute vec2 inputTexCoord0;\
varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform mat4 worldTransform;\
uniform mat4 viewTransform;\
uniform mat4 projTransform;\
\
void main()\
{\
	gl_Position			= vec4(inputPosition, 1.00000) * worldTransform * viewTransform * projTransform;\
	varyingColor0		= inputColor;\
	varyingTexCoord0	= inputTexCoord0;\
}";

const char *smoothTexPS =
"varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform sampler2D diffuseMapSampler; \
\
void main()\
{\
	vec4 diffuseColor	= texture2D(diffuseMapSampler, varyingTexCoord0);\
	gl_FragData[0]		= vec4( varyingColor0.rgb * diffuseColor.rgb, 1.00000); \
}";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *quadVS =
"attribute vec3 inputPosition;\
attribute vec4 inputColor;\
attribute vec2 inputTexCoord0;\
varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform mat4 worldTransform;\
uniform mat4 viewTransform;\
uniform mat4 projTransform;\
\
void main()\
{\
	gl_Position			= vec4(inputPosition, 1.00000) * worldTransform * viewTransform * projTransform;\
	varyingColor0		= inputColor;\
	varyingTexCoord0	= inputTexCoord0;\
}";

const char *quadPS =
"varying vec4 varyingColor0;\
varying vec2 varyingTexCoord0;\
\
uniform sampler2D diffuseMapSampler; \
\
void main()\
{\
	vec4 diffuseColor	= texture2D(diffuseMapSampler, varyingTexCoord0);\
	gl_FragData[0]		= vec4(varyingColor0.rgba * diffuseColor.rgba); \
}";

GXContext::GXContext(int width_, int height_,
					 GXPixelFormat colorFormat_, 
					 GXPixelFormat depthFormat_, 
					 GXMultiSampleMode multiSampleMode_)
: shaderProgram(0)
, vertexBuffers(NUM_VERTEXBUFFERS)
, indexBuffers(NUM_INDEXBUFFERS)
, textures(NUM_TEXTURES)
, frameBuffer(0)
, screen(0)
, notifyUpdateBits(0)
, blendStateAlpha(GXBlendMode::Add, GXBlendFactor::One, GXBlendFactor::Zero)
, blendStateRgb(GXBlendMode::Add, GXBlendFactor::SrcAlpha, GXBlendFactor::OneMinusSrcAlpha)
, clearColor(0, 0, 0, 0)
, clearDepth(1)
, clearStencil(0)
, colorMask(GXColorMask::None)
, cullState(GXCullMode::CW)
, depthTestState(GXDepthTestMode::LEqual, true)
, depthRange(0, 1)
, enableMode(GXEnableMode::Dither)
, lineWidth(1)
, polygonOffsetState(0, 0)
, scissor(0, 0, width_, height_)
, stencilTestStateFront(GXStencilTestMode::Always, 0, 0xffffffff, 0xffffffff)
, stencilOpStateFront(GXStencilOp::Keep, GXStencilOp::Keep, GXStencilOp::Keep)
, stencilTestStateBack(GXStencilTestMode::Always, 0, 0xffffffff, 0xffffffff)
, stencilOpStateBack(GXStencilOp::Keep, GXStencilOp::Keep, GXStencilOp::Keep)
, viewport(0, 0, width_, height_)
, flatShader(0)
, flatTexShader(0)
, smoothShader(0)
, smoothTexShader(0)
, quadShader(0)
{
	/*
		int num = PsmGraphicsContext.Create (width, height, colorFormat, depthFormat, multiSampleMode, out this.handle);
		if (num != 0)
		{
			Error.ThrowNativeException (num);
		}
		PsmGraphicsContext.GetScreenInfo (this.handle, out width, out height, out colorFormat, out depthFormat, out multiSampleMode);
		this.frameBuffer = (this.screen = new FrameBuffer (width, height, colorFormat, depthFormat, multiSampleMode));
		this.caps = new GraphicsCaps (this.handle);
		this.state.Reset (this.Screen);
		GraphicsContext.notifyUpdate |= GraphicsUpdate.Viewport;
		Log.SetToConsole ();
	*/

	for(int i=0; i<NUM_VERTEXBUFFERS; i++)
		vertexBuffers[i] = 0;
	for(int i=0; i<NUM_INDEXBUFFERS; i++)
		indexBuffers[i] = 0;
	
	for(int i=0; i<NUM_TEXTURES; i++)
		textures[i] = 0;
	frameBuffer		= 0;
	screen			= 0;

	frameBuffer = (screen = new GXFrameBuffer(width_, height_, colorFormat_, depthFormat_, multiSampleMode_));
	// this.caps = new GraphicsCaps (this.handle);
	// this.state.Reset (this.Screen);
	notifyUpdateBits |= GXContext::Viewport;


	{
		Vector<String> attributeNames;
		attributeNames.push() = "inputPosition";
		flatShader = new GXShaderProgram(flatVS, sizeof(flatVS),
										 flatPS, sizeof(flatPS),
										 attributeNames);
	}

	{
		Vector<String> attributeNames;
		attributeNames.push() = "inputPosition";
		attributeNames.push() = "inputColor";
		smoothShader = new GXShaderProgram(smoothVS, sizeof(smoothVS),
										   smoothPS, sizeof(smoothPS),
										   attributeNames);
	}

	{
		Vector<String> attributeNames;
		attributeNames.push() = "inputPosition";
		attributeNames.push() = "inputTexCoord0";
		flatTexShader = new GXShaderProgram(flatTexVS, sizeof(flatTexVS),
											flatTexPS, sizeof(flatTexPS),
											attributeNames);
	}

	{
		Vector<String> attributeNames;
		attributeNames.push() = "inputPosition";
		attributeNames.push() = "inputTexCoord0";
		attributeNames.push() = "inputColor";
		smoothTexShader = new GXShaderProgram(smoothTexVS, sizeof(smoothTexVS),
											  smoothTexPS, sizeof(smoothTexPS),
											  attributeNames);
	}

	{
		Vector<String> attributeNames;
		attributeNames.push() = "inputPosition";
		attributeNames.push() = "inputTexCoord0";
		attributeNames.push() = "inputColor";
		quadShader = new GXShaderProgram(quadVS, sizeof(quadVS),
									     quadPS, sizeof(quadPS),
										 attributeNames);
	}
}

GXContext::~GXContext()
{
	if(flatShader)
	{
		delete flatShader;
		flatShader = 0;
	}

	if(smoothShader)
	{
		delete smoothShader;
		smoothShader = 0;
	}

	if(flatTexShader)
	{
		delete flatTexShader;
		flatTexShader = 0;
	}

	if(smoothTexShader)
	{
		delete smoothTexShader;
		smoothTexShader = 0;
	}

	if(quadShader)
	{
		delete quadShader;
		quadShader = 0;
	}
}

const GXFrameBuffer *GXContext::getScreen() const
{
	// return this.screen;

	return screen;
}

void GXContext::flush()
{
	checkUpdate();

	glFlush();
}

void GXContext::finish()
{
	checkUpdate();

	glFinish();
}

void GXContext::clear()
{
	clear(GXClearMask::All);
}

void GXContext::clear(GXClearMask mask_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.Clear (this.handle, mask);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();

	glClear(mask_.getValue());
}

// flat primitives
void GXContext::draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			         const Vector3 *vertices_, const ColorRGBA &color_, int count_)
{
	this->setShaderProgram(flatShader);

	int worldTransformIdx = flatShader->getUniformIdx("worldTransform");
	int viewTransformIdx = flatShader->getUniformIdx("viewTransform");
	int projTransformIdx = flatShader->getUniformIdx("projTransform");
	flatShader->setUniformValue(worldTransformIdx, worldTransform_);
	flatShader->setUniformValue(viewTransformIdx, viewTransform_);
	flatShader->setUniformValue(projTransformIdx, projTransform_);
	int colorIdx    = flatShader->getUniformIdx("color");
	flatShader->setUniformValue(colorIdx   , color_);

	checkUpdate();
	
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), &vertices_[0]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), &texcoords_[0]);
	//glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), &colors_[0]);

	glDrawArrays(mode_.getValue(), 0, count_);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); bind old buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); bind old buffer
	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	this->setShaderProgram(0);
}

// flat texture primitives
void GXContext::draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			         const Vector3 *vertices_, const ColorRGBA &color_, const Vector2 *texcoords_, int count_)
{
	this->setShaderProgram(flatTexShader);

	int worldTransformIdx = flatTexShader->getUniformIdx("worldTransform");
	int viewTransformIdx = flatTexShader->getUniformIdx("viewTransform");
	int projTransformIdx = flatTexShader->getUniformIdx("projTransform");
	flatTexShader->setUniformValue(worldTransformIdx, worldTransform_);
	flatTexShader->setUniformValue(viewTransformIdx, viewTransform_);
	flatTexShader->setUniformValue(projTransformIdx, projTransform_);
	int colorIdx    = flatTexShader->getUniformIdx("color");
	flatTexShader->setUniformValue(colorIdx   , color_);

	checkUpdate();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), &vertices_[0]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), &texcoords_[0]);
	//glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), &colors_[0]);

	glDrawArrays(mode_.getValue(), 0, count_);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); bind old buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); bind old buffer
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	this->setShaderProgram(0);
}

// gourand primitives
void GXContext::draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			         const Vector3 *vertices_, const ColorRGBA *colors_, int count_)
{
	this->setShaderProgram(smoothShader);

	int worldTransformIdx = smoothShader->getUniformIdx("worldTransform");
	int viewTransformIdx = smoothShader->getUniformIdx("viewTransform");
	int projTransformIdx = smoothShader->getUniformIdx("projTransform");
	smoothShader->setUniformValue(worldTransformIdx, worldTransform_);
	smoothShader->setUniformValue(viewTransformIdx, viewTransform_);
	smoothShader->setUniformValue(projTransformIdx, projTransform_);

	checkUpdate();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), &vertices_[0]);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), &texcoords_[0]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), &colors_[0]);

	glDrawArrays(mode_.getValue(), 0, count_);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); bind old buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); bind old buffer
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	this->setShaderProgram(0);
}

// gourand texture primitives
void GXContext::draw(GXDrawMode mode_, const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
			         const Vector3 *vertices_, const ColorRGBA *colors_, const Vector2 *texcoords_, int count_)
{
	this->setShaderProgram(smoothTexShader);

	int worldTransformIdx = smoothTexShader->getUniformIdx("worldTransform");
	int viewTransformIdx = smoothTexShader->getUniformIdx("viewTransform");
	int projTransformIdx = smoothTexShader->getUniformIdx("projTransform");
	smoothTexShader->setUniformValue(worldTransformIdx, worldTransform_);
	smoothTexShader->setUniformValue(viewTransformIdx, viewTransform_);
	smoothTexShader->setUniformValue(projTransformIdx, projTransform_);

	checkUpdate();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), &vertices_[0]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), &texcoords_[0]);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), &colors_[0]);

	glDrawArrays(mode_.getValue(), 0, count_);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); bind old buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); bind old buffer
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	this->setShaderProgram(0);
}

void GXContext::drawQuad(const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
						 const float *vertices_, const ColorRGBA *colors_, const float *texcoords_,
						 int count_)
{
	setShaderProgram(quadShader);

	int worldTransformIdx = quadShader->getUniformIdx("worldTransform");
	int viewTransformIdx = quadShader->getUniformIdx("viewTransform");
	int projTransformIdx = quadShader->getUniformIdx("projTransform");
	quadShader->setUniformValue(worldTransformIdx, worldTransform_);
	quadShader->setUniformValue(viewTransformIdx, viewTransform_);
	quadShader->setUniformValue(projTransformIdx, projTransform_);

	checkUpdate();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), vertices_);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), texcoords_);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), colors_);

	glDrawArrays(GL_TRIANGLES, 0, count_);

	//glBindBuffer(GL_ARRAY_BUFFER, 0); bind old buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); bind old buffer
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GXContext::drawQuad(const Matrix4 &projTransform_, const Matrix4 &viewTransform_, const Matrix4 &worldTransform_, 
						 float xOffset_, float yOffset_, const ColorRGBA &color_,
						 const Quad &quad_)
{
	float w = quad_.width  * 0.5f;
	float h = quad_.height * 0.5f;
	float vertices[] =
	{
		-w + xOffset_, -h + yOffset_, -1,
		 w + xOffset_, -h + yOffset_, -1,
		-w + xOffset_,  h + yOffset_, -1,
		-w + xOffset_,  h + yOffset_, -1,
		 w + xOffset_, -h + yOffset_, -1,
		 w + xOffset_,  h + yOffset_, -1,
	};

	ColorRGBA colors[] =
	{
		color_,
		color_,
		color_,
		color_,
		color_,
		color_
	};

	float texcoords[] =
	{
		quad_.u0,  quad_.v0,
		quad_.u1,  quad_.v0,
		quad_.u0,  quad_.v1,

		quad_.u0,  quad_.v1,
		quad_.u1,  quad_.v0,
		quad_.u1,  quad_.v1
	};

	drawQuad(projTransform_, viewTransform_, worldTransform_, 
			 vertices, colors, texcoords,
			 6);
}

void GXContext::draw(GXDrawMode mode_, int first_, int count_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.DrawArrays (this.handle, mode, first, count, 1);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();

	if(vertexBuffers[0] && vertexBuffers[0]->getVertexCount())
	{
		if(indexBuffers[0] && indexBuffers[0]->getIndexCount())
		{
			glDrawElements(mode_.getValue(), count_, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			glDrawArrays(mode_.getValue(), first_, count_);
		}
	}
}

void GXContext::draw(GXDrawMode mode_, int first_, int count_, int repeat_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.DrawArrays (this.handle, mode, first, count, repeat);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();

	for(int i=0; i<repeat_; i++)
	{
		glDrawArrays(mode_.getValue(), first_, count_);
		first_ += count_;
	}
}

void GXContext::draw(const Vector<GXPrimitive> &primitives_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.DrawArrays2 (this.handle, primitives, 0, -1);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();

	for(int i=0; i<primitives_.length(); i++)
	{
		glDrawArrays(primitives_[i].mode.getValue(), primitives_[i].first, primitives_[i].count);
	}
}

void GXContext::draw(const Vector<GXPrimitive> &primitives_, int first_, int count_)
{
	/*
	this.CheckUpdate ();
	if (count < 0)
	{
		count = 2147483647;
	}
	int num = PsmGraphicsContext.DrawArrays2 (this.handle, primitives, first, count);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	assert(first_+count_ < primitives_.length()	);

	checkUpdate();

	for(int i=first_; i<first_+count_; i++)
	{
		glDrawArrays(primitives_[i].mode.getValue(), primitives_[i].first, primitives_[i].count);
	}
}

void GXContext::readPixels(Vector<unsigned char > &pixels_, GXPixelFormat format_, int sx_, int sy_, int sw_, int sh_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.ReadPixels (this.handle, pixels, format, sx, sy, sw, sh);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();
}

void GXContext::readPixels(GXTexture2D *texture_, int level_, int dx_, int dy_, int sx_, int sy_, int sw_, int sh_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.ReadPixels2 (this.handle, texture.handle, level, TextureCubeFace.PositiveX, dx, dy, sx, sy, sw, sh);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();
}

void GXContext::readPixels(GXTextureCube *texture_, int level_, GXTextureCubeFace cubeFace_, int dx_, int dy_, int sx_, int sy_, int sw_, int sh_)
{
	/*
	this.CheckUpdate ();
	int num = PsmGraphicsContext.ReadPixels2 (this.handle, texture.handle, level, cubeFace, dx, dy, sx, sy, sw, sh);
	if (num != 0)
	{
		Error.ThrowNativeException (num);
	}
	*/
	checkUpdate();
}

const GXShaderProgram *GXContext::getShaderProgram() const
{
	//return this.shaderProgram;

	return shaderProgram;
}

void GXContext::setShaderProgram(GXShaderProgram *program_)
{
	// this.shaderProgram = program;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.ShaderProgram;
	
	if(shaderProgram!=program_)
	{
		shaderProgram = program_;
		notifyUpdateBits |= GXContext::ShaderProgram;
	}
}

const GXVertexBuffer *GXContext::getVertexBuffer(int index_) const
{
	// return this.vertexBuffers [index];

	assert(index_ < NUM_VERTEXBUFFERS);
	return vertexBuffers[index_];
}

void GXContext::setVertexBuffer(int index_, GXVertexBuffer *buffer_)
{
	/*
	this.vertexBuffers [index] = buffer;
	this.handles [4 + index] = ((buffer == null) ? 0 : buffer.handle);
	GraphicsContext.notifyUpdate |= ((index == 0) ? GraphicsUpdate.VertexBuffer0 : GraphicsUpdate.VertexBufferN);
	*/

	assert(index_ < NUM_VERTEXBUFFERS);

	if(vertexBuffers[index_]!=buffer_)
	{
		vertexBuffers[index_]	= buffer_;
		// handles[4 + index]	= ((buffer == null) ? 0 : buffer.handle);
		notifyUpdateBits |= ((index_ == 0) ? GXContext::VertexBuffer0 : GXContext::VertexBufferN);
	}
}

const GXIndexBuffer *GXContext::getIndexBuffer(int index_) const
{
	// return this.indexBuffers [index];

	assert(index_ < NUM_INDEXBUFFERS);
	return indexBuffers[index_];
}

void GXContext::setIndexBuffer(int index_, GXIndexBuffer *buffer_)
{
	/*
	this.indexBuffers [index] = buffer;
	this.handles [4 + index] = ((buffer == null) ? 0 : buffer.handle);
	GraphicsContext.notifyUpdate |= ((index == 0) ? GraphicsUpdate.VertexBuffer0 : GraphicsUpdate.VertexBufferN);
	*/

	assert(index_ < NUM_INDEXBUFFERS);

	if(indexBuffers[index_]!=buffer_)
	{
		indexBuffers[index_]	= buffer_;
		// handles[4 + index]	= ((buffer == null) ? 0 : buffer.handle);
		notifyUpdateBits |= ((index_ == 0) ? GXContext::IndexBuffer0 : GXContext::IndexBufferN);
	}
}

const GXTexture *GXContext::getTexture(int index_)
{
	// return this.textures [index];

	assert(index_ < NUM_TEXTURES);
	return textures[index_];
}

void GXContext::setTexture(int index_, GXTexture *texture_)
{
	/*
	this.textures [index] = texture;
	this.handles [8 + index] = ((texture == null) ? 0 : texture.handle);
	GraphicsContext.notifyUpdate |= ((index == 0) ? GraphicsUpdate.Texture0 : ((GraphicsUpdate)2147483648u));
	*/
	assert(index_ < NUM_TEXTURES);

	if(textures[index_]!=texture_)
	{
		textures[index_] = texture_;
		// this.handles [8 + index] = ((texture == null) ? 0 : texture.handle);
		notifyUpdateBits |= ((index_ == 0) ? GXContext::Texture0 : GXContext::TextureN);
	}
}

GXFrameBuffer *GXContext::getFrameBuffer() const
{
	// return this.frameBuffer;

	return frameBuffer;
}

void GXContext::setFrameBuffer(GXFrameBuffer *buffer_)
{
	/*
	this.frameBuffer = ((buffer != null) ? buffer : this.screen);
	this.handles [1] = this.frameBuffer.handle;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.FrameBuffer;
	*/
	if(buffer_==0)
		buffer_ = screen;

	if(frameBuffer!=buffer_)
	{
		frameBuffer = buffer_;
		// this.handles [1] = this.frameBuffer.handle;
		notifyUpdateBits |= GXContext::FrameBuffer;
	}
}

bool GXContext::isEnabled(GXEnableMode mode_) const
{
	/*
	if ((mode & ~(EnableMode.ScissorTest | EnableMode.CullFace | EnableMode.Blend | EnableMode.DepthTest | EnableMode.PolygonOffsetFill | EnableMode.StencilTest | EnableMode.Dither)) != EnableMode.None)
	{
		throw new ArgumentException ();
	}
	return (mode & this.state.Enable) != EnableMode.None;
	*/
	if( (mode_ & 
		 ~(GXEnableMode::CullFace    | GXEnableMode::ScissorTest | GXEnableMode::Blend       | 
		   GXEnableMode::DepthTest   | GXEnableMode::PolygonOffsetFill | GXEnableMode::StencilTest | 
		   GXEnableMode::Dither)
		 ) != GXEnableMode::None)
	{
		return false;
	}

	return (mode_ & enableMode) != GXEnableMode::None;
}

void GXContext::enable(GXEnableMode mode_, bool status_)
{
	/*
	EnableMode enableMode = this.state.Enable;
	if ((mode & ~(EnableMode.ScissorTest | EnableMode.CullFace | EnableMode.Blend | EnableMode.DepthTest | EnableMode.PolygonOffsetFill | EnableMode.StencilTest | EnableMode.Dither)) != EnableMode.None)
	{
		throw new ArgumentException ();
	}
	enableMode = (status ? (enableMode | mode) : (enableMode & ~mode));
	if (this.state.Enable != enableMode)
	{
		this.state.Enable = enableMode;
		GraphicsContext.notifyUpdate |= GraphicsUpdate.Enable;
	}
	*/
	GXEnableMode enableModeTemp = enableMode;
	if( (mode_ & 
		 ~(GXEnableMode::CullFace    | GXEnableMode::ScissorTest		| GXEnableMode::Blend       | 
		   GXEnableMode::DepthTest   | GXEnableMode::PolygonOffsetFill	| GXEnableMode::StencilTest | 
		   GXEnableMode::Dither)
		 ) != GXEnableMode::None)
	{
		return;
	}

	enableModeTemp = (status_ ? (enableModeTemp | mode_) : (enableModeTemp & ~mode_));
	if(enableMode != enableModeTemp)
	{
		enableMode = enableModeTemp;

		notifyUpdateBits |= GXContext::Enable;
	}
}

void GXContext::enable(GXEnableMode mode_)
{
	// this.Enable (mode, true);

	enable(mode_, true);
}

void GXContext::disable(GXEnableMode mode_)
{
	// this.Enable (mode, false);

	enable(mode_, false);
}

const GXImageRect &GXContext::getScissor() const
{
	// return this.state.Scissor;
	
	return scissor;
}

void GXContext::setScissor(const GXImageRect &scissor_)
{
	// this.state.Scissor = rectangle;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.Scissor;
	if( !(scissor == scissor_) )
	{
		scissor = scissor_;
		notifyUpdateBits |= GXContext::Scissor;
	}
}

void GXContext::setScissor(int x_, int y_, int w_, int h_)
{
	// this.SetScissor (new ImageRect (x, y, w, h));

	setScissor(GXImageRect(x_, y_, w_, h_));
}

const GXImageRect &GXContext::getViewport() const
{
	// return this.state.Viewport;

	return viewport;
}

void GXContext::setViewport(const GXImageRect &viewport_)
{
	/*
	this.state.Viewport = rectangle;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.Viewport;
	*/
	if( !(viewport == viewport_) )
	{
		viewport = viewport_;
		notifyUpdateBits |= GXContext::Viewport;
	}
}

void GXContext::setViewport(int x_, int y_, int w_, int h_)
{
	// this.SetViewport (new ImageRect (x, y, w, h));

	setViewport(GXImageRect(x_, y_, w_, h_));
}

const Vector2 &GXContext::getDepthRange() const
{
	// return this.state.DepthRange;

	return depthRange;
}

void GXContext::setDepthRange(const Vector2 &depthRange_)
{
	/*
	this.state.DepthRange = range;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.DepthRange;
	*/
	if( !(depthRange == depthRange_) )
	{
		depthRange = depthRange_;
		notifyUpdateBits |= GXContext::DepthRange;
	}
}

void GXContext::setDepthRange(float min_, float max_)
{
	// this.SetDepthRange(new Vector2 (min, max));
	
	setDepthRange(Vector2(min_, max_));
}

const Vector4 &GXContext::getClearColor() const
{
	// return this.state.ClearColor;
	
	return clearColor;
}

void GXContext::setClearColor(const Vector4 &clearColor_)
{
	/*
	this.state.ClearColor = color;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.ClearColor;
	*/
	if( !(clearColor == clearColor_) )
	{
		clearColor = clearColor_;
		notifyUpdateBits |= GXContext::ClearColor;
	}
}

void GXContext::setClearColor(float r_, float g_, float b_, float a_)
{
	// this.SetClearColor (new Vector4 (r, g, b, a));
	
	setClearColor(Vector4(r_, g_, b_, a_));
}

void GXContext::setClearColor(int r_, int g_, int b_, int a_)
{
	// this.SetClearColor (new Vector4 ((float)r, (float)g, (float)b, (float)a) * 0.003921569f);

	setClearColor( Vector4(0.003921569f*r_, 0.003921569f*g_, 0.003921569f*b_, 0.003921569f*a_) );
}

float GXContext::getClearDepth() const 
{
	return clearDepth;
}

void GXContext::setClearDepth(float clearDepth_)
{
	/*
	this.state.ClearDepth = depth;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.ClearDepth;
	*/
	if( !(clearDepth == clearDepth_) )
	{
		clearDepth = clearDepth_;
		notifyUpdateBits |= GXContext::ClearDepth;
	}
}

int GXContext::getClearStencil() const
{
	// return this.state.ClearStencil;
	
	return clearStencil;
}

void GXContext::setClearStencil(int clearStencil_)
{
	/*
	this.state.ClearStencil = (int)((byte)stencil);
	GraphicsContext.notifyUpdate |= GraphicsUpdate.ClearStencil;
	*/
	if( !(clearStencil == clearStencil_) )
	{
		clearStencil = clearStencil_;
		notifyUpdateBits |= GXContext::ClearStencil;
	}
}

const GXCullState &GXContext::getCullState() const
{
	return cullState;
}

void GXContext::setCullState(const GXCullState &cullState_)
{
	/*
	this.state.CullFace = face;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.CullFace;
	*/
	if( !(cullState == cullState_) )
	{
		cullState = cullState_;
		notifyUpdateBits |= GXContext::CullFace;
	}
}

void GXContext::setCullState(const GXCullMode &cullMode_)
{
	// this.SetCullFace (new CullFace (mode, direction));

	setCullState(GXCullState(cullMode_));
}

const GXBlendState &GXContext::getBlendState() const
{
	// return this.state.BlendFuncRgb;
	return blendStateRgb;
}

void GXContext::setBlendState(const GXBlendState &blendState_)
{
	/*
	this.state.BlendFuncAlpha = func;
	this.state.BlendFuncRgb = func;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.BlendFunc;
	*/
	setBlendStateRgb(blendState_);
	setBlendStateAlpha(blendState_);
}

void GXContext::setBlendState(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_)
{
	// this.SetBlendFunc (new BlendFunc (mode, srcFactor, dstFactor));

	setBlendState(GXBlendState(mode_, srcFactor_, dstFactor_));
}

const GXBlendState &GXContext::getBlendStateRgb() const
{
	// return this.state.BlendFuncRgb;
	
	return blendStateRgb;
}

void GXContext::setBlendStateRgb(const GXBlendState &blendState_)
{
	// this.state.BlendFuncRgb = func;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.BlendFunc;

	if(!(blendStateRgb==blendState_))
	{
		blendStateRgb = blendState_;

		notifyUpdateBits |= GXContext::BlendFunc;
	}
}

void GXContext::setBlendStateRgb(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_)
{
	// this.SetBlendFuncRgb (new BlendFunc (mode, srcFactor, dstFactor));
	
	setBlendStateRgb(GXBlendState(mode_, srcFactor_, dstFactor_));
}

const GXBlendState &GXContext::getBlendStateAlpha() const
{
	// return this.state.BlendFuncAlpha;
	
	return blendStateAlpha;
}

void GXContext::setBlendStateAlpha(const GXBlendState &blendState_)
{
	// this.state.BlendFuncAlpha = func;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.BlendFunc;
	if(!(blendStateAlpha==blendState_))
	{
		blendStateAlpha = blendState_;

		notifyUpdateBits |= GXContext::BlendFunc;
	}
}

void GXContext::setBlendStateAlpha(const GXBlendMode &mode_, const GXBlendFactor &srcFactor_, const GXBlendFactor &dstFactor_)
{
	// this.SetBlendFuncAlpha (new BlendFunc (mode, srcFactor, dstFactor));

	setBlendStateAlpha(GXBlendState(mode_, srcFactor_, dstFactor_));
}

const GXDepthTestState &GXContext::getDepthTestState() const
{
	// return this.state.DepthFunc;
	return depthTestState;
}

void GXContext::setDepthTestState(const GXDepthTestState &depthTestState_)
{
	//this.state.DepthFunc = func;
	//GraphicsContext.notifyUpdate |= GraphicsUpdate.DepthFunc;
	if(!(depthTestState==depthTestState_))
	{
		depthTestState = depthTestState_;

		notifyUpdateBits |= GXContext::DepthFunc;
	}
}

void GXContext::setDepthTestState(const GXDepthTestMode &mode_, bool writeMask_)
{
	// this.SetDepthFunc (new DepthFunc (mode, writeMask));

	setDepthTestState(GXDepthTestState(mode_, writeMask_));
}

const GXPolygonOffsetState &GXContext::getPolygonOffsetState() const
{
	// return this.state.PolygonOffset;
	
	return polygonOffsetState;
}

void GXContext::setPolygonOffsetState(const GXPolygonOffsetState &polygonOffsetState_)
{
	// this.state.PolygonOffset = offset;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.PolygonOffset;
	if(!(polygonOffsetState==polygonOffsetState_))
	{
		polygonOffsetState = polygonOffsetState_;

		notifyUpdateBits |= GXContext::PolygonOffset;
	}
}

void GXContext::setPolygonOffsetState(float factor_, float units_)
{
	// this.SetPolygonOffset (new PolygonOffset (factor, units));

	setPolygonOffsetState(GXPolygonOffsetState(factor_, units_));
}

const GXStencilTestState &GXContext::getStencilTestState() const
{
	// return this.state.StencilFuncFront;
	return stencilTestStateFront;
}

void GXContext::setStencilTestState(const GXStencilTestState &stencilTestState_)
{
	// this.state.StencilFuncBack = func;
	// this.state.StencilFuncFront = func;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilFunc;

	setStencilTestStateFront(stencilTestState_);
	setStencilTestStateBack(stencilTestState_);
}

void GXContext::setStencilTestState(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_)
{
	// this.SetStencilFunc (new StencilFunc (mode, reference, readMask, writeMask));

	setStencilTestState(GXStencilTestState(mode_, reference_, readMask_, writeMask_));
}

const GXStencilOpState &GXContext::getStencilOpState() const
{
	// return this.state.StencilOpFront;

	return stencilOpStateFront;
}

void GXContext::setStencilOpState(const GXStencilOpState &stencilOpState_)
{
	// this.state.StencilOpBack = op;
	// this.state.StencilOpFront = op;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilOp;
	setStencilOpStateFront(stencilOpState_);
	setStencilOpStateBack(stencilOpState_);
}

void GXContext::setStencilOpState(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_)
{
	// this.SetStencilOp (new StencilOp (fail, zFail, zPass));

	setStencilOpState(GXStencilOpState(failOp_, zFailOp_, zPassOp_));
}

const GXStencilTestState &GXContext::getStencilTestStateFront() const
{
	// return this.state.StencilFuncFront;

	return stencilTestStateFront;
}

void GXContext::setStencilTestStateFront(const GXStencilTestState &stencilTestStateFront_)
{
	/*
	this.state.StencilFuncFront = func;
	GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilFunc;
	*/
	if( !(stencilTestStateFront==stencilTestStateFront_) )
	{
		stencilTestStateFront = stencilTestStateFront_;

		notifyUpdateBits |= GXContext::StencilFunc;
	}
}

void GXContext::setStencilTestStateFront(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_)
{
	// this.SetStencilFuncFront (new StencilFunc (mode, reference, readMask, writeMask));

	setStencilTestStateFront(GXStencilTestState(mode_, reference_, readMask_, writeMask_));
}

const GXStencilOpState &GXContext::getStencilOpStateFront() const
{
	// return this.state.StencilOpFront;
	return stencilOpStateFront;
}

void GXContext::setStencilOpStateFront(const GXStencilOpState &stencilOpStateFront_)
{
	// this.state.StencilOpFront = op;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilOp;
	if( !(stencilOpStateFront==stencilOpStateFront_) )
	{
		stencilOpStateFront = stencilOpStateFront_;

		notifyUpdateBits |= GXContext::StencilOp;
	}
}

void GXContext::setStencilOpStateFront(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_)
{
	// this.SetStencilOpFront (new StencilOp (fail, zFail, zPass));

	setStencilOpStateFront(GXStencilOpState(failOp_, zFailOp_, zPassOp_));
}

const GXStencilTestState &GXContext::getStencilTestStateBack() const
{
	// return this.state.StencilFuncBack;

	return stencilTestStateBack;
}

void GXContext::setStencilTestStateBack(const GXStencilTestState &stencilTestStateBack_)
{
	// this.state.StencilFuncBack = func;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilFunc;
	if( !(stencilTestStateBack==stencilTestStateBack_) )
	{
		stencilTestStateBack = stencilTestStateBack_;

		notifyUpdateBits |= GXContext::StencilFunc;
	}
}

void GXContext::setStencilTestStateBack(const GXStencilTestMode &mode_, unsigned int reference_, unsigned int readMask_, unsigned int writeMask_)
{
	// this.SetStencilFuncBack (new StencilFunc (mode, reference, readMask, writeMask));

	setStencilTestStateBack(GXStencilTestState(mode_, reference_, readMask_, writeMask_));
}

const GXStencilOpState &GXContext::getStencilOpStateBack() const
{
	// return this.state.StencilOpBack;

	return stencilOpStateBack;
}

void GXContext::setStencilOpStateBack(const GXStencilOpState &stencilOpStateBack_)
{
	// this.state.StencilOpBack = op;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.StencilOp;
	if( !(stencilOpStateBack==stencilOpStateBack_) )
	{
		stencilOpStateBack = stencilOpStateBack_;

		notifyUpdateBits |= GXContext::StencilOp;
	}
}

void GXContext::setStencilOpStateBack(const GXStencilOp &failOp_, const GXStencilOp &zFailOp_, const GXStencilOp &zPassOp_)
{
	// this.SetStencilOpBack (new StencilOp (fail, zFail, zPass));

	setStencilOpStateBack( GXStencilOpState(failOp_, zFailOp_, zPassOp_) );
}

const GXColorMask &GXContext::getColorMask() const
{
	// return this.state.ColorMask;

	return colorMask;
}

void GXContext::setColorMask(const GXColorMask &colorMask_)
{
	// this.state.ColorMask = mask;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.ColorMask;
	if( !(colorMask==colorMask_) )
	{
		colorMask = colorMask_;
		notifyUpdateBits |= GXContext::ColorMask;
	}
}

float GXContext::getLineWidth() const
{
	// return this.state.LineWidth;

	return lineWidth;
}

void GXContext::setLineWidth(float lineWidth_)
{
	// this.state.LineWidth = width;
	// GraphicsContext.notifyUpdate |= GraphicsUpdate.LineWidth;
	if( !(lineWidth==lineWidth_) )
	{
		lineWidth = lineWidth_;
		notifyUpdateBits |= GXContext::LineWidth;
	}
}

void GXContext::notifyUpdate(GraphicsUpdate update_)
{
	// GraphicsContext.notifyUpdate |= update;

	notifyUpdateBits |= update_;
}

void GXContext::checkUpdate()
{
	/*
	if (this.shaderProgram != null)
	{
		this.shaderProgram.UpdateShader ();
	}
	if (GraphicsContext.notifyUpdate != GraphicsUpdate.None)
	{
		if ((GraphicsContext.notifyUpdate & GraphicsUpdate.ShaderProgram) != GraphicsUpdate.None)
		{
			this.handles [0] = ((this.shaderProgram == null) ? 0 : this.shaderProgram.handle);
		}
		PsmGraphicsContext.Update (this.handle, GraphicsContext.notifyUpdate, ref this.state, this.handles);
		GraphicsContext.notifyUpdate = GraphicsUpdate.None;
	}
	*/
	if(notifyUpdateBits != GXContext::None) // if have update
	{
		if( (notifyUpdateBits & GXContext::ShaderProgram) != GXContext::None) // if have shader update
		{
			// this.handles [0] = ((this.shaderProgram == 0) ? 0 : this.shaderProgram.handle);
		}
		
		update();
		notifyUpdateBits = GXContext::None;
	}
	if(shaderProgram && shaderProgram->handle)
	{
		shaderProgram->update();
	}
}

void GXContext::update()
{
	checkGLError("GraphicsUpdate::update");

	if(notifyUpdateBits & GXContext::BlendFunc				   )
	{
		GXBlendMode			rgbMode		= blendStateRgb.getMode() ;
		GXBlendFactor	rgbSrcFactor	= blendStateRgb.getSrcFactor();
		GXBlendFactor	rgbDstFactor	= blendStateRgb.getDstFactor();

		GXBlendMode			alphaMode	= blendStateAlpha.getMode() ;
		GXBlendFactor	alphaSrcFactor	= blendStateAlpha.getSrcFactor();
		GXBlendFactor	alphaDstFactor	= blendStateAlpha.getDstFactor();
		
		glBlendEquationSeparate(rgbMode.getValue(), alphaMode.getValue());
		glBlendFuncSeparate(rgbSrcFactor.getValue(), rgbDstFactor.getValue(), alphaSrcFactor.getValue(), alphaDstFactor.getValue());

		checkGLError("GraphicsUpdate::BlendFunc");
	}
	if(notifyUpdateBits & GXContext::ClearColor			   )
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

		checkGLError("GraphicsUpdate::ClearColor");
	}
	if(notifyUpdateBits & GXContext::ClearDepth			   )
	{
#ifdef WIN32
	#ifdef USE_GLES20
			glClearDepthf(clearDepth);
	#else
			glClearDepth(clearDepth);
	#endif		
#elif defined(__ANDROID__ )
		glClearDepthf(clearDepth);
#elif ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )
		glClearDepthf(clearDepth);
#endif

		checkGLError("GraphicsUpdate::ClearDepth");
	}
	if(notifyUpdateBits & GXContext::ClearStencil			   )
	{
		glClearStencil(clearStencil);

		checkGLError("GraphicsUpdate::ClearStencil");
	}
	if(notifyUpdateBits & GXContext::ColorMask				   )
	{
		bool rMask = false;
		bool gMask = false;
		bool bMask = false;
		bool aMask = false;
		if(colorMask & GXColorMask::R)
			rMask = true;
		if(colorMask & GXColorMask::G)
			gMask = true;
		if(colorMask & GXColorMask::B)
			bMask = true;
		if(colorMask & GXColorMask::A)
			aMask = true;
		
		glColorMask(rMask, gMask, bMask, aMask);

		checkGLError("GraphicsUpdate::ColorMask");
	}
	if(notifyUpdateBits & GXContext::CullFace				   )
	{
		const GXCullMode &cullMode = cullState.getMode();

		if(cullMode==GXCullMode::CW)
			glFrontFace(GL_CCW);
		else
			glFrontFace(GL_CW);

		checkGLError("GraphicsUpdate::CullFace");
	}
	if(notifyUpdateBits & GXContext::DepthFunc				   )
	{
		GXDepthTestMode depthFuncMode	= depthTestState.getMode();
		bool writeMask					= depthTestState.getWriteMask();

		glDepthFunc(depthFuncMode.getValue());
		glDepthMask(writeMask);

		checkGLError("GraphicsUpdate::DepthFunc");
	}
	if(notifyUpdateBits & GXContext::DepthRange			   )
	{
		glDepthRangef(depthRange[0], depthRange[1]);

		checkGLError("GraphicsUpdate::DepthRange");
	}
	if(notifyUpdateBits & GXContext::Enable				   )
	{
		if(enableMode & GXEnableMode::ScissorTest)
			glEnable(GL_SCISSOR_TEST);
		else
			glDisable(GL_SCISSOR_TEST);
		if(enableMode & GXEnableMode::CullFace)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
		if(enableMode & GXEnableMode::Blend)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
		if(enableMode & GXEnableMode::DepthTest)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
		if(enableMode & GXEnableMode::PolygonOffsetFill)
			glEnable(GL_POLYGON_OFFSET_FILL);
		else
			glDisable(GL_POLYGON_OFFSET_FILL);
		if(enableMode & GXEnableMode::StencilTest)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);
		if(enableMode & GXEnableMode::Dither)
			glEnable(GL_DITHER);
		else
			glDisable(GL_DITHER);

		checkGLError("GraphicsUpdate::Enable");
	}

	if(notifyUpdateBits & GXContext::FrameBuffer			   )
	{
		checkGLError("GraphicsUpdate::FrameBuffer");
	}
	if(notifyUpdateBits & GXContext::LineWidth				   )
	{
		glLineWidth(lineWidth);

		checkGLError("GraphicsUpdate::LineWidth");
	}
	if(notifyUpdateBits & GXContext::PolygonOffset			   )
	{
		glPolygonOffset(polygonOffsetState.getFactor(), polygonOffsetState.getUnits());

		checkGLError("GraphicsUpdate::PolygonOffset");
	}
	if(notifyUpdateBits & GXContext::Scissor				   )
	{
		glScissor(scissor.x, scissor.y, scissor.width, scissor.height);

		checkGLError("GraphicsUpdate::Scissor");
	}
	if(notifyUpdateBits & GXContext::ShaderProgram			   )
	{
		if(shaderProgram && shaderProgram->handle)
		{
			glUseProgram((GLuint)shaderProgram->handle);
		}
		else
		{
			glUseProgram(0);
		}

		checkGLError("GraphicsUpdate::ShaderProgram");
	}
	if(notifyUpdateBits & GXContext::StencilFunc			   )
	{
		GXStencilTestMode frontMode = stencilTestStateFront.getMode();
		int frontRef				= stencilTestStateFront.getReference();
		int frontReadMask			= stencilTestStateFront.getReadMask();
		int frontWriteMask			= stencilTestStateFront.getWriteMask();

		GXStencilTestMode backMode	= stencilTestStateBack.getMode();
		int backRef					= stencilTestStateBack.getReference();
		int backReadMask			= stencilTestStateBack.getReadMask();
		int backWriteMask			= stencilTestStateBack.getWriteMask();

		glStencilFuncSeparate(GL_FRONT, frontMode.getValue(), frontRef, frontReadMask);
		glStencilFuncSeparate(GL_BACK , backMode .getValue(), backRef , backReadMask );
		glStencilMaskSeparate(GL_FRONT, frontWriteMask);
		glStencilMaskSeparate(GL_BACK , backWriteMask);

		checkGLError("GraphicsUpdate::StencilFunc");
	}
	if(notifyUpdateBits & GXContext::StencilOp				   )
	{
		GXStencilOp frontFailOp		= stencilOpStateFront.getFailOp() ;
		GXStencilOp frontZFailOp	= stencilOpStateFront.getZFailOp();
		GXStencilOp frontZPassOp	= stencilOpStateFront.getZPassOp();

		GXStencilOp backFailOp		= stencilOpStateBack.getFailOp() ;
		GXStencilOp backZFailOp		= stencilOpStateBack.getZFailOp();
		GXStencilOp backZPassOp		= stencilOpStateBack.getZPassOp();

		glStencilOpSeparate(GL_FRONT, frontFailOp.getValue(), frontZFailOp.getValue(), frontZPassOp.getValue());
		glStencilOpSeparate(GL_BACK , backFailOp .getValue(), backZFailOp .getValue(), backZPassOp .getValue());

		checkGLError("GraphicsUpdate::StencilOp");
	}
	if(notifyUpdateBits & GXContext::Texture0				   )
	{
		updateTexture(0, textures[0]);

		checkGLError("GraphicsUpdate::Texture0");
	}
	if(notifyUpdateBits & GXContext::TextureN				   )
	{
		for(int i=0; i<textures.length(); i++)
		{
			glActiveTexture(GL_TEXTURE0+i);
			updateTexture(i, textures[i]);
		}
		glActiveTexture(GL_TEXTURE0);

		checkGLError("GraphicsUpdate::TextureN");
	}
	if(notifyUpdateBits & GXContext::VertexBuffer0			   )
	{
		updateVertexBuffer(0, vertexBuffers[0]);

		checkGLError("GraphicsUpdate::VertexBuffer0");
	}
	if(notifyUpdateBits & GXContext::VertexBufferN			   )
	{
		for(int i=0; i<vertexBuffers.length(); i++)
		{
			updateVertexBuffer(i, vertexBuffers[i]);
		}
		
		checkGLError("GraphicsUpdate::VertexBufferN");
	}
	if(notifyUpdateBits & GXContext::IndexBuffer0			   )
	{
		updateIndexBuffer(0, indexBuffers[0]);

		checkGLError("GraphicsUpdate::IndexBuffer0");
	}
	if(notifyUpdateBits & GXContext::IndexBufferN			   )
	{
		for(int i=0; i<indexBuffers.length(); i++)
		{
			updateIndexBuffer(i, indexBuffers[i]);
		}
		
		checkGLError("GraphicsUpdate::IndexBufferN");
	}
	if(notifyUpdateBits & GXContext::Viewport				   )
	{
		glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

		checkGLError("GraphicsUpdate::Viewport");
	}
}

void GXContext::updateTexture(int i, GXTexture *texture)
{
	if(texture)
	{
		const GXPixelBufferType			&textureType	= texture->getType();
		const GXTextureMagFilterMode	&magFilter		= texture->getFilter().getMagFilter();
		const GXTextureMinFilterMode	&minFilter		= texture->getFilter().getMinFilter();
		const GXTextureWrapMode			&wrapS			= texture->getWrap().getWrapS();
		const GXTextureWrapMode			&wrapT			= texture->getWrap().getWrapT();
		float anisotropy								= texture->getMaxAnisotropy();

		checkGLError("GraphicsUpdate::Viewport");
		glBindTexture(textureType.getValue(), texture->handle);

		checkGLError("GraphicsUpdate::Viewport");
		glTexParameteri(textureType.getValue(), GL_TEXTURE_MAG_FILTER, magFilter.getValue());
		checkGLError("GraphicsUpdate::Viewport");

		glTexParameteri(textureType.getValue(), GL_TEXTURE_MIN_FILTER, minFilter.getValue());
		checkGLError("GraphicsUpdate::Viewport");

		glTexParameteri(textureType.getValue(), GL_TEXTURE_WRAP_S, wrapS.getValue());
		
		checkGLError("GraphicsUpdate::Viewport");
		glTexParameteri(textureType.getValue(), GL_TEXTURE_WRAP_T, wrapT.getValue());
		checkGLError("GraphicsUpdate::Viewport");
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void GXContext::updateVertexBuffer(int i, GXVertexBuffer *vertexBuffer)
{
	int maxVertexAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

	if(vertexBuffer)
	{
		unsigned int vertexBufferHandle			= vertexBuffer->vertexBufferHandle;
		const Vector<GXVertexFormat> &formats	= vertexBuffer->getFormats();
		unsigned int stride						= vertexBuffer->stride;
	
		if(vertexBufferHandle)
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		else
			glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        checkGLError("GraphicsUpdate::update");
	
		for(int i=0; i<maxVertexAttribs; i++)
			glDisableVertexAttribArray(i);
        
        checkGLError("GraphicsUpdate::update");
	
		int offset = 0;
		for(int i=0; i<formats.length(); i++)
		{
			int numElements  = formats[i].getNumElements();
			int elementType  = formats[i].getElementType();
			bool normalize	 = formats[i].getNormalize();

			glEnableVertexAttribArray(i);
			glVertexAttribPointer
			(
				i, 
				numElements, // formats[i].getNumElements(),
				elementType, // formats[i].getElementType(),
				normalize, // formats[i].getNormalize(),
				stride, 
				(const void *)offset
			);
            
            checkGLError("GraphicsUpdate::update");

			offset += formats[i].getSize();
		}
	}
	else
	{
		for(int i=0; i<maxVertexAttribs; i++)
			glDisableVertexAttribArray(i);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void GXContext::updateIndexBuffer(int i_, GXIndexBuffer *indexBuffer_)
{
	if(indexBuffer_)
	{
		unsigned int indexBufferHandle			= indexBuffer_->indexBufferHandle;
	
		if(indexBufferHandle)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
		else
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}