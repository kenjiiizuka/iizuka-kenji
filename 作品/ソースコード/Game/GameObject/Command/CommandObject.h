/**
* @file CommandObject.h
* @brief CommandObjectクラスの定義
*/

#pragma once

//---------- INCLUDES -----------
#include "../GameObject.h"

//---------- 前方宣言 -----------
class SpriteComponent;

/**
* @class CommandObject
* @brief タイトルやリザルトで表示するコマンド
*/
class CommandObject : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	CommandObject();

	/**
	* デストラクタ
	*/
	~CommandObject();

private:
	/** コマンド表示用スプライト */
	std::weak_ptr<SpriteComponent> mCommandSprite;

public:
	/**
	* @fn Init
	* @brief 初期化処理
	* @detail 使用するスプライトコンポーネントの準備をしている
	* @param const DirectX::SimpleMath::Vector2 (_pos)  スプライトの表示位置
	* @param const DirectX::SimpleMath::Vector2 (_size) スプライトのサイズ
	* @param std::string_view (_filePath) 使用するテクスチャのファイルパス
	* @return void
	*/
	void Init(const DirectX::SimpleMath::Vector2 _pos, const DirectX::SimpleMath::Vector2 _size, std::string_view _filePath);

	/**
	* @fn GetCommandSprite
	* @brief コマンド表示用スプライトを返す
	* @return std::weak_ptr<SpriteComponent>
	*/
	inline std::weak_ptr<SpriteComponent> GetCommandSprite() const noexcept;

};

//---------- INLINES ----------

inline std::weak_ptr<SpriteComponent> CommandObject::GetCommandSprite() const noexcept
{
	return mCommandSprite;
}

