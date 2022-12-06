#pragma once

#include<GL/glew.h>
#include<string>
#include"include/CustomMath.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();
	bool Load(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	void Unload();
	void SetActive();
public:
	// ============== UNIFORMS ======================
	virtual void SetUniforms(class Renderer* renderer);
	void SetBoolUniform(const char* name, bool value);
	void SetIntUniform(const char* name, int value);
	void SetFloatUniform(const char* name, float value);
	void SetVec2Uniform(const char* name, const Vector2& vec2);
	void SetVec2Uniform(const char* name, float x, float y);
	void SetVec3Uniform(const char* name, const Vector3& vec3);
	void SetVec3Uniform(const char* name, float x, float y, float z);
	void SetVec4Uniform(const char* name, float x, float y, float z, float w);
	void SetMatrix4Uniform(const char* name, const Matrix4& matrix);
	void SetMatrix3Uniform(const char* name, const Matrix3& matrix);
	// ============== UNIFORMS ======================
protected:
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mShaderProgram;
 private:
	bool CompileShader(const std::string& shaderFilePath, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
};
