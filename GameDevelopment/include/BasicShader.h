#pragma once

#include "include/Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader();
	~BasicShader();
	virtual void SetUniforms(class Renderer* renderer) override;
};
