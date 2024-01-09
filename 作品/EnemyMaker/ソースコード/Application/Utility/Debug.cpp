//----------- INCLUDES ------------
#include "Debug.h"

void CoutVector3(DirectX::SimpleMath::Vector3 _vector)
{
	std::cout << " X " << _vector.x << " Y " << _vector.y << " Z " << _vector.z << std::endl;
}

void CoutMatrix(DirectX::SimpleMath::Matrix _matrix)
{
	std::cout
		<< "行列" << std::endl 
		<< _matrix._11 << " " << _matrix._12 << " " << _matrix._13 << " " << _matrix._14 << std::endl
		<< _matrix._21 << " " << _matrix._22 << " " << _matrix._23 << " " << _matrix._24 << std::endl
		<< _matrix._31 << " " << _matrix._32 << " " << _matrix._33 << " " << _matrix._34 << std::endl
		<< _matrix._41 << " " << _matrix._42 << " " << _matrix._43 << " " << _matrix._44 << std::endl;
}

void Cout(std::string _output)
{
	std::cout << _output << std::endl;
}


