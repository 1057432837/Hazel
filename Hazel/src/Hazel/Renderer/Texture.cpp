#include "hzpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel {
	Texture::Texture() {

	}

	Texture::~Texture() {

	}

	void Texture::Bind(uint32_t slot) const {

	}

	Texture2D::Texture2D() {

	}

	Texture2D::~Texture2D() {

	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return MakeRef<OpenGLTexture2D>(path);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}