#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override;

		virtual void SetLayout(const BufferLayout& layout) override;

	private:
		uint32_t m_RendererID;

		BufferLayout m_Layout;

	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual uint32_t GetCount() const;

	private:
		uint32_t m_RendererID;

		uint32_t m_Count;

	};

}