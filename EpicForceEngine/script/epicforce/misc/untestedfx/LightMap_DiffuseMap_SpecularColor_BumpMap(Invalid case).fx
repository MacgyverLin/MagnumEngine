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
float envMapAmt
<
	string UIName	= "This Shader is invalid!!!"; 
> = 1.0;
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
};

struct VSOuput
{
    float4 position			: POSITION;
};

VSOuput VS(VSInput input)
{
    VSOuput output = (VSOuput)0;

    output.position 	= mul(float4(input.position, 1), worldViewProjMat);

    return output;
}

struct PSInput
{
    float4 position			: POSITION;
};

struct PSOuput
{
    float4 color		: COLOR;
};

PSOuput PS(PSInput input)
{
	PSOuput output = (PSOuput)0;
	
	output.color  			= float4(0.3, 0.3, 0.3, 1.0);
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