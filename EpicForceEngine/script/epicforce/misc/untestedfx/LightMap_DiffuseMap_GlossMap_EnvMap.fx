string vertexDesc = "position,float3,normal,float3,texcoord0,float2,texcoord1,float2";

//////////////////////////////////////////////////////////////////////////
// Uniform Variables with UI

//-----------------------------------------------------------------
// Lights
float4 ambientLightColor
<
	string UIName = "Ambient Light Color"; 
> = {0.2, 0.2, 0.2, 1.0};

float3 dirLightDir : DIRECTION 
<
	string UIName = "Directional Light"; 
	string Object = "TargetLight";
	int RefID = 0;
> = {-0.577, -0.577, 0.577};

float4 dirLightColor : LIGHTCOLOR
<
	string UIName = "Directional Light"; 
	int LightRef = 0;
>;

float3 omniLightPosition0 : POSITION
<
	string UIName	= "Omni Light 1"; 
	string Object	= "OmniLight";
	int RefID		= 1;
> = {-0.577, -0.577, 0.577};

float4 omniLightColor0 : LIGHTCOLOR
<
	string UIName	= "Omni Light 1"; 
	int LightRef	= 1;
>;

float3 omniLightPosition1 : POSITION
<
	string UIName	= "Omni Light 2"; 
	string Object	= "OmniLight";
	int RefID		= 2;
> = {-0.577, -0.577, 0.577};

float4 omniLightColor1 : LIGHTCOLOR
<
	string UIName	= "Omni Light 2"; 
	int LightRef	= 2;
>;

//-----------------------------------------------------------------
// material reflectivity
texture lightMap : LightMap
< 
	string name		= "lightMap.png"; 
	string UIName	= "LightMap Texture";
	int Texcoord	= 1;
	int MapChannel	= 2;
>;

sampler lightMapSampler = sampler_state
{
    Texture   = (lightMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

texture diffuseMap : DiffuseMap
< 
	string name		= "diffusemap.png"; 
	string UIName	= "Diffuse Map";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler diffuseMapSampler = sampler_state
{
    Texture   = (diffuseMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

// Specular Color
float4 k_s
<
	string UIName = "Specular";
> = float4( 1.0f, 1.0f, 1.0f, 1.0f );       // specular

// GlossMap
texture glossMap : SpecularMap
< 
	string name		= "glossMap.png"; 
	string UIName	= "Gloss Map";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler glossMapSampler = sampler_state
{
    Texture   = (glossMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

int p
<
	string UIName = "Specular Power";
	string UIType = "IntSpinner";
	float UIMin = 0.0f;
	float UIMax = 50.0f;	
> = 15;

texture envMap : Environment 
<
	string name		= "envmap.png"; 
	string UIName	= "Environment Texture";
	string type     = "Cube";
>;

samplerCUBE envSampler = sampler_state
{
	Texture = <envMap>;
	MipFilter = Linear;
	MinFilter = Linear;
	MagFilter = Linear;
};

float envMapAmt
<
	string UIName	= "Environment Texture Amount"; 
> = 1.0;

//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 worldMatI			: WORLDI;
float4x4 viewMat			: VIEW;
float4x4 projectionMat		: PROJECTION;
float4x4 worldViewProjMat	: WORLDVIEWPROJ;
float4x4 worldViewMat		: WORLDVIEW;

//////////////////////////////////////////////////////////////////////////
// Code

//////////////////////////////////////////////////////////////////////////
// Shading Function
float3 convertWorldToView(float3 dir)
{
#ifdef MAX
	return normalize(mul(dir, (float3x3)viewMat));			// from max : dirLightDir is worldspace
#else
	return normalize(mul(dir, (float3x3)viewMat));			// from game : dirLightDir is worldspace
#endif
}

float3 convertWorldToObj(float3 dir)
{
#ifdef MAX
	return normalize(mul(dir, (float3x3)worldMatI));			// from max : dirLightDir is worldspace
#else
	return normalize(mul(dir, (float3x3)worldMatI));			// from game : dirLightDir is worldspace
#endif
}

float3 blinnDiffuse(float3 L, float3 N)
{
    return max(0, dot(N, L));				// diffuse
}

float3 blinnSpecular(float3 H, float3 N, int p)
{
	return pow(max(0, dot(N, H)), p);		// specular
}

//////////////////////////////////////////////////////////////////////////
// PerVertex Lighting Shader
struct VSInput
{
	float3 position		: POSITION;
	float3 normal		: NORMAL;
	float2 texCoord0	: TEXCOORD0;
	float2 texCoord1	: TEXCOORD1;
};

struct VSOuput
{
    float4 position		: POSITION;
	float3 normal	    : NORMAL;
    float4 color0		: COLOR0;
	float4 color1		: COLOR1;
	float2 texCoord0	: TEXCOORD0;
	float2 texCoord1	: TEXCOORD1;
};

VSOuput VS(VSInput input)
{
    VSOuput output = (VSOuput)0;

	float3 N = normalize(mul(input.normal,(float3x3)worldViewMat));					// normal (view space)
	float3 L = convertWorldToView(dirLightDir);										// light (view space)
	float3 V = float3(0, 0, -1);													// view direction
	float3 H = normalize(L + V);													// half vector

    output.position		= mul(float4(input.position, 1), worldViewProjMat);
	output.normal		= N;
	output.color0 		= float4(ambientLightColor + dirLightColor * blinnDiffuse (L, N), 1);	// ambient + diffuse Lighting
	output.color1 		= float4(dirLightColor * k_s * blinnSpecular(H, N, p), 1);				// specular color
	output.texCoord0	= input.texCoord0;
	output.texCoord1	= input.texCoord1;

    return output;
}

struct PSInput
{
    float4 position		: POSITION;
	float3 normal	    : NORMAL;
    float4 color0		: COLOR0;
	float4 color1		: COLOR1;
	float2 texCoord0	: TEXCOORD0;
	float2 texCoord1	: TEXCOORD1;
};

struct PSOuput
{
    float4 color		: COLOR;
};

PSOuput PS(PSInput input)
{
	PSOuput output = (PSOuput)0;
	
	float3 diffuseColor		= tex2D(diffuseMapSampler , input.texCoord0);
	float3 diffuseLighting	= tex2D(lightMapSampler   , input.texCoord1);
	float3 glosssiness		= tex2D(glossMapSampler, input.texCoord0);
	float3 envColor			= texCUBE(envSampler, reflect(float3(0, 0, -1), input.normal) ) * envMapAmt;

	output.color			= float4(diffuseLighting * diffuseColor + ((float3)input.color1+envColor) * glosssiness, 1);

    return output;
}

/////////////////////////////////////////////////////////////////////////////////////
//
technique BlinnShadePerVertexLighting
{
    pass P0
    {
        // shaders
        CullMode = None;
        ShadeMode = Gouraud;
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}