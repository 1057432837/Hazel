#pragma once

#include "memory"

#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class VertexArray
	{
	public:
		VertexArray();

		virtual ~VertexArray();

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return std::vector<Ref<VertexBuffer>>(); }

		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return Ref<IndexBuffer>(); }

		static Ref<VertexArray> Create();

	private:

	};

}