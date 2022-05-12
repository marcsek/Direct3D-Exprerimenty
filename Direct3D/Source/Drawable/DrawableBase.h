#pragma once

#include "Drawable.h"
#include "../Bindable/IndexBuffer.h"

template<class T>
class DrawableBase : public Drawable
{
protected:
	static bool IsStaticInitialized() noexcept
	{
		return !staticBinds.empty();
	}

	static void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept
	{
		staticBinds.push_back(std::move(bind));
	}

	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept
	{
		pIndexBuffer = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}

	void SetIndexFromStatic() noexcept
	{
		for(const auto& sBind : staticBinds)
		{
			if(const auto p = dynamic_cast<IndexBuffer*>(sBind.get()))
			{
				pIndexBuffer = p;
				return;
			}
		}
	}

private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept
	{
		return staticBinds;
	}

private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> DrawableBase<T>::staticBinds;
