#include "include/PhongShader.h"
#include "include/Game.h"
#include "include/Renderer.h"
#include "include/Camera.h"

PhongShader::PhongShader()
{
}

PhongShader::~PhongShader()
{
}

void PhongShader::SetUniforms(Renderer* renderer)
{
	renderer->SetLightUniforms(this);
	Shader::SetMatrix4Uniform("uViewMatrix", renderer->GetGame()->GetCamera()->GetViewMatrix());
	Shader::SetMatrix4Uniform("uProjectionMatrix", renderer->GetProjectionMatrix());
}