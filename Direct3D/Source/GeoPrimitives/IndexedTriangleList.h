#pragma once

#include <vector>
#include <DirectXMath.h>

template<class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(std::vector<T> verts_in, std::vector<unsigned short> indices_in)
		:
		vertices(verts_in), indices(indices_in)
	{}

	void Transform(DirectX::FXMMATRIX matrix)
	{
		for(auto& vert : vertices)
		{
			const DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&vert.pos);

			DirectX::XMStoreFloat3
			(
				&vert.pos,
				DirectX::XMVector3Transform(pos, matrix)
			);
		}
	}

public:
	std::vector<T> vertices;
	std::vector<unsigned short> indices;
};