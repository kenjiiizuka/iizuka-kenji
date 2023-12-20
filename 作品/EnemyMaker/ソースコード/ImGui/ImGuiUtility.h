/**
* @file ImGuiUtility
* @brief ImGuiUtilityクラスの定義
*/
#pragma once

//--------- INCLUDES ---------
#include <Windows.h>
#include <string>
#include "../System/Singleton.h"
#include "../Game/Component/TransformComponent/Transform.h"
#include "imgui.h"


/**
* @class ImGuiUtility
* @brief ImGuiを使いやすいようにラップしたクラス
*/
class ImGuiUtility : public Singleton<ImGuiUtility>
{
	/**----------------------------------------------------------------------------------------------
	* 基底クラスのSingletonクラスからコンストラクタと、デストラクタにアクセスするために必要であり
	* クラス外から生成、破棄できないようにするためにフレンド指定する
	------------------------------------------------------------------------------------------------*/
	friend class Singleton<ImGuiUtility>;

private:
	/**
	* デフォルトコンストラクタ
	*/
	ImGuiUtility()
	{
		// 処理なし
	}

	/**
	* デストラクタ
	*/
	~ImGuiUtility()
	{
		// 処理なし
	}

	/**
	* コピーコンストラクタ
	* コピー禁止のため delete指定
	*/
	ImGuiUtility(const ImGuiUtility&) = delete;

	/**
	* =演算子のオーバーロード
	* 代入禁止のため delete指定
	*/
	void operator=(const ImGuiUtility&) = delete;

public:
	/**
	* @fn Initialize
	* @brief ImGuiの初期化を行う
	* @param const HWND& (_windowHandle) ImGuiを描画したいWindowHandle
	* @return void
	*/
	void Initialize(const HWND& _windowHandle);

	/**
	* @fn Uninitialize
	* @brief ImGuiの終了処理を行う
	* @return void
	*/
	void Uninitialize();

	/**
	* @fn Update
	* @brief ImGuiの更新処理
	* @detail NewFrame関数を呼び出している
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief ImGuiの描画処理
	* @detail ImGuiのレンダリング関数を呼び出している
	* @return void
	*/
	void Draw();

	/**
	 * @fn VerticalColorSliderFloat
	 * @brief カラーつきバーティカルスライダーを表示する
	 * @param const std::string&  (_label)
	 * @param const ImVec2 (_size)
	 * @param float& (_value)
	 * @param const float (_min)
	 * @param const float (_max)
	 * @param const ImColor (_color)
	 * @param const ImVec4 (_densityChanges)
	 * @param const std::string& (_format)
	 * @return void
	*/
	void VerticalColorSliderFloat(const std::string& _label, const ImVec2 _size, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format = "%.3f");

	/**
	 * @fn ColorSliderFloat
	 * @brief カラーつきバーティカルスライダーを表示する
	 * @param const std::string&  (_label)
	 * @param float& (_value)
	 * @param const float (_min)
	 * @param const float (_max)
	 * @param const ImColor (_color)
	 * @param const ImVec4 (_densityChanges)
	 * @param const std::string& (_format)
	 * @return void
	*/
	void ColorSliderFloat(const std::string& _label, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format = "%.3f");

	/**
	* @fn DrawTransform
	* @brief トランスフォームをDragで表示する
	* @param std::string_view (_label)
	* @param Transform& (_transform)
	* @return void
	*/
	void DragTransform(std::string_view _label, Transform& _transform);

	/**
	* @fn DragFloat
	* @brief ImGui::DragFloat をラップし、IDを設定しています
	* @param std::string_view (_label)
	* @param float& (_value)
	* @param const float (_min)
	* @param const float (_max)
	* @return void
	*/
	void DragFloat(std::string_view _label, float& _value, const float _min = 0.0f, const float _max = 0.0f);

	/**
	* @fn ComboEnum
	* @brief ImGui::Comboをラップした関数
	* @param std::string_view (_label)
	* @param std::vector<std::string> (_item)
	* @param int& (_current)
	* @return void 
	*/
	void Combo(std::string_view _label, std::vector<std::string> _item, int& _current);

	/**
	* @fn InputVector2
	* @brief Vector2をInputFloat2で表示できるようにラップ下関数
	* @param std::string_view (_label)
	* @param DirectX::SimpleMath::Vector2& (_vector)
	* @return void
	*/
	void InputVector2(std::string_view _label, DirectX::SimpleMath::Vector2& _vector);
};

