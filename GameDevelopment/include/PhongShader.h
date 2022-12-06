#pragma once

#include "include/Shader.h"

class PhongShader : public Shader
{
public:
	PhongShader();
	~PhongShader();
	virtual void SetUniforms(class Renderer* renderer) override;
};

