#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Graphics& gfx, const Drawable& parent, UINT slot)
	:
	parent(parent)
{
	if(!vcbuf)
	{
		vcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx, slot);
	}
}

void TransformCbuf::Bind(Graphics& gfx) noexcept
{
	const auto modelView = parent.GetTransfromXM() * gfx.GetCamera();
	const Transforms tf =
	{
		DirectX::XMMatrixTranspose(modelView),
		DirectX::XMMatrixTranspose(
			modelView *
			gfx.GetProjection()
		)
	};
	vcbuf->Update(gfx, tf);

	vcbuf->Bind(gfx);
}

std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::vcbuf;