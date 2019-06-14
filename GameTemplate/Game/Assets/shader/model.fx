/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t3);	
Texture2D<float4> g_shadowMap : register(t4);		//todo シャドウマップ。
Texture2D<float4> g_normalMap : register(t2);		//	法線マップ。
Texture2D<float4> g_specularMap : register(t5);		//スペキュラマップ。
Texture2D<float4> g_aoMap : register(t6);			//AOマップ。
TextureCube<float4> skyCubeMap : register(t0);     //スカイキューブマップ
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//todo ライトビュー行列を追加。
	float4x4 mLightView;	//ライトビュー行列。
	float4x4 mLightProj;	//ライトプロジェクション行列。
	int isShadowReciever;	//シャドウレシーバーフラグ。
	int isHasNormalMap;	//法線マップある？
	int isHasSpecularMap;	//スペキュラマップある？
	int isHasAoMap;	//AOマップある？
};

////ライト用の定数バッファ
//cbuffer LightCb : register(b0) {
//	float3 dligDirection;
//	float4 dligColor;
//};
//ディレクションライト
struct SDirectionLight {
	float4 direction;
	float4 color;
	float3 ambientLight;
};
/*!
*@brief	ライト用の定数バッファ。
*/
cbuffer LightCb : register(b1) {
	SDirectionLight		directionLight;		//ディレクションライト。
	float3				eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトの絞り。
};

/// <summary>
/// シャドウマップ用の定数バッファ。
/// </summary>
cbuffer ShadowMapCb : register(b1) {
	float4x4 lightViewProjMatrix;	//ライトビュープロジェクション行列。
}
/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos		: TEXCOORD1;	//ワールド座標。
	float4 posInLVP		: TEXCOORD2;	//ライトビュープロジェクション空間での座標。
};
/// <summary>
/// シャドウマップ用のピクセルシェーダへの入力構造体。
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//座標。
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	//ローカル座標系からワールド座標系に変換する。
	float4 worldPos = mul(mWorld, In.Position);
	//鏡面反射のためにワールド座標をピクセルシェーダーに渡す。
	psInput.worldPos = worldPos.xyz;
	//ワールド座標系からカメラ座標系に変換する。
	psInput.Position = mul(mView, worldPos);
	//カメラ座標系からスクリーン座標系に変換する。
	psInput.Position = mul(mProj, psInput.Position);
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, worldPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}

	//pos = mul(mView, pos);
	//pos = mul(mProj, pos);
	//psInput.Position = pos;
	
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	////UV座標はそのままピクセルシェーダーに渡す。
	//psInput.TexCoord = In.TexCoord;
	////法線をワールド行列で変換する。
	////法線がfloat3の3要素のベクトルなので、回転と拡大の変換だけが行われる。
	//psInput.Normal = mul(mWorld, In.Normal);
	////拡大成分が入っているかもしれないので、正規化しとこ。
	//psInput.Normal = normalize(psInput.Normal);
	////接ベクトルも回す。
	//psInput.Tangent = mul(mWorld, In.Tangent);
	//psInput.Tangent = normalize(psInput.Tangent);
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	    
		
	}
	float4 WPos = pos;
	if (isShadowReciever == 1) {
		//続いて、ライトビュープロジェクション空間に変換。
		psInput.posInLVP = mul(mLightView, WPos);
		psInput.posInLVP = mul(mLightProj, psInput.posInLVP);
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);

	//法線を計算する。
	float3 normal = 0;
	if (isHasNormalMap == 1) {
		//法線マップがある。
		//法線と接ベクトルの外積を計算して、従ベクトルを計算する。
		float3 biNormal = cross(In.Normal, In.Tangent);
		normal = g_normalMap.Sample(Sampler, In.TexCoord);
		//0.0～1.0の範囲になっているタンジェントスペース法線を
		//-1.0～1.0の範囲に変換する。
		normal = (normal * 2.0f) - 1.0f;
		//法線をタンジェントスペースから、ワールドスペースに変換する。
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}
	else {
		//ない。
		normal = In.Normal;
	}

	//ディレクションライトの拡散反射光を計算する。
	float3 lig = max(0.0f, dot(normal * -1.0f, directionLight.direction)) * directionLight.color.xyz;
	////ディレクションライトの鏡面反射光を計算する。
	{
		
		// ライトを当てる面から視点に伸びるベクトルtoEyeDirを求める。
		

		{
			float3 toEyeDir = normalize(In.worldPos - eyePos);

			//求めたtoEyeDirの反射ベクトルを求める。
			float3 reflectEyeDir = -toEyeDir + 2 * dot(normal, toEyeDir) * normal;

			//求めた反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
			float t = max(0.0f, dot(-directionLight.direction,reflectEyeDir));
			float specPower = 1.0f;
			if (isHasSpecularMap) {
				//スペキュラマップがある。
				specPower = g_specularMap.Sample(Sampler, In.TexCoord);
			}
			//pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
			
			float4 specLig = pow(t, specPow) * specPower * directionLight.color;
			//スペキュラ反射が求まったら、ligに加算する。
			//鏡面反射を反射光に加算する。
			lig = lig + specLig;
		}
	}
	if (isShadowReciever == 1) {	
		//シャドウレシーバー。
		//LVP空間から見た時の最も手前の深度値をシャドウマップから取得する。

		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		
		////シャドウマップの範囲内かどうかを判定する。
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x > 0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {

		//	///LVP空間での深度値を計算。

			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//シャドウマップに書き込まれている深度値を取得。
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);

			if (zInLVP > zInShadowMap+0.001f) {
				//影が落ちているので、光を弱くする
				lig *= 0.5f;
			}
		}
	}



	float4 finalColor = float4(0.0f, 0.0f,0.0f, 1.0f);
	finalColor.xyz += albedoColor.xyz * lig;
	finalColor.xyz += albedoColor.xyz* directionLight.ambientLight;
	return finalColor;
}
/// <summary>
/// シャドウマップ生成用の頂点シェーダー。
/// </summary>
PSInput_ShadowMap VSMain_ShadowMap(VSInputNmTxVcTangent In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
PSInput_ShadowMap VSMain_ShadowMapSkin(VSInputNmTxWeights In)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos = 0;
	{

		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//最後のボーンを計算する。
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
		pos = mul(skinning, In.Position);


	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;	
	return psInput;
}

float4 PSCubeMain(PSInput In) : SV_Target0
{
	float4 color = skyCubeMap.Sample(Sampler, In.Normal*-1.0f);
	color.xyz *= 1.0f;
	return color;
}
/// <summary>
/// ピクセルシェーダーのエントリ関数。
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//射影空間でのZ値を返す。
	return In.Position.z / In.Position.w;
}