#pragma once
#include "Bindable.h"
#include "ConstantBuffers.h"
#include "../Drawable/Drawable.h"
#include "DirectXMath.h"

class TransformCbuf : public Bindable
{
private:
	struct Transforms
	{
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX model;
	};

public:
	TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot = 0u);
	void Bind(Graphics& gfx) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<Transforms>> vcbuf;
	const Drawable& parent;
};

