#pragma once
#include "../Graphics.h"
#include <DirectXMath.h>
#include "memory"

class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;

public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransfromXM() const noexcept;

	void Draw(Graphics& gfx) const noexcept;
	virtual void Update(float dt) noexcept;
	virtual ~Drawable() = default;

protected:
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf) noexcept;
	void AddBind(std::unique_ptr<class Bindable> bind) noexcept;

private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;

	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};

