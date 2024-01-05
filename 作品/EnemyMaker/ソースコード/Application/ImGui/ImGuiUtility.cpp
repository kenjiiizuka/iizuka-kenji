//----------- INCLUDES -----------
#include "ImGuiUtility.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "../System/RendererSystem/Renderer.h"
#include "../../Application/Application.h"
#include "../Utility/MathLibrary.h"

void ImGuiUtility::Initialize(const HWND& _windowHandle)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(_windowHandle);
	ImGui_ImplDX11_Init(Renderer::GetInstance().GetDevice(), Renderer::GetInstance().GetDeviceContext());
}

void ImGuiUtility::Uninitialize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiUtility::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();	
}

void ImGuiUtility::Draw()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiUtility::VerticalColorSliderFloat(const std::string& _label, const ImVec2 _size, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format)
{
	// カラーゲージで表示
	// カラー設定
	ImVec4 colorValue = _color.Value;
	ImGui::PushStyleColor(ImGuiCol_FrameBg, {colorValue.x, colorValue.y,colorValue.z, 100});

	ImVec4 addDensity(50.0f * _densityChanges.x, 50.0f * _densityChanges.y, 50.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 130.0f);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, colorValue);

	addDensity = ImVec4(100.0f * _densityChanges.x, 100.0f * _densityChanges.y, 100.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 160.0f);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, colorValue);

	addDensity = ImVec4(130.0f * _densityChanges.x, 130.0f * _densityChanges.y, 130.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 130.0f);
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, colorValue);

	// スライダーの表示
	ImGui::VSliderFloat(_label.c_str(), _size, &_value, _min, _max, _format.c_str());
	ImGui::PopStyleColor(4);
}

void ImGuiUtility::ColorSliderFloat(const std::string& _label, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format)
{
	// カラーゲージで表示
	// カラー設定
	ImVec4 colorValue = _color.Value;
	ImGui::PushStyleColor(ImGuiCol_FrameBg, { colorValue.x, colorValue.y,colorValue.z, 100 });

	ImVec4 addDensity(50.0f * _densityChanges.x, 50.0f * _densityChanges.y, 50.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 130.0f);
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, colorValue);

	addDensity = ImVec4(100.0f * _densityChanges.x, 100.0f * _densityChanges.y, 100.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 160.0f);
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, colorValue);

	addDensity = ImVec4(130.0f * _densityChanges.x, 130.0f * _densityChanges.y, 130.0f * _densityChanges.z, 0.0f);
	colorValue = ImVec4(colorValue.x + addDensity.x, colorValue.y + addDensity.y, colorValue.z + addDensity.z, 130.0f);
	ImGui::PushStyleColor(ImGuiCol_SliderGrab, colorValue);

	// スライダーの表示
	ImGui::SliderFloat(_label.c_str(), &_value, _min, _max, _format.c_str());
	ImGui::PopStyleColor(4);
}

void ImGuiUtility::DragTransform(std::string_view _label, Transform& _transform)
{
	
	float position[3] = {_transform.mPosition.x,_transform.mPosition.y, _transform.mPosition.z };
	float scale[3] = { _transform.mScale.x,_transform.mScale.y, _transform.mScale.z };
	float rotation[3] =
	{ 
		MathLibrary::FloatRadianToDegree(_transform.mRotation.x),
		MathLibrary::FloatRadianToDegree(_transform.mRotation.y),
		MathLibrary::FloatRadianToDegree(_transform.mRotation.z)
	};
	

	std::string positionLabel = "Position";
	positionLabel += _label.data();
		
	std::string rotationLabel = "Rotation";
	rotationLabel += _label.data();

	std::string scaleLabel = "Scale";
	scaleLabel += _label.data();

	ImGui::DragFloat3(positionLabel.c_str(), position);
	ImGui::DragFloat3(rotationLabel.c_str(), rotation);
	ImGui::DragFloat3(scaleLabel.c_str(), scale);

	_transform.mPosition = { position[0],position[1], position[2] };	
	_transform.mScale = { scale[0],scale[1], scale[2] };
	_transform.mRotation = 
	{ 
		MathLibrary::FloatDegreeToRadian(rotation[0]),
		MathLibrary::FloatDegreeToRadian(rotation[1]),
		MathLibrary::FloatDegreeToRadian(rotation[2])
	};
}

void ImGuiUtility::DragFloat(std::string_view _label, float& _value, const float _min, const float _max)
{
	std::string id = _label.data();
	id += "ID";
	ImGui::PushID(id.data());
	ImGui::DragFloat(_label.data(), &_value, _min, _max);
	ImGui::PopID();
}

void ImGuiUtility::Combo(std::string_view _label, std::vector<std::string> _item, int& _current)
{
	int itemCount = static_cast<int>(_item.size());
	std::vector<char*> items(_item.size());
	for (size_t item_i = 0; char*& item : items)
	{
		item = _item[item_i].data();
		item_i++;
	}
	std::string id = _label.data();
	id += "Combo";
	ImGui::PushID(id.c_str());
	ImGui::Combo(_label.data(), &_current, items.data(), itemCount);
	ImGui::PopID();
}

void ImGuiUtility::InputVector2(std::string_view _label, DirectX::SimpleMath::Vector2& _vector)
{
	float value[2] = { _vector.x, _vector.y };
	ImGui::InputFloat2(_label.data(), value);
	_vector.x = value[0];
	_vector.y = value[1];
}

void ImGuiUtility::InputVector3(std::string_view _label, DirectX::SimpleMath::Vector3& _vector)
{
	float value[3] = { _vector.x, _vector.y, _vector.z };
	ImGui::InputFloat3(_label.data(), value);
	_vector.x = value[0];
	_vector.y = value[1];
	_vector.z = value[2];
}

void ImGuiUtility::InputInt(std::string_view _label, uint16_t& _value)
{
	int v = static_cast<int>(_value);
	ImGui::InputInt(_label.data(), &v);
	_value = static_cast<uint16_t>(v);
}
