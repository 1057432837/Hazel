#include "hzpch.h"

#include "Hazel/Log.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {
	BufferLayout::BufferLayout() {
	
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		CalculateOffsetAndStride();

	}

	std::vector<BufferElement>::iterator BufferLayout::begin() {
		return m_Elements.begin();
	
	}

	std::vector<BufferElement>::iterator BufferLayout::end() {
		return m_Elements.end();

	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const {
		return m_Elements.begin();
	
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const {
		return m_Elements.end();
	
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

	VertexBuffer::~VertexBuffer() {
	
	}

	void VertexBuffer::Bind() const {

	}

	void VertexBuffer::Unbind() const {

	}

	const BufferLayout& VertexBuffer::GetLayout() const {

	}

	void VertexBuffer::SetLayout(const BufferLayout& layout) {

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

	IndexBuffer::~IndexBuffer() {
	
	}

	void IndexBuffer::Bind() const {

	}

	void IndexBuffer::Unbind() const {

	}

	uint32_t IndexBuffer::GetCount() const {

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