#include "hzpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel {
	Shader::Shader() {

	}

	Shader::~Shader() {

	}

	void Shader::Bind() const {

	}

	void Shader::Unbind() const {

	}

	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return MakeRef<OpenGLShader>(filepath);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: {
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;

		}

		case RendererAPI::API::OpenGL: {
			return MakeRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

		}

		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

	ShaderLibrary::ShaderLibrary() {
		
	}

	ShaderLibrary::~ShaderLibrary() {

	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);

	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		HZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;

	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;

	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;

	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		HZ_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];

	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();

	}

}