/**
* @file GeometryShader.h
* @brief GeometryShaderクラスの定義
*/

#pragma once

//------- INCLUDES ---------
#include "../Shader.h"

/**
* @class GeometryShader
* @brief ジオメトリシェーダークラス
* @detail ジオメトリシェーダーの初期化を行う
*/
class GeometryShader : public Shader
{
public:
	/**
	* コンストラクタ
	* 
	* @param VisualEntity* (_visualEntity) ジオメトリシェーダーを使う描画オブジェクト
	*/
	GeometryShader(VisualEntity* _visualEntity);

	/**
	* デストラクタ
	*/
	~GeometryShader();

private:
	/** 読み込んだシェーダーを管理するためのMap */
	static std::unordered_map<std::string, ID3D11GeometryShader*> mGeometryShaders;

	/** 現在割り当てられているシェーダーの名前 */
	static std::string mCurrentBindShaderName;

	/** 自身が扱うシェーダーのポインタ */
	ID3D11GeometryShader* mGeometryShader;

public:
	/**
	* @fn Uninit
	* @brief 終了処理
	* @return void
	*/
	void Uninit() override;

	/**
	* @fn UpdateBuffer
	* @brief 定数バッファの更新処理
	* @param uint8_t (_dataID) 描画するメッシュID
	* @return void
	*/
	virtual void UpdateBuffer(uint8_t _dataID);

	/**
　　* @fn BindShader
	* @brief シェーダーの割り当て
　　* @return void
　　*/
	void BindShader() override;

	/**
	* @fn Deallocate
	* @brief シェーダーの割り当て解除
	* @return void
	*/
	static void Deallocate();

protected:
	/**
　　* @fn MakeShader
	* @brief シェーダーを作成する
	* @param void* (_pData)
	* @param UINT (_fileSize)
	* @param std::string (_shaderName)
　　* @return HRESULT
　　*/
	HRESULT MakeShader(void* _pData, UINT _fileSize, std::string _shaderName) override;

	/**
　　 * @fn MakeBuffer
	 * @brief 定数バッファ作成関数 リフレクションで読み取ったデータから定数バッファを作成する
	 * @param void* (_pData)
	 * @param UINT (_fileSize)
　　 * @return HRESULT
　　*/
	HRESULT MakeBuffer(void* _pData, UINT _fileSize) override;

	/**
　　* @fn CheckDuplication
	* @brief 二重読み込みチェック
	* @param std::string (_shaderName)
　　* @return bool true 重複なし false 重複
　　*/
	bool CheckDuplication(std::string _shaderName) override;

private:



};

