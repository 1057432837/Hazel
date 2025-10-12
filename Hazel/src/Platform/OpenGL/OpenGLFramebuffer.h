#pragma once

#include "Hazel/Renderer/Framebuffer.h"

namespace Hazel {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer();

		virtual ~OpenGLFramebuffer();

		OpenGLFramebuffer(const FramebufferSpecification& spec);

		void Invalidate();

		virtual void Bind() override;
		
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; };

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; };

	private:
		uint32_t m_RendererID;

		uint32_t m_ColorAttachment;

		uint32_t m_DepthAttachment;

		FramebufferSpecification m_Specification;

	};

}