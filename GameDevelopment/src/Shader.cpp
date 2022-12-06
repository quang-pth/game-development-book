#include "Shader.h"

#include"include/Renderer.h"
#include<SDL2/SDL.h>
#include<fstream>
#include<sstream>

Shader::Shader() : mVertexShader(), mFragmentShader(), mShaderProgram()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	if (!this->CompileShader(vertexFilePath, GL_VERTEX_SHADER, mVertexShader) ||
		!this->CompileShader(fragmentFilePath, GL_FRAGMENT_SHADER, mFragmentShader)) 
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

	return this->IsValidProgram();
}

void Shader::Unload()
{
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	glDeleteProgram(mShaderProgram);
}

void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::SetUniforms(Renderer* renderer)
{
}

void Shader::SetBoolUniform(const char* name, bool value)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform1i(location, static_cast<int>(value));
}

void Shader::SetFloatUniform(const char* name, float value)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform1f(location, value);
}

void Shader::SetIntUniform(const char* name, int value)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform1i(location, value);
}

void Shader::SetVec2Uniform(const char* name, const Vector2& vec2)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform2fv(location, 1, vec2.GetAsFloatPtr());
}

void Shader::SetVec2Uniform(const char* name, float x, float y)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform2f(location, x, y);
}

void Shader::SetVec3Uniform(const char* name, const Vector3& vec3)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform3fv(location, 1, vec3.GetAsFloatPtr());
}

void Shader::SetVec3Uniform(const char* name, float x, float y, float z)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform3f(location, x, y, z);
}

void Shader::SetVec4Uniform(const char* name, float x, float y, float z, float w)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniform4f(location, x, y, z, w);
}

void Shader::SetMatrix4Uniform(const char* name, const Matrix4& matrix)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_TRUE /*Transpose if use row vectors*/,
		matrix.GetAsFloatPtr());
}

void Shader::SetMatrix3Uniform(const char* name, const Matrix3& matrix)
{
	GLuint location = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix3fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompileShader(const std::string& shaderFilePath, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderStream(shaderFilePath);

	if (shaderStream.is_open()) {
		std::stringstream sstream;
		sstream << shaderStream.rdbuf();
		const std::string& contents = sstream.str();
		const char* shaderSrc = contents.c_str();

		// Create shader
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &shaderSrc, nullptr);
		glCompileShader(outShader);

		if (!this->IsCompiled(outShader)) {
			SDL_Log("Failed to compile shader %s ", shaderFilePath.c_str());
			return false;
		}
	}
	else {
		SDL_Log("Shader file not found: %s ", shaderFilePath.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL compiled failed\n%s,", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("Shader Program is not valid\n%s ", buffer);
		return false;
	}

	return true;
}
