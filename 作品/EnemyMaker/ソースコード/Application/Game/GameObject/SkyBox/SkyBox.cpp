#include "SkyBox.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"
#include "../../../Utility//MathLibrary.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/Shader/PixelShader/TexturePixelShader.h"
#include "../Plane/PlaneObject.h"

using namespace DirectX::SimpleMath;

SkyBox::SkyBox()
{
	// èàóùÇ»Çµ
}

void SkyBox::Init()
{
	SetScale(100.0f);
	// äeñ ÇÃÉ|ÉäÉSÉìÇê∂ê¨
	std::vector<std::string> texFilePath(6);
	texFilePath[0] = "assets/Field/CubeMap/px.png";
	texFilePath[1] = "assets/Field/CubeMap/py.png";
	texFilePath[2] = "assets/Field/CubeMap/pz.png";
	texFilePath[3] = "assets/Field/CubeMap/nx.png";
	texFilePath[4] = "assets/Field/CubeMap/ny.png";
	texFilePath[5] = "assets/Field/CubeMap/nz.png";


	std::vector<Vector3> planePosition(6);
	planePosition[0] = { 1.99f,0.0f,0.0f };
	planePosition[1] = { 0.0f,1.99f,0.0f };
	planePosition[2] = { 0.0f,0.0f,1.99f };
	planePosition[3] = { -1.99f,0.0f,0.0f };
	planePosition[4] = { 0.0f,-1.99f,0.0f };
	planePosition[5] = { 0.0,0.0f,-1.99f };

	std::vector<Vector3> planeRotation(6);

	float fPI = static_cast<float>(PI);
	float rad90 = fPI / 2.0f;
	planeRotation[0] = { -rad90 ,0.0f,rad90};
	planeRotation[1] = { fPI,0.0f,0.0f};
	planeRotation[2] = { -rad90,-fPI,fPI };
	planeRotation[3] = { -rad90,0.0f,-rad90 };
	planeRotation[4] = { 0.0f,0.0f,0.0f };
	planeRotation[5] = { -rad90,0.0f,fPI};

	uint8_t plane_i = 0;

	for (std::string& path : texFilePath) 
	{	
		std::shared_ptr<PlaneObject> plane = AddChildObject<PlaneObject>();
		plane->Init(path, 2, false);
		plane->SetPosition(planePosition[plane_i]);
		plane->SetRotation(planeRotation[plane_i]);
		plane_i++;
	}
}
