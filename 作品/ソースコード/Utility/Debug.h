#pragma once

#include <SimpleMath.h>
#include <iostream>
void CoutVector3(DirectX::SimpleMath::Vector3 _vector);

void CoutMatrix(DirectX::SimpleMath::Matrix _matrix);

void Cout(std::string _output);

template<typename T>
inline void Cout(T _output)
{	
#if defined(DEBUG) || defined(_DEBUG)
	std::cout << _output << std::endl;
#endif 
	//std::cout << _output << std::endl;
}
