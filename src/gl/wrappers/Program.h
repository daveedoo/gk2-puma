#pragma once
#include <gl/glew.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <functional>

namespace GL
{
	class Program
	{
	private:
		static GLuint currentlyUsedProgramID;

	private:
		GLuint ID;

		void Build(Shader* vertexShader, Shader* geometryShader, Shader* fragmentShader);
		void ExecuteUniformVariableOperation(std::string uniformName, std::function<void(GLint)> operation);

	public:
		Program(Shader& vertexShader, Shader& fragmentShader);
		~Program();

		void Use();
		constexpr GLuint GetID() const { return this->ID; };

		void SetMat4(std::string uniformName, glm::mat4 value);
		void SetVec3(std::string uniformName, glm::vec3 value);
		void SetVec4(std::string uniformName, glm::vec4 value);
		void SetInt(std::string uniformName, int value);
		void SetUint(std::string uniformName, unsigned int value);
		void SetFloat(std::string uniformName, float value);
	};
}
