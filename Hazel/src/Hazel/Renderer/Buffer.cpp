#include "hzpch.h"

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

	Ref<BufferLayout> BufferLayout::Create(const std::initializer_list<BufferElement>& elements) {
		return CreateRef<BufferLayout>(elements);

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

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLVertexBuffer>(size);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLVertexBuffer>(vertices, size);

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

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLIndexBuffer>(indices, count);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}