//-----------------------------------------------------------------
// Layer1 Map
texture layer1Map : DiffuseMap
< 
	string name		= "layer1Map.png"; 
	string UIName	= "Diffuse Texture 1";
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
texture layer2Map : SpecularMap
< 
	string name		= "layer2Map.png";
	string UIName	= "Diffuse Texture 2";
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
// material reflectivity
// Diffuse Map
texture splatMap : OpacityMap
< 
	string name		= "splatMap.png"; 
	string UIName	= "Splat Map";
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

float texturePatchPerUnit1
<
	string UIName = "Texture Patches Per Unit 1";
	string UIType = "FloatSpinner";
	int UIMin = 0.1;
	int UIMax = 10;
> = 1;

float texturePatchPerUnit2
<
	string UIName = "Texture Patches Per Unit 2";
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
		out float2 outputTexCoord1	: TEXCOORD1,
		out float2 outputTexCoord2	: TEXCOORD2)
{
    outputPosition		= mul(float4(inputPosition, 1), worldViewProjMat);

	float4 texcoord		= float4(inputPosition, 1);
	float3 bboxsize		= localbboxmax - localbboxmin;

	outputTexCoord0		= texcoord.xy * texturePatchPerUnit1;
	outputTexCoord1		= texcoord.xy * texturePatchPerUnit2;
	outputTexCoord2		= float2((texcoord.x - localbboxmin.x), (localbboxmin.y - texcoord.y)) / bboxsize.xy;
}

void PS(in float4 inputPosition		: POSITION,
		in float2 inputTexCoord0	: TEXCOORD0,
		in float2 inputTexCoord1	: TEXCOORD1,
		in float2 inputTexCoord2	: TEXCOORD2,
		out float4 outputColor		: COLOR)
{
	float4 diffuseColor1	= tex2D(layer1MapSampler, inputTexCoord0);
	float4 diffuseColor2	= tex2D(layer2MapSampler, inputTexCoord1);
	float4 splatColor		= tex2D(splatMapSampler, inputTexCoord2);

	outputColor				= float4(diffuseColor1.rgb * (1.0-splatColor.r) + diffuseColor2.rgb * splatColor.r, 1);
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