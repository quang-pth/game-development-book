#version 330 

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 uViewProj;
uniform mat4 uWorldTransform;

out vec2 fragTexCoords;

void main() {
	fragTexCoords = inTexCoords;
	gl_Position = vec4(inPosition, 1.0) * uWorldTransform * uViewProj;
}