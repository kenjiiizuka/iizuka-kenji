/**
* @file Utility.h
* @brief Utility�֐���錾���Ă���t�@�C��
* @detail �g�p�p�x�̍����A���S���Y����悭�g���W���̊֐������b�v�����֐���錾���Ă���
*/

#pragma once

//---------- INCLUDES ----------
#include <vector>


/** Utility�̊֐���錾�������O��� */
namespace Utility
{
	/**
	* @fn MemCpyAndShiftWritePointer
	* @brief �������R�s�[������ɁA�R�s�[�����T�C�Y���������݈ʒu�������|�C���^��i�߂�
	* @param char*&      (_writePtr)  �f�[�^�������݈ʒu
	* @param const void* (_source)    �������ރf�[�^
	* @param size_t      (_byteSize)  �������݃f�[�^�T�C�Y
	* @return void
	*/
	void MemCpyAndShiftWritePointer(char*& _writePtr, const void* _source, size_t _byteSize);

	/**
	* @fn MemCpyAndShiftReadPointer
	* @brief �������R�s�[������ɓǂݍ��݈ʒu�������|�C���^��i�߂�
	* @param void*  (_destination) �f�[�^�������݈ʒu
	* @param char*& (_readPtr)     �������ރf�[�^
	* @param size_t (_byteSize)    �������݃f�[�^�T�C�Y
	* @return void
	*/
	void MemCpyAndShiftReadPointer(void* _destination, char*& _readPtr, size_t _byteSize);

	/**
	* @fn QuickSort
	* @brief �l���~���ɕ��ׂ�����
	* @detail std::vector<std::pair<float, size_t>>�^�̈����ɂ��āA���בւ������Ƃ�second�̒l�łǂ̂悤�ɕ��בւ����̂��킩��悤�ɂ��Ă���
	*         �N���X�̃����o�̒l�ŕ��בւ������Ƃ��ȂǂɎg���₷�����邽�߂ɂ��̂悤�ɂ��Ă��܂��B
	* @param std::vector<std::pair<float, size_t>>& (_valueAndIndex) �l�Ɣz��Ƃ��Ƃ̔z��̓Y����
	* @param const size_t (_l) �z��̍ŏ��̈ʒu
	* @param const size_t (_r) �z��̍Ō�̈ʒu
	* @return void
	*/
	void QuickSort(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l , const size_t _r);

	/**
	* @fn Partition
	* @brief �N�C�b�N�\�[�g�Ŏ��ۂɒl���r���A����ւ���֐�
	* @param std::vector<std::pair<float, size_t>>& (_valueAndIndex) �l�Ɣz��Ƃ��Ƃ̔z��̓Y����
	* @param const size_t (_l) �z��̍ŏ��̈ʒu
	* @param const size_t (_r) �z��̍Ō�̈ʒu
	* @return size_t �z��̕����ʒu�ƂȂ�l
	*/
	size_t Partition(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l, const size_t _r);

	/**
	* @fn Swap
	* @brief �n���ꂽ�l����בւ���֐�
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

/** �t���[�g�^�̃o�C�g�T�C�Y */
constexpr size_t FLOATBYTESIZE = sizeof(float);

/** size_t�^�̃o�C�g�T�C�Y */
constexpr size_t SIZE_TBYTESIZE = sizeof(size_t);

/** bool�^�̃o�C�g�T�C�Y */
constexpr size_t BOOLBYTESIZE = sizeof(bool);