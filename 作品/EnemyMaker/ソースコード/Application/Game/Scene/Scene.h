/**
* @file Scene.h
* @brief Sceneクラスの定義
*/

#pragma once

//---------- INCLUDES ----------
#include <list>
#include <array>
#include <memory>

//---------------- 前方宣言 -------------
class GameObject;
class CameraManager;


//-------- コンセプト ------------
template<class Object>
concept DrivedObject = std::derived_from<Object, GameObject>;

/* 各レイヤー*/
enum class ELayer : uint8_t
{
	BaseLayer = 0,
	ObjectLayer = 1,
	UILayer = 2,
	CustomLayer = 3,
	LayerMax = 4
};

/**
* @class Scene
* @brief シーンに共通する機能を持ち、すべてのシーンの基底クラスとなる
*/
class Scene
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Scene();

	/**
	* デストラクタ
	*/
	virtual ~Scene();

private:
	/** シーン内で生成したゲームオブジェクトを保持するリスト */
	 std::array<std::list<std::shared_ptr<GameObject>>,static_cast<size_t>(ELayer::LayerMax)> mpGameObjectList;

protected:
	/** カメラを管理するマネージャー */
	std::shared_ptr<CameraManager> mpCameraManager;

public:
	/**
	* @fn InitBase
	* @brief 初期化処理べ―ス
	* @detail シーンのInitを実行し、カメラマネージャーを生成し初期化する
	* @return void
	*/
	void InitBase();

	/**
	* @fn UninitBase
	* @brief 終了処理ベース
	* @detail シーンのUninitを実行し、リストに保持しているゲームオブジェクトを解放する
	* @return void
	*/
	void UninitBase();

	/**
	* @fn UpdateBase
	* @brief 更新処理ベース
	* @detail シーンのUpdateを実行しリストに保持しているゲームオブジェクトの更新処理をする
	* @return void
	*/
	void UpdateBase();

	/**
	* @fn LastUpdateBase
	* @brief 最終更新処理ベース
	* @detail シーンのLastUpdateを実行しリストに保持しているゲームオブジェクトのLastUpdateBaseを実行する
	* @return void
	*/
	void LastUpdateBase();

	/**
	* @fn DrawBase
	* @brief 描画処理ベース
	* @detail シーンのDrawを実行しリストに保持しているゲームオブジェクトのDrawBaseを実行する
	* @return void
	*/
	void DrawBase();

	/**
　　 * @fn Initialize
	 * @brief 初期化処理
　　 * @return void
　　*/
	virtual void Initialize();

	/**
　　 * @fn Uninitialize
	 * @brief 終了処理
　　 * @return void
　　*/
	virtual void Uninitialize();

	/**
　　 * @fn Update
	 * @brief更新処理
　　 * @return void
　　*/
	virtual void Update();

	/**
　　 * @fn Update
	 * @brief 最終更新処理
　　 * @return void
　　*/
	virtual void LastUpdate();

	/**
　　 * @fn Draw
	 * @brief 描画処理
　　 * @return void
　　*/
	virtual void Draw();

	/**
	* @fn AddGameObject
	* @brief ゲームオブジェクトをシーンに追加する
	* @return std::shared_ptr<Object> 追加したオブジェクト
	*/
	template <DrivedObject Object>
	inline std::shared_ptr<Object> AddGameObject(ELayer _layer);

	/**
	* @fn GetGameObject
	* @brief シーンにあるゲームオブジェクトを取得する関数
	* @return std::shared_ptr<Object> GameObject
	*/
	template <DrivedObject Object>
	std::shared_ptr<Object> GetGameObject(ELayer _layer);
	
	/**
	* @fn CameraManager
	* @brief シーンにあるカメラマネージャーを取得する関数
	* @return std::shared_ptr<CameraManager> カメラマネージャー
	*/
	inline std::shared_ptr<CameraManager> GetCameraManager();
};

//----------- INLINES ------------

template <DrivedObject Object>
inline std::shared_ptr<Object> Scene::AddGameObject(ELayer _layer)
{
	std::shared_ptr<Object> gameObject = std::make_shared<Object>();
	std::static_pointer_cast<GameObject>(gameObject)->InitBase();
	mpGameObjectList[(int)_layer].push_back(gameObject);
	return gameObject;
};

template <DrivedObject Object>
std::shared_ptr<Object> Scene::GetGameObject(ELayer _layer)
{
	for (std::shared_ptr<GameObject> obj : mpGameObjectList[(int)_layer])
	{
		if (typeid(*obj) == typeid(Object)) {
			return std::static_pointer_cast<Object>(obj);
		}
	}
	return nullptr;
}

inline std::shared_ptr<CameraManager> Scene::GetCameraManager()
{
	return mpCameraManager;
}