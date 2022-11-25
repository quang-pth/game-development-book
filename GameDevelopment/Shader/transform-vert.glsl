#version 330 

layout (location = 0) in vec3 inPosition;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;

void main() {
	gl_Position = vec4(inPosition, 1.0) * uWorldTransform * uViewProj;
}