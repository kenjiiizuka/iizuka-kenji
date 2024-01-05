#include <iostream>
#include "Utility.h"

size_t writingSize = 0;

void Utility::MemCpyAndShiftWritePointer(char*& _writePtr, const void* _source, size_t _byteSize)
{
	// メモリコピー
	std::memcpy(_writePtr, _source, _byteSize);
	_writePtr += _byteSize;

	writingSize += _byteSize;

	if (_byteSize == 1)
	{
		int i = 0;
	}
	std::cout << " 書き込みサイズ " << _byteSize << " 合計書き込みサイズ " << writingSize << std::endl;
}

void Utility::MemCpyAndShiftReadPointer(void* _destination, char*& _readPtr, size_t _byteSize)
{
	std::memcpy(_destination, _readPtr, _byteSize);
	_readPtr += _byteSize;
}

void Utility::QuickSort(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l, const size_t _r)
{
	if (_l < _r)
	{
		size_t pivot = Partition(_valueAndIndex, _l, _r);
		QuickSort(_valueAndIndex, _l, pivot -1);
		QuickSort(_valueAndIndex, pivot + 1, _r);
	}
}

size_t Utility::Partition(std::vector<std::pair<float, size_t>>& _valueAndIndex, const size_t _l, const size_t _r)
{
	size_t pivot = _valueAndIndex[_r].first;
	size_t i = (_l - 1);

	for (size_t j = _l; j < _r; j++) 
	{
		if (_valueAndIndex[j].first >= pivot) 
		{
			i++;
			Swap(_valueAndIndex[i], _valueAndIndex[j]);
		}
	}
	Swap(_valueAndIndex[i + 1], _valueAndIndex[_r]);
	return (i + 1);
}

