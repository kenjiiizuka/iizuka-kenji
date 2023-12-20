/**
 * @file Component.h
 * @brief Componentの基底クラス
 */


#pragma once

//---------- INCLUDES -----------
#include <list>
#include <memory>


//------ 前方宣言 ---------
class GameObject;

/**
* @class Component
* @brief すべてのコンポーネントの基底となるクラス
*/
class Component
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Component();

	/**
	* デストラクタ
	*/
	virtual ~Component();

protected:
	/** このコンポーネントを所有しているゲームオブジェクト */
	GameObject* mOwner;

	/** このコンポーネントが有効か */
	bool mbActive;

	/** 可視か不可視か */
	bool mbVisible;

	/** 破壊フラグ */
	bool bIsDestroy; 

public:
	/**
	 * @fn　Init
	 * @brief 初期化処理
	 * @return void
	*/
	virtual void Init(){}

	/**
	 * @fn　Uninit
	 * @brief 終了処理
	 * @return void
	*/
	virtual void Uninit(){}

	/**
	 * @fn　Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update(const double _deltaTime){}

	/**
	 * @fn　LastUpdate
	 * @brief 最終更新処理
	 * @return void
	*/
	virtual void LastUpdate(){}

	/**
	 * @fn　Draw
	 * @brief 描画処理
	 * @return void
	*/
	virtual void Draw(){}
		
	/**
	 * @fn　InitBase
	 * @brief 初期化処理
	 * @return void
	*/
	inline void InitBase();

	/**
	 * @fn　UninitBase
	 * @brief 終了処理
	 * @return void
	*/
	inline void UninitBase();

	/**
	 * @fn　UpdateBase
	 * @brief 更新処理
	 * @return void
	*/
	inline void UpdateBase(const double _deltaTime);

	/**
	 * @fn　LastUpdateBase
	 * @brief すべての更新処理が終ったあとに行う更新処理
	 * @return void
	*/
	inline void LastUpdateBase();

	/**
	 * @fn　DrawBase
	 * @brief 描画に関連する処理
	 * @return void
	*/
	inline void DrawBase();

public:
	/**
	 * @fn　SetOwner
	 * @brief オーナーのゲームオブジェクトのセッター
	 * @param GameObject* (_owner) オーナーになるオブジェクト
	 * @return void
	*/
	inline void SetOwner(GameObject* _owner);

	/**
	* @fn　GetOwner
	* @brief オーナーのゲームオブジェクトのゲッタ-
	* @return GameObject* オーナーのゲームオブジェクト
	*/
	inline GameObject* GetOwner() const;

	/**
	* @fn SetActive
	* @brief アクティブのセッター
	* @param bool (_active) true : 有効  false : 無効
	* @return void
	*/
	inline void SetActive(const bool _active) noexcept;

	/**
    * @fn IsActive
    * @brief このコンポーネントがアクティブなのか
    * @return bool
    */
	inline bool IsActive() const noexcept;

	/**
	* @fn　SetVisible
	* @brief 可視性のセッター
	* @param bool (_visible) true : 可視  false : 不可視
	* @return void
	*/
	inline virtual void SetVisible(const bool _visible) noexcept;

	/**
	* @fn　Destroy
	* @brief 破棄関数
	* @return void
	*/
	inline void Destroy() noexcept;

	/**
	* @fn　GetDestroy
	* @brief 破棄フラグのゲッター
	* @return bool true 破棄 : false 破棄しない
	*/
	inline bool IsDestroy() const noexcept;
};

//-------------------- INLINES ------------------

inline void Component::InitBase()
{
	Init();
}

inline void Component::UninitBase()
{
	Uninit();
}

inline void Component::UpdateBase(const double _deltaTime)
{
	if (mbActive) 
	{
		Update(_deltaTime);
	}	
}

inline void Component::LastUpdateBase()
{
	if (mbActive)
	{
		LastUpdate();
	}
}

inline void Component::DrawBase()
{
	if (mbVisible)
	{
		Draw();
	}	
}

inline void Component::SetOwner(GameObject* _owner)
{
	mOwner = _owner;
}

inline GameObject* Component::GetOwner() const
{
	return mOwner ? mOwner : nullptr;
}

inline void Component::SetActive(bool _active) noexcept
{
	mbActive = _active;
}

inline bool Component::IsActive() const noexcept
{
	return mbActive;
}

inline void Component::SetVisible(bool _visible) noexcept
{
	mbVisible = _visible;
}

inline void Component::Destroy() noexcept
{
	bIsDestroy = true;
}

inline bool Component::IsDestroy() const noexcept
{
	return bIsDestroy;
}