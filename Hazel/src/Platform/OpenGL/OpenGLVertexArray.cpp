#include "hzpch.h"

#include "glad/glad.h"

#include "OpenGLVertexArray.h"

namespace Hazel {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Hazel::ShaderDataType::Float: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Float2: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Float3: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Float4: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Mat3: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Mat4: {
			return GL_FLOAT;

		}

		case Hazel::ShaderDataType::Int: {
			return GL_INT;

		}

		case Hazel::ShaderDataType::Int2: {
			return GL_INT;

		}

		case Hazel::ShaderDataType::Int3: {
			return GL_INT;

		}

		case Hazel::ShaderDataType::Int4: {
			return GL_INT;

		}

		case Hazel::ShaderDataType::Bool: {
			return GL_BOOL;

		}

		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;

	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);

	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);

	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);

	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "vertex buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout->GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout->GetStride(), (const void*)element.Offset);
			index++;

		}

		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

	}

}