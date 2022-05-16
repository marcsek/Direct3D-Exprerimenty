#include "PointLight.h"
#include "../Vendor/ImGui/imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	mesh(gfx, radius), cbuf(gfx)
{
	Reset();
}


void PointLight::SpawnConstrolWindow() noexcept
{
	if (ImGui::Begin("Light Control"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &cbData.pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &cbData.pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &cbData.pos.z, -60.0f, 60.0f, "%.1f");

		ImGui::Text("Color Params");
		ImGui::SliderFloat("Intesity", &cbData.diffuseIntensity, 0.01f, 2.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
		ImGui::ColorEdit3("Intesity", &cbData.diffuseColor.x);
		ImGui::ColorEdit3("Ambient", &cbData.ambient.x);
		//ImGui::ColorEdit3("Material", &cbData.materialColor.x);

		ImGui::Text("Fallof");
		ImGui::SliderFloat("Constant", &cbData.attConst, 0.05f, 10.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
		ImGui::SliderFloat("Linear", &cbData.attLin, 0.0001f, 4.0f,"%.4f", ImGuiSliderFlags_Logarithmic);
		ImGui::SliderFloat("Quadratic", &cbData.attQuad, 0.0000001f, 10.0f, "%.7f", ImGuiSliderFlags_Logarithmic);

		//ImGuiSliderFlags

		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void PointLight::Reset() noexcept
{
	cbData =
	{
		{ 0.0f, 0.0f, 0.0f },
		{ 0.15f, 0.15f, 0.15f },
		{ 1.0f, 1.0f, 1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,

	};
}

void PointLight::Draw(Graphics& gfx) const noexcept
{
	mesh.SetPos(cbData.pos);
	mesh.Draw(gfx);
}

void PointLight::Bind(Graphics& gfx, DirectX::FXMMATRIX view) const noexcept
{
	auto dataCopy = cbData;
	const auto pos = DirectX::XMLoadFloat3(&cbData.pos);
	DirectX::XMStoreFloat3(&dataCopy.pos, DirectX::XMVector3Transform(pos, view));
	cbuf.Update(gfx, dataCopy);
	cbuf.Bind(gfx);
}