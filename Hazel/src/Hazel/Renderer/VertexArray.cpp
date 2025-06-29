#include "hzpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {
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

	//const std::vector<Ref<VertexBuffer>>& VertexArray::GetVertexBuffers() const {

	//}

	//const Ref<IndexBuffer>& VertexArray::GetIndexBuffer() const {

	//}

	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return new OpenGLVertexArray();

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}