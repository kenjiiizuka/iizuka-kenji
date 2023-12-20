#pragma once
#include <mutex>
#include <cassert>


/** Singletonクラスを破棄するためのクラス */
class SingletonFinalizer final
{
public:
	// 破棄用の関数
	using FinalizerFunc = void(*)();

	/**
　　 * @fn AddFinalizer
	 * @brief Singletonクラス破棄関数を追加する関数
	 * @param FinalizerFunc (_func) 破棄関数
　　 * @return void
　　*/
	static void AddFinalizer(FinalizerFunc _func);

	/**
　　 * @fn Finalize
	 * @brief 登録された破棄関数を登録の逆順に実行する
　　 * @return void
　　*/
	static void Finalize();
};


template <typename Instance>
class Singleton
{
public:
	/**
　　 * @fn GetInstance
	 * @brief インスタンスの取得をする関数 初回のみインスタンスの生成をするCreate関数を呼ぶ
　　 * @return Instance&
　　*/
	static inline Instance& GetInstance();

private:
	/**
　　 * @fn Create
	 * @brief インスタンスの生成関数
　　 * @return void
　　*/
	static void Create();
	
	/**
　　 * @fn Destroy
	 * @brief インスタンスの破棄関数　ファイナライザに登録して使用する
　　 * @return void
　　*/
	static void Destroy();
	
private:
	/** Create関数を一度だけ呼ぶためのフラグ */
	static std::once_flag mInitFlg;

	/** インスタンス */
	static Instance* mInstance;

};

template<typename Instance> std::once_flag Singleton<Instance>::mInitFlg;
template<typename Instance> Instance* Singleton<Instance>::mInstance = nullptr;

//-------------- INLINES ---------------

template<typename Instance>
inline Instance& Singleton<Instance>::GetInstance()
{	
	std::call_once(mInitFlg, Create);
	assert(mInstance);
	return *mInstance;
}

template<typename Instance>
inline void Singleton<Instance>::Create()
{	
	mInstance = new Instance;

	// ファイナライザーに破棄関数を登録
	SingletonFinalizer::AddFinalizer(&Singleton<Instance>::Destroy);	
}

template<typename Instance>
inline void Singleton<Instance>::Destroy()
{
	delete mInstance;
	mInstance = nullptr;
}
