#include "hzpch.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "Hazel/Log.h"
#include "OpenGLShader.h"

namespace Hazel {
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
		// Create an empty vertex OpenGLShader handle
		GLuint vertexOpenGLShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexOpenGLShader, 1, &source, 0);

		// Compile the vertex OpenGLShader
		glCompileShader(vertexOpenGLShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(vertexOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex OpenGLShader compilation failure!");

			return;

		}

		// Create an empty fragment OpenGLShader handle
		GLuint fragmentOpenGLShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment OpenGLShader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentOpenGLShader, 1, &source, 0);

		// Compile the fragment OpenGLShader
		glCompileShader(fragmentOpenGLShader);

		glGetShaderiv(fragmentOpenGLShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentOpenGLShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentOpenGLShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the OpenGLShader anymore.
			glDeleteShader(fragmentOpenGLShader);
			// Either of them. Don't leak OpenGLShaders.
			glDeleteShader(vertexOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment OpenGLShader compilation failure!");

			return;

		}

		// Vertex and fragment OpenGLShaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our OpenGLShaders to our program
		glAttachShader(program, vertexOpenGLShader);
		glAttachShader(program, fragmentOpenGLShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetOpenGLShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak OpenGLShaders either.
			glDeleteShader(vertexOpenGLShader);
			glDeleteShader(fragmentOpenGLShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGLShader link failure!");

			return;
		}

		// Always detach OpenGLShaders after a successful link.
		glDetachShader(program, vertexOpenGLShader);
		glDetachShader(program, fragmentOpenGLShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(0);

	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);

	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);

	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);

	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);

	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);

	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);

	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);

	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}

}