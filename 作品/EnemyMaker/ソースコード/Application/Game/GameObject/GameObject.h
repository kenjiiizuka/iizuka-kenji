/**
* @file GameObject.h
* @brief GameObjectクラスの定義
*/

#pragma once


//----------- INCLUDES ----------
#include <memory>
#include "../Component/TransformComponent/TransformComponent.h"
#include "../../System/RendererSystem/Shader/Shader.h"


//-------- 前方宣言 ----------
class PrimitiveComponent;

/**
* @class GameObject
* @brief すべてのGameObjectの基底となるクラス
* @detail 子オブジェクトと、Componentを持たせることができる
*/
class GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	GameObject();

	/**
	* デストラクタ
	*/
	virtual ~GameObject();

protected:
	/** このオブジェクトが破棄されるかどうか */
	bool bDestroy;

	/** このオブジェクトが有効か無効かを表す */
	bool bActive;

	/** このオブジェクトを表示するかどうか */
	bool bIsVisible;

	/** デルタタイムをスケーリングする値 この値を変化させることでオブジェクトの時間を変化させることができる */
	double mTimeDilation;

	/** スケーリングされたデルタタイム */
	double mCustomDeltaTime;

	/** トランスフォームコンポーネント */
	std::weak_ptr<TransformComponent> mTransform;

	/** コンポーネントのリスト */
	std::list<std::shared_ptr<Component>> mComponent;

	/** 子オブジェクトのリスト */
	std::list<std::shared_ptr<GameObject>> mChildObject;

	/** 親オブジェクト */
	GameObject* mParent;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @return void
	*/
	virtual void Init(){};

	/**
	 * @fn Uninit
	 * @brief 終了処理
	 * @return void
	*/
	virtual void Uninit(){};

	/**
	 * @fn Update
	 * @brief 更新処理
	 * @return void
	*/
	virtual void Update(const double _deltaTime){};

	/**
	 * @fn Draw
	 * @brief 描画処理
	 * @return void
	*/
	virtual void Draw(){};
	/**
	 * @fn LastUpdate
	 * @brief 最終更新処理
	 * @return void
	*/
	virtual void LastUpdate(){};
	
	/**
	 * @fn InitBase
	 * @brief 初期化処理のベース
	 * @return void
	*/
	inline void InitBase();

	/**
	 * @fn UninitBase
	 * @brief 終了処理のベース
	 * @detail コンポーネントの処理、子オブジェクトの処理、自身の処理をする
	 * @return void
	*/
	void UninitBase();
	
	/**
	 * @fn UpdateBase
	 * @brief 更新処理のベース
	 * @detail コンポーネントの処理、子オブジェクトの処理、自身の処理をする
	 * @param const double (_deltaTime)
	 * @return void
	*/
	void UpdateBase(const double _deltaTime);

	/**
	 * @fn LastUpdateBase
	 * @brief 最終更新処理のベース
	 * @return void
	 * @detail コンポーネントの処理、子オブジェクトの処理、自身の処理をする
	*/
	void LastUpdateBase();
	
	/**
	 * @fn DrawBase
	 * @brief 描画のベース関数
	 * @return void
	 * @detail コンポーネントの描画処理、子オブジェクトの描画処理、自身の描画処理をする
	*/
	void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);
	
	/**
	 * @fn AddComponent
	 * @brief コンポーネントの追加関数
	 * @return std::shared_ptr<T>　追加したコンポーネント
	*/
	template <typename T>
	inline std::shared_ptr<T> AddComponent();
	
	/**
	 * @fn GetComponent
	 * @brief コンポーネントの取得関数
	 * @return std::shared_ptr<T>
	*/
	template<typename T>
	inline std::shared_ptr<T> GetComponent();
	
	/**
	 * @fn GetAllComponent
	 * @brief 指定されたコンポーネントすべての取得関数
	 * @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	inline std::vector<std::shared_ptr<T>> GetAllComponent();

	/**
	 * @fn GetChildComponents
	 * @brief 子オブジェクトのコンポーネントの取得関数
	 * @return std::vector<std::shared_ptr<T>>
	*/
	template<typename T>
	inline std::vector<std::shared_ptr<T>> GetChildComponents();

	/**
	  * @fn AddChildObject
	  * @brief 子オブジェクトの追加関数
	  * @return std::shared_ptr<T> 追加した子オブジェクト	 
	*/
	template<typename T>
	inline std::shared_ptr<T> AddChildObject();
	
	/**
	 * @fn BeginHit
	 * @brief 何かのオブジェクトの当たったときに呼ばれる関数
	 * @param GameObject* 当たったゲームオブジェクト
	 * @return void
	*/
	virtual void BeginHit(GameObject* _hitGameObject, PrimitiveComponent* _hitComponent) {};

