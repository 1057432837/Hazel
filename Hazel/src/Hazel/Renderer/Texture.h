#pragma once

#include "string"

#include "Hazel/Core/Core.h"

namespace Hazel {
	class Texture
	{
	public:
		Texture();

		virtual ~Texture();

		virtual uint32_t GetWidth() const { return m_Width; }

		virtual uint32_t GetHeight() const { return m_Height; }

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual bool operator == (const Texture& other) const = 0;

		virtual uint32_t GetRendererID() const = 0;

	private:
		uint32_t m_Width;

		uint32_t m_Height;

	};

	class Texture2D : public Texture
	{
	public:
		Texture2D();

		virtual ~Texture2D();

		static Ref<Texture2D> Create(uint32_t width, uint32_t height);

		static Ref<Texture2D> Create(const std::string& path);

	private:

	};

}