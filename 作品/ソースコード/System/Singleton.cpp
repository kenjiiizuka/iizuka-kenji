#include "Singleton.h"

// 無名空間に変数を宣言することでStaticなクラスの変数でも隠ぺいできる
namespace 
{
	/** ファイナライザーの最大サイズ */
	constexpr int cMaxFinalizerSize = 256;

	/** 排他制御用 */
	std::mutex gMutex;

	// 現在のファイナライザーの数
	size_t gFinalizersCount = 0;                                      

	/** 破棄関数を格納する配列 */
	SingletonFinalizer::FinalizerFunc gFinalizers[cMaxFinalizerSize];
}


void SingletonFinalizer::AddFinalizer(FinalizerFunc _func)
{
	// マルチスレッドになったときでも排他的に制御できるようにロックをかける
	std::lock_guard<std::mutex> lock(gMutex);

	// サイズを超えていないかチェック
	assert(gFinalizersCount < cMaxFinalizerSize); 

	gFinalizers[gFinalizersCount] = _func;
	gFinalizersCount++;
}

void SingletonFinalizer::Finalize()
{
	// Lockをかける
	std::lock_guard<std::mutex> lock(gMutex); 

	// 逆順にファイナライズを実行
	for (size_t i = gFinalizersCount - 1; (i < cMaxFinalizerSize && i >= 0); i--)
	{
		if (i >= cMaxFinalizerSize)
		{
			continue;
		}
		(*gFinalizers[i])();
	}
	gFinalizersCount = 0;
}
