//////////////////////////////////////////////////////////////////////////
// Uniform Variables with UI

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

//////////////////////////////////////////////////////////////////////////
// Uniform Variables without UI
float4x4 worldMat			: WORLD;
float4x4 viewMat			: VIEW;
float4x4 viewMatI			: VIEWI;
float4x4 projectionMat		: PROJECTION;

//////////////////////////////////////////////////////////////////////////
// Application Data
struct VSInput
{
	float3 position		: POSITION;
	float2 texCoord0	: TEXCOORD0;
};

struct VSOutput
{
    float4 position		: POSITION;
	float2 texCoord0	: TEXCOORD0;
};

struct PSOutput
{
    float4 color		: COLOR0;
};

//////////////////////////////////////////////////////////////////////////
// Vertex Shader
VSOutput VS(VSInput input)
{
    VSOutput output = (VSOutput)0;

	float4x4 mat = worldMat;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0;
	
	float3 p = mul(float4(input.position, 1), mat) + float3(viewMatI[3][0], viewMatI[3][1], viewMatI[3][2]);

    output.position		= mul(mul(float4(p, 1), viewMat), projectionMat);
	output.texCoord0	= input.texCoord0;

    return output;
}

//////////////////////////////////////////////////////////////////////////
// Pixel Shader
PSOutput PS(VSOutput input)
{
	PSOutput output = (PSOutput)0;
	
	float3 diffuseColor		= tex2D(diffuseMapSampler , input.texCoord0);
	output.color			= float4(diffuseColor, 1);

	return output;
}


/////////////////////////////////////////////////////////////////////////////////////
//
technique BlinnShadePerVertexLighting
{
    pass P0
    {
		// vertex State
		CullMode				= none;							// NONE, CW, CCW
		ZEnable					= false;

        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}