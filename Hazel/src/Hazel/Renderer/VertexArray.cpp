#include "hzpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {
	VertexArray::VertexArray() {

	}

	VertexArray::~VertexArray() {

	}

	void VertexArray::Bind() const {

	}

	void VertexArray::Unbind() const {

	}

	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {

	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {

	}

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return CreateRef<OpenGLVertexArray>();

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}