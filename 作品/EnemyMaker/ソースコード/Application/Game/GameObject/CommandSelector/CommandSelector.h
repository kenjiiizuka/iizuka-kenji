/**
* @file CommandSelector.h
* @brief CommandSelectorクラスの定義
*/

#pragma once

//----------- INCLUDES ----------
#include "../GameObject.h"
#include "../../../System/InputSystem/InputData.h"

//---------- 前方宣言 ----------
class CommandObject;
class SpriteComponent;
class AudioComponent;

/**
* @class CommandSelector
* @brief 登録されたコマンドを選択するクラス
* @detail CommandObjectを登録
*         決定ボタンが押されたときに選択されているコマンドのIDを返す
* 　　　　決定ボタンのデフォルトは[PadのA]
*         IDは登録された順に1から割り振られる
*         選択する用のカーソルも表示されます
*/
class CommandSelector : public GameObject
{
public:
	/**
	* @enum 選択されているIDを示す列挙型
	* @detail マジックナンバーの使用防止の為に定義している
	*          GetSelectCommandIDで帰ってくる値がなにかを判断する際に使うように
	*/
	enum ID : uint8_t
	{
		NoSelect = 0,
		ID_1,
		ID_2,
		Max
	};

	/**
	* デフォルトコンストラクタ
	*/
	CommandSelector();

	/**
	* デストラクタ
	*/
	~CommandSelector();

private:
	/** コマンド */
	std::vector<std::weak_ptr<CommandObject>> mCommands;

	/** 現在選択しているコマンドID */
	ID mCurrentChoiceID;

	/** 選択しているコマンドを示すスプライト */
	std::weak_ptr<SpriteComponent> mCursorSprite;

	/** コマンド決定時の音 */
	std::weak_ptr<AudioComponent> mSelectSE;

	/** カーソル移動時のコマンド */
	std::weak_ptr<AudioComponent> mCursorMoveSE;

	/** 決定ボタン */
	Pad mSelectButton;

public:
	/**
	* @fn Init
	* @brief 初期化
	* @return void
	*/
	void Init();

	/**
	* @fn Update
	* @brief 更新処理
	* @param const double (_deltaTime)
	* @return void
	*/
	void Update(const double _deltaTime);

private:
	/**
	* @fn MoveCursor
	* @brief 指定されたIDのカーソルに移動する
	* @param const ID (_id)
	* @return void
	*/
	void MoveCursor(const ID _id);

public:
	/**
	* @fn AddCommand
	* @brief コマンド追加関数
	* @param const std::shared_ptr<CommandObject>
	* @return void
	*/
	void AddCommand(const std::shared_ptr<CommandObject> _command);

	/**
	* @fn ResetCursorPosition
	* @brief カーソルの位置をリセットする関数
	* @detail カーソルの位置をID0のコマンドにリセットする
	* @return void
	*/
	void ResetCursorPosition();

	/**
	* @fn GetSelectCommand
	* @brief 決定ボタンが押された時に選択されたコマンドIDを返す
	* @detail 決定ボタンが押されていない時は0を返す
	* @return ID 
	*/
	ID GetSelectCommandID() const noexcept;

};

