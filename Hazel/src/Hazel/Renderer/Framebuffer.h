#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel {
	enum class FramebufferTextureFormat
	{
		None = 0,

		RGBA8,

		DEPTH24STENCIL8,

		Depth = DEPTH24STENCIL8

	};

	class FramebufferTextureSpecification
	{
	public:
		FramebufferTextureSpecification();

		FramebufferTextureSpecification(FramebufferTextureFormat format);

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;

	private:

	};

	class FramebufferAttachmentSpecification
	{
	public:
		FramebufferAttachmentSpecification();

		FramebufferAttachmentSpecification(const std::initializer_list<FramebufferTextureSpecification>& attachments);

		std::vector<FramebufferTextureSpecification> Attachments;

	private:

	};

	class FramebufferSpecification
	{
	public:
		uint32_t Width = 0;
		
		uint32_t Height = 0;

		FramebufferAttachmentSpecification Attachments;

		uint32_t Samples = 1;

		bool SwapChainTarget = false;

		static Ref<FramebufferSpecification> Create();

	private:

	};

	class Framebuffer
	{
	public:
		Framebuffer();

		~Framebuffer();

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	private:

	};

}