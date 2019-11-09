string vertexDesc = "position,float3,normal,float3,texcoord0,float2";

float4 ambientLightColor
<
	string UIName = "Ambient Light Color";
> = {0.2, 0.2, 0.2, 1.0};

float4 k_s
<
	string UIName = "Specular";
> = {1.0, 1.0, 1.0, 1.0};

int p
<
	string UIName = "Specular Power";	string UIType = "IntSpinner";	float UIMin = 0.0;	float UIMax = 50.0;
> = {15};

float envMapAmt
<
	string UIName = "Environment Texture Amount";
> = {0.4};

float4x4 worldMat : WORLD;

float4x4 viewMat : VIEW;

float4x4 projectionMat : PROJECTION;

float4x4 worldViewMat : WORLDVIEW;

float4x4 worldViewProjMat : WORLDVIEWPROJ;

float4x4 worldInvMat : WORLDI;

float4x4 viewInvMat : VIEWI;

float4x4 projectionInvMat : PROJECTIONI;

float4x4 worldViewInvMat : WORLDVIEWI;

float4x4 worldViewProjInvMat : WORLDVIEWPROJI;

float3 worldCameraPosition : WORLDCAMERAPOSITION;

float3 localBoxMin : LOCALBBOXMIN;

float3 localBoxMax : LOCALBBOXMAX;

float3 localBoxSize : LOCALBBOXSIZE;

float3 directionLightDirection : DIRECTION = {1, 1, 1};

float4 directionLightColor : LIGHTCOLOR = {1, 0, 0, 1};

float3 omniLight0Position : POSITION = { 5, 5, 5};

float4 omniLight0Color : LIGHTCOLOR = {0, 1, 0, 1};

float4 omniLight0Atteunation : LIGHTATTENUATION = {1, 10, 100, 200};

float3 omniLight1Position : POSITION = {-5, 5, 5};

float4 omniLight1Color : LIGHTCOLOR = {0, 0, 1, 1};

float4 omniLight1Atteunation : LIGHTATTENUATION = {1, 10, 100, 200};

float3 spotLight1Position : POSITION = {-5, -5, 1};

float4 spotLight1Color : LIGHTCOLOR = {1, 1, 1, 1};

float4 spotLight1Atteunation : LIGHTATTENUATION = {1, 10, 100, 200};

float spotLight1HotSpot : LIGHTHOTSPOT = 10;

float spotLight1FallOff : LIGHTFALLOFF = 40;

texture diffuseMap : DIFFUSEMAP
<
	string name		= "";
	string UIName	= "diffuseMap Texture";
	string type		= "2D";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler diffuseMapSampler = sampler_state
{
	Texture			= (diffuseMap);
	MinFilter		= Linear;
	MagFilter		= Linear;
	MipFilter		= Linear;
	ADDRESSU		= Wrap;
	ADDRESSV		= Wrap;
};

texture glossMap : SPECULARMAP
<
	string name		= "";
	string UIName	= "glossMap Texture";
	string type		= "2D";
	int Texcoord	= 0;
	int MapChannel	= 1;
>;

sampler glossMapSampler = sampler_state
{
	Texture			= (glossMap);
	MinFilter		= Linear;
	MagFilter		= Linear;
	MipFilter		= Linear;
	ADDRESSU		= Wrap;
	ADDRESSV		= Wrap;
};

texture envMap : REFLECTIONMAP
<
	string name		= "";
	string UIName	= "envMap Texture";
	string type		= "Cube";
>;

samplerCUBE envMapSampler = sampler_state
{
	Texture			= (envMap);
	MinFilter		= Linear;
	MagFilter		= Linear;
	MipFilter		= Linear;
};

float3 convertWorldToView(float3 dir) { return normalize(mul(dir, (float3x3)viewMat)); /* from max : dirLightDir is worldspace */ } float3 convertWorldToObj(float3 dir) { return normalize(mul(dir, (float3x3)worldInvMat)); /* from max : dirLightDir is worldspace */ } float3 blinnDiffuse(float3 L, float3 N) { return max(0, dot(N, L)); /* diffuse */ } float3 blinnSpecular(float3 H, float3 N, int p) { return pow(max(0, dot(N, H)), p); /* specular */ } /* PerVertex Lighting Shader */ struct VSInput { float3 position : POSITION; float3 normal : NORMAL; float2 texCoord0 : TEXCOORD0; }; struct VSOutput { float4 position : POSITION; float3 normal : NORMAL; float4 color0 : COLOR0; float4 color1 : COLOR1; float2 texCoord0 : TEXCOORD0; }; VSOutput VS(VSInput input) { VSOutput output = (VSOutput)0; float3 N = normalize(mul(input.normal,(float3x3)worldViewMat)); /* normal (view space) */ float3 L = convertWorldToView(directionLightDirection); /* light (view space) */ float3 V = float3(0, 0, -1); /* view direction */ float3 H = normalize(L + V); /* half vector */ output.position = mul(float4(input.position, 1), worldViewProjMat); output.normal = N; output.color0 = float4(ambientLightColor + directionLightColor * blinnDiffuse (L, N), 1); /* ambient + diffuse Lighting */ output.color1 = float4(directionLightColor * k_s * blinnSpecular(H, N, p), 1); /* specular color */ output.texCoord0 = input.texCoord0; return output; }struct PSInput { float4 position : POSITION; float3 normal : NORMAL; float4 color0 : COLOR0; float4 color1 : COLOR1; float2 texCoord0 : TEXCOORD0; }; struct PSOutput { float4 color : COLOR; }; PSOutput PS(PSInput input) { PSOutput output = (PSOutput)0; float3 diffuseColor = tex2D(diffuseMapSampler , input.texCoord0); float3 envColor = texCUBE(envMapSampler, reflect(float3(0, 0, -1), input.normal) ) * envMapAmt; output.color = float4(input.color0 * diffuseColor + (float3)input.color1 + envColor, 1); return output; }

technique DiffuseMap
{
	pass p0
	{
		cullmode = ccw;
		alphablendenable = true;
		blendop = add;
		colorwriteenable = red | green | blue| alpha ;
		destblend = zero;
		fillmode = solid;
		shademode = gouraud;
		srcblend = one;
		stencilenable = false;
		stencilfail = keep;
		stencilfunc = always;
		stencilmask = 0xffffffff;
		stencilpass = keep;
		stencilref = 0;
		stencilwritemask = 0xffffffff;
		stencilzfail = keep;
		zenable = true;
		zfunc = lessequal;
		zwriteenable = true;

		VertexShader = compile vs_3_0 VS();
		PixelShader  = compile ps_3_0 PS();
	}
}
