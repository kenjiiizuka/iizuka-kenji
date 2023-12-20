#include "Texture.h"
#include "../../../Utility/StringEncoding.h"
#include "../../../System/RendererSystem/Renderer.h"
#include "../../../Utility/Debug.h"

#pragma comment (lib, "DirectXTex.lib")

Texture::Texture()
	: mResource(nullptr)
{
}

