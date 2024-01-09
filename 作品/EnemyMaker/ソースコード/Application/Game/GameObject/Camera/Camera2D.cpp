//---------- INCLUDES -----------
#include "Camera2D.h"
#include "../../../System/RendererSystem/Renderer.h"
#include "../../../System/RendererSystem/Shader/Shader.h"

void Camera2D::Draw()
{
	DirectX::SimpleMath::Matrix view_projectionData[2];

	DirectX::SimpleMath::Matrix view;
	view = DirectX::SimpleMath::Matrix::Identity;
	view = view.Transpose();

	DirectX::SimpleMath::Matrix projection;
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(Renderer::GetInstance().GetWidth()),	    // ビューボリュームの最小Ｘ
		static_cast<float>(Renderer::GetInstance().GetHeight()),    // ビューボリュームの最小Ｙ
		0.0f,													    // ビューボリュームの最大Ｙ
		0.0f,
		1.0f);
	projection = projection.Transpose();
	view_projectionData[0] = view;
	view_projectionData[0] = projection;
	Shader::WriteView_ProjectionMatrix(&view_projectionData);
}