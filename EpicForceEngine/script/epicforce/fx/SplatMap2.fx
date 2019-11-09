//-----------------------------------------------------------------
// Layer1 Map
texture layer1Map : DiffuseMap
< 
	string name		= "layer1Map.png"; 
	string UIName	= "Diffuse Texture 1";
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

int texture1RepeatCountX
<
	string UIName = "Texture 1 Repeat Count X";
	string UIType = "IntSpinner";
	int UIMin = 1;
	int UIMax = 10000;
> = 100;

int texture1RepeatCountY
<
	string UIName = "Texture 1 Repeat Count Y";
	string UIType = "IntSpinner";
	int UIMin = 1;
	int UIMax = 10000;
> = 100;

int texture2RepeatCountX
<
	string UIName = "Texture 2 Repeat Count X";
	string UIType = "IntSpinner";
	int UIMin = 1;
	int UIMax = 10000;
> = 100;

int texture2RepeatCountY
<
	string UIName = "Texture 2 Repeat Count Y";
	string UIType = "IntSpinner";
	int UIMin = 1;
	int UIMax = 10000;
> = 100;

//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 worldViewProjMat	: WORLDVIEWPROJ;
float3 localBBoxMin			: LOCAL_BBOX_MIN;
float3 localBBoxMax			: LOCAL_BBOX_MAX;

//////////////////////////////////////////////////////////////////////////
// PerVertex Lighting Shader
void VS(in float3 inputPosition		: POSITION,
		out float4 outputPosition	: POSITION,
		out float2 outputTexCoord0	: TEXCOORD0,
		out float2 outputTexCoord1	: TEXCOORD1,
		out float2 outputTexCoord2	: TEXCOORD2)
{
    outputPosition				= mul(float4(inputPosition, 1), worldViewProjMat);

	float4 texcoord				= float4(inputPosition, 1);
	float3 bBoxSize				= localBBoxMax - localBBoxMin;
	float2 invSplatTextureSize	= 1.0 / bBoxSize.xy;
	float2 invColorTexture1Size	= float2(texture1RepeatCountX, texture1RepeatCountY) * invSplatTextureSize;
	float2 invColorTexture2Size	= float2(texture2RepeatCountX, texture2RepeatCountY) * invSplatTextureSize;
	
	outputTexCoord0		= texcoord.xy * invColorTexture1Size;
	outputTexCoord1		= texcoord.xy * invColorTexture2Size;
	outputTexCoord2		= float2((texcoord.x - localBBoxMin.x), -(texcoord.y-localBBoxMin.y)) * invSplatTextureSize;
}

void PS(in float4 inputPosition		: POSITION,
		in float2 inputTexCoord0	: TEXCOORD0,
		in float2 inputTexCoord1	: TEXCOORD1,
		in float2 inputTexCoord2	: TEXCOORD2,
		out float4 outputColor		: COLOR)
{
	float4 diffuseColor1	= tex2D(layer1MapSampler, inputTexCoord0);
	float4 diffuseColor2	= tex2D(layer2MapSampler, inputTexCoord1);
	float4 splatColor		= tex2D(splatMapSampler , inputTexCoord2);

	outputColor				= float4((diffuseColor1.rgb * (1.0-splatColor.a) + diffuseColor2.rgb * splatColor.a) * splatColor.rgb , 1);
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