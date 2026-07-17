#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();

		virtual ~OpenGLVertexBuffer();

		OpenGLVertexBuffer(uint32_t size);

		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual const Ref<Hazel::BufferLayout> GetLayout() const { return m_Layout; };

		virtual void SetLayout(const Ref<Hazel::BufferLayout> layout) { m_Layout = layout; };

		virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;

		Ref<Hazel::BufferLayout> m_Layout;

	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer();

		virtual ~OpenGLIndexBuffer();

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;

		uint32_t m_Count;

	};

}