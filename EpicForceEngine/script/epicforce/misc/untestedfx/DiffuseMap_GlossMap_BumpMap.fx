string vertexDesc = "position,float3,normal,float3,texcoord0,float2";

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
/*
float4 k_a 
<
	string UIName = "Ambient Color";
> = float4( 0.47f, 0.47f, 0.47f, 1.0f );    // ambient

float4 k_d
<
	string UIName = "Diffuse Color";
> = float4( 0.47f, 0.47f, 0.47f, 1.0f );    // diffuse
*/

texture diffuseMap : DiffuseMap
< 
	string name		= "diffusemap.png"; 
	string UIName	= "Diffuse Texture";
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

float4 k_s
<
	string UIName = "Specular Color";
> = float4( 1.0f, 1.0f, 1.0f, 1.0f );       // specular

int p
<
	string UIName = "Specular Power";
	string UIType = "IntSpinner";
	float UIMin = 0.0f;
	float UIMax = 50.0f;	
> = 15;

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

texture bumpMap : BumpMap
< 
	string name		= "bumpmap.png"; 
	string UIName	= "Bump Texture";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler bumpMapSampler = sampler_state
{
    Texture   = (bumpMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

/*
float4 selfIllumination
<
	string UIName = "Self Illumination";
> = float4( 0.0f, 0.0f, 0.0f, 0.0f );       // specular
*/

//-----------------------------------------------------------------
// Maps
//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 worldMatI			: WORLDI;
float4x4 worldViewMatI		: WORLDVIEWI;
float4x4 viewMat			: VIEW;
float4x4 viewMatI			: VIEWI;
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
    return max(0, dot(L, N));				// diffuse
}

float3 blinnSpecular(float3 H, float3 N, int p)
{
	return pow(max(0, dot(H, N)), p);		// specular
}

//////////////////////////////////////////////////////////////////////////
// PerVertex Lighting Shader
struct VSInput
{
	float3 position		: POSITION;
	float3 normal		: NORMAL;
	float2 texCoord0	: TEXCOORD0;
	float3 tangent		: TANGENT;
	float3 binormal		: BINORMAL;
};

struct VSOuput
{
    float4 position			: POSITION;
	float2 texCoord0		: TEXCOORD0;
	float3 lightVector		: TEXCOORD2; // tangent space lightVector
	float3 halfVector		: TEXCOORD3; // half space halfVector
};

VSOuput VS(VSInput input)
{
    VSOuput output = (VSOuput)0;

	float3x3 objToTangentSpace;
	objToTangentSpace[0] = input.binormal;
	objToTangentSpace[1] = input.tangent;
	objToTangentSpace[2] = input.normal;

	float3 N			= (float3)input.normal;										// normal (object space)
	float3 L			= convertWorldToObj(dirLightDir);							// light (object space)
	float3 V			= -normalize(mul(input.position, worldViewMat));			// view direction (object space)
	float3 H			= normalize(L + V);											// half vector (object space)

    output.position 	= mul(float4(input.position, 1), worldViewProjMat);			
	output.texCoord0	= input.texCoord0;
	output.lightVector	= mul(objToTangentSpace, L);
	output.halfVector	= mul(objToTangentSpace, H);

    return output;
}

struct PSInput
{
    float4 position			: POSITION;
	float2 texCoord0		: TEXCOORD0;
	float3 lightVector		: TEXCOORD2;
	float3 halfVector		: TEXCOORD3;
};

struct PSOuput
{
    float4 color		: COLOR;
};

PSOuput PS(PSInput input)
{
	PSOuput output = (PSOuput)0;
	
	float4 diffuseColor		= tex2D(diffuseMapSampler , input.texCoord0);
	float3 glosssiness		= tex2D(glossMapSampler, input.texCoord0);
	float3 N				= 2 * (tex2D(bumpMapSampler, input.texCoord0)-0.5);
	float3 L				= input.lightVector;
	float3 H				= input.halfVector;
	
	output.color  			= float4((ambientLightColor + dirLightColor * blinnDiffuse (L, N) ) * diffuseColor +
									  dirLightColor * k_s * blinnSpecular(H, N, p), 1);
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