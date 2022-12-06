#include "include/BasicShader.h"
#include "include/Renderer.h"
#include "include/Game.h"
#include "include/Camera.h"

BasicShader::BasicShader() : Shader()
{
}

BasicShader::~BasicShader()
{
}

void BasicShader::SetUniforms(Renderer* renderer)
{
	Shader::SetMatrix4Uniform("uViewMatrix", renderer->GetGame()->GetCamera()->GetViewMatrix());
	Shader::SetMatrix4Uniform("uProjectionMatrix", renderer->GetProjectionMatrix());
}
