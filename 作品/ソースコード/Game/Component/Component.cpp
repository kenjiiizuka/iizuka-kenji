#include "Component.h"

Component::Component()
	: mOwner(nullptr)
	, mbActive(true)
	, mbVisible(true)
	, bIsDestroy(false)
{
	// 処理なし
}

Component::~Component()
{
	// 処理なし
}