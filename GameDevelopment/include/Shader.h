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
 private:
	bool CompileShader(const std::string& shaderFilePath, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
	// Shader IDs
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mShaderProgram;
};
