#include "hzpch.h"

#include "OpenGLShaderType.h"

namespace Hazel {
    GLenum ShaderTypeFromString(const std::string& type) {
        if (type == "vertex") {
            return GL_VERTEX_SHADER;

        }
        if (type == "fragment" || type == "pixel") {
            return GL_FRAGMENT_SHADER;

        }

        HZ_CORE_ASSERT(false, "Unknown shader type!");
        return 0;

    }

}