#pragma once

#include "string"

namespace Hazel {
	class Shader
	{
	public:
		Shader();

		virtual ~Shader();

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:

	};

}