public:
	/**
	 * @fn IsVisible
	 * @brief 表示するかどうか返す
	 * @return bool
	*/
	inline bool IsVisible();

	/**
	 * @fn IsActive
	 * @brief 有効か、無効化を返す
	 * @return bool
	*/
	inline bool IsActive();

	/**
	* @fn GetCustomDeltaTime
	* @brief デルタタイムを取得
	* @detail dilationを適応されたDeltaTimeを返している
	* @return double 
	*/
	inline double GetCustomDeltaTime() const noexcept;

	/**
	 * @fn SetPosition
	 * @brief 位置のセッター
	 * @param DirectX::SimpleMath::Vector3 (_pos) 座標
	 * @return void
	*/
	virtual inline void SetPosition(DirectX::SimpleMath::Vector3 _pos);

	/**
	 * @fn SetScale
	 * @brief スケールのセッター
	 * @param DirectX::SimpleMath::Vector3 (_scale) スケール
	 * @return void
	*/
	inline void SetScale(DirectX::SimpleMath::Vector3 _scale);

	/**
	 * @fn SetScale
	 * @brief スケールのセッター
	 * @param float (_scale) スケール
	 * @return void
	*/
	inline void SetScale(float _scale);

	/**
	 * @fn SetRotation
	 * @brief 回転のセッター
	 * @param DirectX::SimpleMath::Vector3 (_rotation) 回転
	 * @return void
	*/
	inline void SetRotation(DirectX::SimpleMath::Vector3 _rotation);

	/**
	 * @fn GetParent
	 * @brief 親オブジェクトのゲッター
	 * @return GameObject* このゲームオブジェクトの親オブジェクト
	*/
	inline GameObject* GetParent();

	/**
	* @fn GetTimeDilation
	* @brief タイムダイレーションをゲットする
	* @return double タイムダイレーション
	*/
	inline double GetTimeDilation() const noexcept;

	/**
	* @fn SetTimeDilation
	* @brief タイムダイレーションをセットする
	* @param const double (_timeDilation)
	* @return void
	*/
	inline void SetTimeDilation(const double _timeDilation) noexcept;

	/**
	* @fn SetActive
	* @brief アクティブフラグのセッター
	* @param const bool (_active) 
	* @return void 
	*/
	inline void SetActive(const bool _active) noexcept;

	/**
	* @fn Destroy
	* @brief 破棄関数
	* @return void
	*/
	inline void Destroy() noexcept;

};

//--------------- INLINES ---------------------

inline bool GameObject::IsVisible()
{
	return bIsVisible && bActive;
}

inline bool GameObject::IsActive()
{
	return bActive;
}

inline double GameObject::GetCustomDeltaTime() const noexcept
{
	return mCustomDeltaTime;
}

inline void GameObject::InitBase()
{
	mTransform = AddComponent<TransformComponent>();
	Init();
}

template <typename T>
inline std::shared_ptr<T> GameObject::AddComponent()
{
	std::shared_ptr<T> component = std::make_shared<T>();
	std::shared_ptr<Component> comp = std::dynamic_pointer_cast<Component>(component);
	comp->SetOwner(this);
	mComponent.push_back(component);
	comp->InitBase();
	return component;
}

template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	for (std::shared_ptr<Component> comp : mComponent)
	{
		if (typeid(*comp.get()) == typeid(T))
		{
			return std::dynamic_pointer_cast<T>(comp);
		}
	}
	return nullptr;
}

template<typename T>
inline std::vector<std::shared_ptr<T>> GameObject::GetAllComponent()
{
	std::vector<std::shared_ptr<T>> components;
	for (std::shared_ptr<Component> comp : mComponent)
	{
		if (typeid(*comp.get()) == typeid(T))
		{
			components.push_back(std::dynamic_pointer_cast<T>(comp));
		}
	}
	return components;
}

template<typename T>
inline std::vector<std::shared_ptr<T>> GameObject::GetChildComponents()
{
	std::vector<std::shared_ptr<T>> components;
	for(std::shared_ptr<GameObject> child : mChildObject)
	{
		std::shared_ptr<T> comp = child->GetComponent<T>();
		if (comp)
		{
			components.push_back(comp);
		}
	}
	return components;
}

template<typename T>
inline std::shared_ptr<T> GameObject::AddChildObject()
{
	std::shared_ptr<T> obj = std::make_shared<T>();
	std::shared_ptr<GameObject> child = std::dynamic_pointer_cast<GameObject>(obj);
	child->mParent = this;
	mChildObject.push_back(obj);
	std::dynamic_pointer_cast<GameObject>(obj)->InitBase();
	return obj;
}

inline void GameObject::SetPosition(DirectX::SimpleMath::Vector3 _pos)
{
	mTransform.lock()->SetPosition(_pos);
}

inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 _scale)
{
	mTransform.lock()->SetScale(_scale);
}

inline void GameObject::SetScale(float _scale)
{
	mTransform.lock()->SetScale(_scale);
}

inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 _rot)
{
	mTransform.lock()->SetRotation(_rot);
}

inline GameObject* GameObject::GetParent()
{
	return mParent;
}

inline double GameObject::GetTimeDilation() const noexcept
{
	return mTimeDilation;
}

inline void GameObject::SetTimeDilation(const double _timeDilation) noexcept
{
	mTimeDilation = _timeDilation;
}

inline void GameObject::SetActive(const bool _active) noexcept
{
	bActive = _active;
}

inline void GameObject::Destroy() noexcept
{
	bDestroy = true;
}
