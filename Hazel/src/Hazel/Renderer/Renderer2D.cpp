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
		Ref<Shader> FlatColorShader;
		
	}*s_Data;

	Renderer2D::Renderer2D() {

	}

	Renderer2D::~Renderer2D() {

	}

	void Renderer2D::Init() {
		/*------------------------------------------------------------------------------------------------------*/
		s_Data = new Renderer2DStorage();																		//
																												//
		float squareVertices[3 * 4] = {																			//
			-0.5f, -0.5f,  0.0f,																				//
			 0.5f, -0.5f,  0.0f,																				//
			 0.5f,  0.5f,  0.0f,																				//
			-0.5f,  0.5f,  0.0f,																				//
																												//
		};																										//
																												//
		s_Data->QuadBufferLayout = BufferLayout::Create({														//
			{ ShaderDataType::Float3, "a_Position" },															//
																												//
		});																										//
																												//
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };														//
																												//
		s_Data->QuadVertexArray  = VertexArray::Create();														//
		s_Data->QuadVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));				//
		s_Data->QuadIndexBuffer  = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));//
		s_Data->FlatColorShader  = Shader::Create("assets/shaders/FlatColor.glsl");								//
																												//
		s_Data->QuadVertexBuffer->SetLayout(s_Data->QuadBufferLayout);											//
		s_Data->QuadVertexArray->SetIndexBuffer(s_Data->QuadIndexBuffer);										//
		s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);										//
																												//
		/*------------------------------------------------------------------------------------------------------*/

	}

	void Renderer2D::Shutdown() {
		delete s_Data;

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

	}

	void Renderer2D::EndScene() {

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->Bind();
		s_Data->FlatColorShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->FlatColorShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

	}

}