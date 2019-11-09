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
> = {0.6, 0.6, 0.6, 0.6};

float4 lightColor
<
	string UIName = "Light Color";
> = {10.0, 10.0, 10.0, 10.0};

//-----------------------------------------------------------------
// material reflectivity
// Diffuse Map
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

texture splatMap : OpacityMap
< 
	string name		= "splatMap.png"; 
	string UIName	= "Splat Map";
>;

sampler splatMapSampler = sampler_state
{
    Texture   = (splatMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

// EnvMap
texture envMap
< 
	string name		= "envMap.png"; 
	string UIName	= "Enviroment Map";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler envMapSampler = sampler_state
{
    Texture   = (envMap);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

float envAmount
<
	string UIName = "Env Amount";
> = 0.3;       // envAmount

//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 worldMatI			: WORLDI;
float4x4 viewMat			: VIEW;
float4x4 projectionMat		: PROJECTION;
float4x4 worldViewProjMat	: WORLDVIEWPROJ;
float4x4 worldViewMat		: WORLDVIEW;
float3 localBBoxMin			: LOCAL_BBOX_MIN;
float3 localBBoxMax			: LOCAL_BBOX_MAX;

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
void VS(in float3 inputPosition		: POSITION,
	    in float3 inputNormal		: NORMAL,
	    in float2 inputTexCoord0	: TEXCOORD0,
		out float4 outputPosition	: POSITION,
		out float4 outputColor0		: COLOR0,
		out float2 outputTexCoord0	: TEXCOORD0,
		out float2 outputTexCoord1	: TEXCOORD1,
		out float2 outputTexCoord2	: TEXCOORD2)
{
	float3 N = normalize(mul(inputNormal,(float3x3)worldViewMat));					/* normal (view space)	*/
	float3 L = convertWorldToView(dirLightDir);										/* light (view space)	*/
	float3 V = float3(0, 0, -1);													/* view direction		*/
	float3 H = normalize(L + V);													/* half vector			*/

	float4 texcoord				= float4(inputPosition, 1);
	float3 bBoxSize				= localBBoxMax - localBBoxMin;
	float2 invSplatTextureSize	= 1.0 / bBoxSize.xy;

    outputPosition		= mul(float4(inputPosition, 1), worldViewProjMat);
	outputColor0 		= float4(ambientLightColor + dirLightColor * blinnDiffuse (L, N), 1); 	/* ambient + diffuse Lighting	*/
	outputTexCoord0		= inputTexCoord0;
	outputTexCoord1		= float2((texcoord.x - localBBoxMin.x), -(texcoord.y-localBBoxMin.y)) * invSplatTextureSize;
	outputTexCoord2		= float2(N.xy * float2(0.5, 0.5) + float2(0.5, 0.5));
}

void PS(in float4 inputPosition		: POSITION,
		in float4 inputColor0		: COLOR0,
		in float2 inputTexCoord0	: TEXCOORD0,
		in float2 inputTexCoord1	: TEXCOORD1,
		in float2 inputTexCoord2	: TEXCOORD2,
		out float4 outputColor		: COLOR)
{
	float4 diffuseColor		= tex2D(diffuseMapSampler, inputTexCoord0);
	float4 splatColor		= tex2D(splatMapSampler  , inputTexCoord1);
	float4 envMapColor		= tex2D(envMapSampler, inputTexCoord2);

	float4 result			= inputColor0 * diffuseColor * splatColor + lightColor + envMapColor * envAmount;
	outputColor				= float4(result.rgb, diffuseColor.a);
}

/////////////////////////////////////////////////////////////////////////////////////
//
technique Default
{
    pass P0
    {
        CullMode 				= none;
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