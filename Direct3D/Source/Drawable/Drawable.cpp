#include "Drawable.h"

#include "../Bindable/Bindable.h"
#include "../Bindable/IndexBuffer.h"

DirectX::XMMATRIX Drawable::GetTransfromXM() const noexcept
{
	return DirectX::XMMatrixIdentity();
}

void Drawable::Draw(Graphics& gfx) const noexcept
{
	for(auto& bindable : binds)
	{
		bindable->Bind(gfx);
	}
	for(auto& sBindable : GetStaticBinds())
	{
		sBindable->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void Drawable::Update(float dt) noexcept
{
}

void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept
{
	binds.push_back(std::move(bind));
}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept
{
	pIndexBuffer = ibuf.get();

	binds.push_back(std::move(ibuf));
}
