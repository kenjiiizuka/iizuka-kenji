#pragma once
#include "PixelShader.h"

class AssetHandle;

/** セルフシャドウのピクセルシェーダー */
class LightPixelShader : public PixelShader
{
public:
	/**
	* コンストラクタ
	*/
	LightPixelShader(VisualEntity* _entity);

	/**
　　 * @fn UpdateBuffer
	 * @brief 定数バッファの更新(書き込み)
	 * @param uint8_t (_dataID)
　　 * @return void
　　*/
	void UpdateBuffer(uint8_t _dataID) override;

private:
	/** ランプテクスチャー */
	static std::shared_ptr<AssetHandle> mRampTexture;

};

