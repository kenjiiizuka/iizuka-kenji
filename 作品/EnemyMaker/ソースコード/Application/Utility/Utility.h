/**
* @file Utility.h
* @brief Utility関数を宣言しているファイル
* @detail 使用頻度の高いアルゴリズムやよく使う標準の関数をラップした関数を宣言している
*/

#pragma once

//---------- INCLUDES ----------
#include <vector>


/** Utilityの関数を宣言した名前空間 */
namespace Utility
{
	/**
	* @fn MemCpyAndShiftWritePointer
	* @brief メモリコピーした後に、コピーしたサイズ分書き込み位置を示すポインタを進める
	* @param char*&      (_writePtr)  データ書き込み位置
	* @param const void* (_source)    書き込むデータ
	* @param size_t      (_byteSize)  書き込みデータサイズ
	* @return void
	*/
	void MemCpyAndShiftWritePointer(char*& _writePtr, const void* _source, size_t _byteSize);

	/**
	* @fn MemCpyAndShiftReadPointer
	* @brief メモリコピーした後に読み込み位置を示すポインタを進める
	* @param void*  (_destination) データ書き込み位置
	* @param char*& (_readPtr)     書き込むデータ
	* @param size_t (_byteSize)    書き込みデータサイズ
	* @return void
	*/
	void MemCpyAndShiftReadPointer(void* _destination, char*& _readPtr, size_t _byteSize);

	/**
	* @fn QuickSort
	* @brief 値を降順に並べかえる
	* @detail std::vector<std::pair<float, size_t>>型の引数にして、並べ替えたあとにsecondの値でどのように並べ替えたのかわかるようにしている
	*         クラスのメンバの値で並べ替えたいときなどに使いやすくするためにこのようにしています。
	* @param std::vector<std::pair<float, size_t>>& (_valueAndIndex) 値と配列ともとの配列の添え字
	* @param const size_t (_l) 配列の最初の位置
	* @param const size_t (_r) 配列の最後の位置
	* @return void
	*/
	void QuickSort(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l , const size_t _r);

	/**
	* @fn Partition
	* @brief クイックソートで実際に値を比較し、入れ替える関数
	* @param std::vector<std::pair<float, size_t>>& (_valueAndIndex) 値と配列ともとの配列の添え字
	* @param const size_t (_l) 配列の最初の位置
	* @param const size_t (_r) 配列の最後の位置
	* @return size_t 配列の分割位置となる値
	*/
	size_t Partition(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l, const size_t _r);

	/**
	* @fn Swap
	* @brief 渡された値を並べ替える関数
	* @param T& (_value1)
	* @param T& (_value2)
	* @return void
	*/
	template<typename T>
	void Swap(T& _value1, T& _value2);

	template<typename T>
	void Swap(T& _value1, T& _value2)
	{
		T temp = _value2;
		_value2 = _value1;
		_value1 = temp;
	}

}

/** フロート型のバイトサイズ */
constexpr size_t FLOATBYTESIZE = sizeof(float);

/** size_t型のバイトサイズ */
constexpr size_t SIZE_TBYTESIZE = sizeof(size_t);

/** bool型のバイトサイズ */
constexpr size_t BOOLBYTESIZE = sizeof(bool);