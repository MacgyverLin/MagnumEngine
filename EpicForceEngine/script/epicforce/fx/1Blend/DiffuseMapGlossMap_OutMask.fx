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
// Diffuse Map
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
    MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
};

// Specular Color
float4 specularColor
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
void VS(in  float3 inputPosition		: POSITION,
	    in  float3 inputNormal		: NORMAL,
	    in  float2 inputTexCoord0	: TEXCOORD0,
		out float4 outputPosition	: POSITION,
		out float4 outputColor0		: COLOR0,
		out float4 outputColor1		: COLOR1,
		out float2 outputTexCoord0	: TEXCOORD0)
{
	float3 N = normalize(mul(inputNormal,(float3x3)worldViewMat));					// normal (view space)
	float3 L = convertWorldToView(dirLightDir);										// light (view space)
	float3 V = float3(0, 0, -1);													// view direction
	float3 H = normalize(L + V);													// half vector

    outputPosition		= mul(float4(inputPosition, 1), worldViewProjMat);
	outputColor0 		= float4(ambientLightColor + dirLightColor * blinnDiffuse (L, N), 1);	// ambient + diffuse Lighting
	outputColor1 		= float4(dirLightColor * specularColor * blinnSpecular(H, N, p), 1);				// specular color
	outputTexCoord0		= inputTexCoord0;
}

void PS(in  float4 inputPosition	: POSITION,
		in  float4 inputColor0		: COLOR0,
		in  float4 inputColor1		: COLOR1,
		in  float2 inputTexCoord0	: TEXCOORD0,
		out float4 outputColor		: COLOR)
{
	float4 diffuseColor		= tex2D(diffuseMapSampler , inputTexCoord0);
	if(diffuseColor.a==0)
		discard;

	float3 glosssiness		= tex2D(glossMapSampler, inputTexCoord0);

	outputColor				= float4(inputColor0.rgb * diffuseColor.rgb + inputColor1.rgb * glosssiness.rgb, 1);
}

/////////////////////////////////////////////////////////////////////////////////////
//
technique BlinnShadePerVertexLighting
{
    pass P0
    {
        CullMode 				= cw;
        ShadeMode 				= Gouraud;

		AlphaBlendEnable		= false;							// TRUE, FALSE
		BlendOp					= ADD;							// ADD, SUBTRACT, REVSUBTRACT;
		SrcBlend				= SRCALPHA;						// ZERO, ONE, SRCCOLOR, INVSRCCOLOR, SRCALPHA, INVSRCALPHA, DESTALPHA, INVDESTALPHA, DESTCOLOR, INVDESTCOLOR, SRCALPHASAT,		
		DestBlend				= INVSRCALPHA;					// ZERO, ONE, SRCCOLOR, INVSRCCOLOR, SRCALPHA, INVSRCALPHA, DESTALPHA, INVDESTALPHA, DESTCOLOR, INVDESTCOLOR, SRCALPHASAT,

		ZEnable					= true;
		ZWriteEnable			= true;

        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}