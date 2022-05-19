#include "AssTest.h"
#include "../Bindable/BindableBase.h"
#include "../Macros/GraphicsThrowMacros.h"
#include "../Vendor/assimp/Importer.hpp"
#include "../Vendor/assimp/scene.h"
#include "../Vendor/assimp/postprocess.h"
#include "../Vertex.h"

AssTest::AssTest
(
	Graphics& gfx, std::mt19937& rng,
	std::uniform_real_distribution<float>& adist,
	std::uniform_real_distribution<float>& ddist,
	std::uniform_real_distribution<float>& odist,
	std::uniform_real_distribution<float>& rdist,
	DirectX::XMFLOAT3 material,
	float scale
)
	:
	TestObject
	(
		gfx,
		rng,
		adist,
		ddist,
		odist,
		rdist,
		adist
	)
{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		using hw3dexp::VertexLayout;
		hw3dexp::VertexBuffer vBuf
		(
			std::move
			(
				VertexLayout{}
				.Append(VertexLayout::Position3D)
				.Append(VertexLayout::Normal)
			)
		);

		Assimp::Importer importer;
		const auto pModel = importer.ReadFile
		(
			"C:\\Users\\jakub\\source\\repos\\Direct3D\\Direct3D\\Source\\Models\\suzanne.obj",
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices
		);

		const auto pMesh = pModel->mMeshes[0];

		for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
		{
			vBuf.EmplaceBack
			(
					dx::XMFLOAT3{pMesh->mVertices[i].x * scale, pMesh->mVertices[i].y * scale, pMesh->mVertices[i].z * scale},
					*reinterpret_cast<dx::XMFLOAT3*>(&pMesh->mNormals[i])
			);
		}

		std::vector<unsigned short> indices;
		indices.reserve(pMesh->mNumFaces * 3);

		for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
		{
			const auto& face = pMesh->mFaces[i];
			assert(face.mNumIndices == 3);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vBuf));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"PhongVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongPS.cso"));

		AddStaticBind(std::make_unique<InputLayout>(gfx, vBuf.GetLayout().GetD3DLayout(), pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	struct PSMaterialConstant
	{
		DirectX::XMFLOAT3 color;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[3];
	} pmc;
	pmc.color = material;
	AddBind(std::make_unique<PixelConstantBuffer<PSMaterialConstant>>(gfx, pmc, 1u));

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));
}