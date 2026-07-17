#include "hzpch.h"

#include "Framebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel {
	FramebufferTextureSpecification::FramebufferTextureSpecification() {

	}

	FramebufferTextureSpecification::FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {
	
	}

	FramebufferAttachmentSpecification::FramebufferAttachmentSpecification() {

	}

	FramebufferAttachmentSpecification::FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification>& attachments) : Attachments(attachments) {

	}

	Ref<FramebufferSpecification> FramebufferSpecification::Create() {
		return CreateRef<FramebufferSpecification>();

	}

	Framebuffer::Framebuffer() {

	}

	Framebuffer::~Framebuffer() {

	}

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: {
				HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;

			}

			case RendererAPI::API::OpenGL: {
				return CreateRef<OpenGLFramebuffer>(spec);

			}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}