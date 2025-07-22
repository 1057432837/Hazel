#include "hzpch.h"

#include "Hazel/Log.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {
	BufferLayout::BufferLayout() {
	
	}

	BufferLayout::~BufferLayout() {

	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		CalculateOffsetAndStride();

	}

	BufferLayout* BufferLayout::Create(const std::initializer_list<BufferElement>& elements) {
		return new BufferLayout(elements);

	}

	void BufferLayout::CalculateOffsetAndStride() {
		uint32_t offset = 0;
		m_Stride = 0;

		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;

		}

	}

	VertexBuffer::VertexBuffer() {

	}

	VertexBuffer::~VertexBuffer() {
	
	}

	void VertexBuffer::Bind() const {

	}

	void VertexBuffer::Unbind() const {

	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return new OpenGLVertexBuffer(vertices, size);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	IndexBuffer::IndexBuffer() {

	}
	
	IndexBuffer::~IndexBuffer() {
	
	}

	void IndexBuffer::Bind() const {

	}

	void IndexBuffer::Unbind() const {

	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return new OpenGLIndexBuffer(indices, size);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}