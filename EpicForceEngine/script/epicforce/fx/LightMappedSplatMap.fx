//-----------------------------------------------------------------
// Layer1 Map
texture layer1Map : DiffuseMap
< 
	string name		= "layer1Map.png"; 
	string UIName	= "Diffuse Texture";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler layer1MapSampler = sampler_state
{
    Texture   = (layer1Map);
    MipFilter = POINT;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

//-----------------------------------------------------------------
// Layer2 Map
texture layer2Map : DiffuseMap
< 
	string name		= "layer2Map.png"; 
	string UIName	= "Diffuse Texture";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler layer2MapSampler = sampler_state
{
    Texture   = (layer2Map);
    MipFilter = POINT;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

//-----------------------------------------------------------------
// Layer2 Map
texture lightMap : DiffuseMap
< 
	string name		= "lightMap.png"; 
	string UIName	= "Diffuse Texture";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler lightMapSampler = sampler_state
{
    Texture   = (lightMap);
    MipFilter = POINT;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

//-----------------------------------------------------------------
// material reflectivity
// Diffuse Map
texture splatMap : DiffuseMap
< 
	string name		= "splatMap.png"; 
	string UIName	= "Diffuse Texture";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler splatMapSampler = sampler_state
{
    Texture   = (splatMap);
    MipFilter = POINT;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

float texturePatchPerMeter
<
	string UIName = "texture Patches Per Meter";
	string UIType = "FloatSpinner";
	int UIMin = 0.1;
	int UIMax = 10;
> = 1;

//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 worldViewProjMat	: WORLDVIEWPROJ;
float3 localbboxmin			: LOCAL_BBOX_MIN;
float3 localbboxmax			: LOCAL_BBOX_MAX;

//////////////////////////////////////////////////////////////////////////
// PerVertex Lighting Shader
void VS(in float3 inputPosition		: POSITION,
		out float4 outputPosition	: POSITION,
		out float2 outputTexCoord0	: TEXCOORD0,
		out float2 outputTexCoord1	: TEXCOORD1)
{
    outputPosition		= mul(float4(inputPosition, 1), worldViewProjMat);

	float4 texcoord0	= float4(inputPosition, 1);
	float2 bboxsize		= (localbboxmax.xy - localbboxmin.xy);

	outputTexCoord0		= (texcoord0.xy * bboxsize.xy    * texturePatchPerMeter) / bboxsize.xy;
	outputTexCoord1		= (texcoord0.xy - localbboxmin.xy) / bboxsize.xy;
}

void PS(in float4 inputPosition		: POSITION,
		in float2 inputTexCoord0	: TEXCOORD0,
		in float2 inputTexCoord1	: TEXCOORD1,
		out float4 outputColor		: COLOR)
{
	float4 diffuseColor1	= tex2D(layer1MapSampler, inputTexCoord0);
	float4 diffuseColor2	= tex2D(layer2MapSampler, inputTexCoord0);
	float4 splatColor		= tex2D(splatMapSampler, inputTexCoord1);
	float4 lightMapColor	= tex2D(lightMapSampler, inputTexCoord1);

	outputColor				= float4(lightMapColor.rgb*(diffuseColor1.rgb * splatColor.a + diffuseColor2.rgb * (1.0-splatColor.a)), 1);
}

/////////////////////////////////////////////////////////////////////////////////////
//
technique Default
{
    pass P0
    {
        CullMode 				= cw;
        ShadeMode 				= Gouraud;

		AlphaBlendEnable		= false;						// TRUE, FALSE
		BlendOp					= ADD;							// ADD, SUBTRACT, REVSUBTRACT;
		SrcBlend				= SRCALPHA;						// ZERO, ONE, SRCCOLOR, INVSRCCOLOR, SRCALPHA, INVSRCALPHA, DESTALPHA, INVDESTALPHA, DESTCOLOR, INVDESTCOLOR, SRCALPHASAT,		
		DestBlend				= INVSRCALPHA;					// ZERO, ONE, SRCCOLOR, INVSRCCOLOR, SRCALPHA, INVSRCALPHA, DESTALPHA, INVDESTALPHA, DESTCOLOR, INVDESTCOLOR, SRCALPHASAT,

		ZEnable					= true;
		ZWriteEnable			= true;
		
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}