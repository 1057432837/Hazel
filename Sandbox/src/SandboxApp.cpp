#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Hazel.h"
#include "SandboxApp.h"
#include "Hazel/Core/EntryPoint.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"

namespace Hazel {
	ExampleLayer::ExampleLayer() : Layer("Example") {
	/*--------------------------------------------------------------------------------------------------------------*/
		float vertices[3 * 7] = {																					//
			-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,															//
			 0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,															//
			 0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,															//
																													//
		};																											//
																													//
		m_Layout = BufferLayout::Create({																			//
			{ ShaderDataType::Float3, "a_Position" },																//
			{ ShaderDataType::Float4, "a_Color" },																	//
																													//
			});  																									//
																													//
		uint32_t indices[3] = { 0, 1, 2 };																			//
																													//
		std::string vertexSrc = R"(																					//
		#version 330 core																							//
																													//
		layout(location = 0) in vec3 a_Position;																	//
		layout(location = 1) in vec4 a_Color;																		//
																													//
		uniform mat4 u_ViewProjection;																				//
		uniform mat4 u_Transform;																					//
																													//
		out vec3 v_Position;																						//
		out vec4 v_Color;																							//
																													//
		void main() {																								//
			v_Position = a_Position;																				//
			v_Color = a_Color;																						//
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);									//
																													//
		}																											//
																													//
	)";																												//
																													//
		std::string fragmentSrc = R"(																				//
		#version 330 core																							//
																													//
		layout(location = 0) out vec4 color;																		//
																													//
		in vec3 v_Position;																							//
		in vec4 v_Color;																							//
																													//
		void main() {																								//
			color = vec4(v_Position * 0.5 + 0.5, 1.0);																//
			color = v_Color;																						//
																													//
		}																											//
																													//
	)";																												//
																													//
		m_VertexArray = VertexArray::Create();																		//
		m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));											//
		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));							//
		m_Shader = Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);										//
																													//
		m_VertexBuffer->SetLayout(m_Layout);																		//
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);																//
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);																//
																													//
	/*--------------------------------------------------------------------------------------------------------------*/
		float squareVertices[5 * 4] = {																				//
			-0.5f, -0.5f,  0.0f, 0.0f, 0.0f,																		//
			 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,																		//
			 0.5f,  0.5f,  0.0f, 1.0f, 1.0f,																		//
			-0.5f,  0.5f,  0.0f, 0.0f, 1.0f,																		//
																													//
		};																											//
																													//
		m_SquareVBLayout = BufferLayout::Create({																	//
			{ ShaderDataType::Float3, "a_Position" },																//
			{ ShaderDataType::Float2, "a_TexCoord" }																//
																													//
			});																										//
																													//
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };															//
																													//
		std::string flatColorShaderVertexSrc = R"(																	//
		#version 330 core																							//
																													//
		layout(location = 0) in vec3 a_Position;																	//
																													//
		uniform mat4 u_ViewProjection;																				//
		uniform mat4 u_Transform;																					//
																													//
		out vec3 v_Position;																						//
																													//
		void main() {																								//
			v_Position = a_Position;																				//
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);									//
																													//
		}																											//
																													//
	)";																												//
																													//
		std::string flatColorShaderFragmentSrc = R"(																//
		#version 330 core																							//
																													//
		layout(location = 0) out vec4 color;																		//
																													//
		in vec3 v_Position;																							//
																													//
		uniform vec3 u_Color;																						//
																													//
		void main() {																								//
			color = vec4(u_Color, 1.0);																				//
																													//
		}																											//
																													//
	)";																												//
																													//
		m_SquareVA = VertexArray::Create();																			//
		m_SquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));									//
		m_SquareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));					//
		m_FlatColorShader = Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);		//´¿É«
		m_Texture = Texture2D::Create("assets/textures/avatar.jpg");												//
		m_TextureShader = Shader::Create("assets/shaders/Texture.glsl");											//ÎÆÀíÉ«
																													//
		m_SquareVB->SetLayout(m_SquareVBLayout);																	//
		m_SquareVA->SetIndexBuffer(m_SquareIB);																		//
		m_SquareVA->AddVertexBuffer(m_SquareVB);																	//
																													//
		Cast<OpenGLShader>(m_TextureShader)->Bind();																//
		Cast<OpenGLShader>(m_TextureShader)->UploadUniformInt("m_Texture", 0);										//
																													//
	/*--------------------------------------------------------------------------------------------------------------*/
		m_CameraController.reset(new OrthographicCameraController(1280.0f / 720.0f, true));

	}

	ExampleLayer::~ExampleLayer() {

	}

	void ExampleLayer::OnUpdate(Timestep ts) {
		m_CameraController->OnUpdate(ts);

		Renderer::Flush({ 0.1f, 0.1f, 0.1f, 1 });

		Renderer::BeginScene(m_CameraController->GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		Cast<OpenGLShader>(m_FlatColorShader)->Bind();
		Cast<OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);

			}

		}

		m_Texture->Bind();

		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Renderer::EndScene();

	}

	void ExampleLayer::OnImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void ExampleLayer::OnEvent(Event& e) {
		m_CameraController->OnEvent(e);

	};

	Sandbox::Sandbox() : Application("Sandbox") {
		PushLayer(new Sandbox2D());

	}

	Sandbox::~Sandbox() {

	}

	Application* CreateApplication() {
		return new Sandbox();

	}

}