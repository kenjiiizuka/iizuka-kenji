//--------- INCLUDES ---------
#include "DirectX11ViewPort.h"

DirectX11ViewPort::DirectX11ViewPort()
	:mViewPort({})
{
	// èàóùÇ»Çµ
}

DirectX11ViewPort::~DirectX11ViewPort()
{
	// èàóùÇ»Çµ
}

void DirectX11ViewPort::SetupViewPort(const FLOAT _width, const FLOAT _height, const FLOAT _maxDepth, const FLOAT _minDepth, const FLOAT _topLeftX, const FLOAT _topLeftY)
{
	mViewPort.Width = _width;
	mViewPort.Height = _height;
	mViewPort.MaxDepth = _maxDepth;
	mViewPort.MinDepth = _minDepth;
	mViewPort.TopLeftX = _topLeftX;
	mViewPort.TopLeftY = _topLeftY;
}

