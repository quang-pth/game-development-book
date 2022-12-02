#pragma once

#include<GL/glew.h>
#include<string>
#include"include/CustomMath.h"

class Shader
{
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void Unload();
	void SetActive();
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	void SetVec3Uniform(const char* name, const Vector3& vec3);
	void SetFloatUniform(const char* name, float value);
 private:
	bool CompileShader(const std::string& shaderFilePath, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
	// Shader IDs
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mShaderProgram;
};
