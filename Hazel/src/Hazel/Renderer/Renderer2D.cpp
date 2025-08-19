#include "hzpch.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Hazel {
	static struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<IndexBuffer> QuadIndexBuffer;
		Ref<BufferLayout> QuadBufferLayout;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		
	}*s_Data;

	Renderer2D::Renderer2D() {

	}

	Renderer2D::~Renderer2D() {

	}

	void Renderer2D::Init() {
		HZ_PROFILE_FUNCTION();

		/*----------------------------------------------------------------------------------------------------------*/
		s_Data = new Renderer2DStorage();																			//
																													//
		float squareVertices[5 * 4] = {																				//
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,																		//
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,																		//
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,																		//
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f																			//
																													//
		};																											//
																													//
		s_Data->QuadBufferLayout = BufferLayout::Create({															//
			{ ShaderDataType::Float3, "a_Position" },																//
			{ ShaderDataType::Float2, "a_TexCoord" },																//
																													//
		});																											//
																													//
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };															//
																													//
		uint32_t whiteTextureData = 0xffffffff;																		//
																													//
		s_Data->QuadVertexArray   = VertexArray::Create();															//
		s_Data->QuadVertexBuffer  = VertexBuffer::Create(squareVertices, sizeof(squareVertices));					//
		s_Data->QuadIndexBuffer   = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));	//
		s_Data->TextureShader     = Shader::Create("assets/shaders/Texture.glsl");									//
		s_Data->WhiteTexture      = Texture2D::Create(1, 1);														//
																													//
		s_Data->QuadVertexBuffer->SetLayout(s_Data->QuadBufferLayout);												//
		s_Data->QuadVertexArray->SetIndexBuffer(s_Data->QuadIndexBuffer);											//
		s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);											//
		s_Data->TextureShader->Bind();																				//
		s_Data->TextureShader->SetInt("u_Texture", 0);																//
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));											//
																													//
		/*----------------------------------------------------------------------------------------------------------*/

	}

	void Renderer2D::Shutdown() {
		HZ_PROFILE_FUNCTION();

		delete s_Data;

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	}

	void Renderer2D::EndScene() {
		HZ_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor) {
		HZ_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

	}

}