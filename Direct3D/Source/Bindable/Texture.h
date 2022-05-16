#pragma once
#include "Bindable.h"


class Texture : public Bindable
{
public:
	Texture(Graphics& gfx, const class Surface& surface);
	void Bind(Graphics& gfx) noexcept override;

protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
};