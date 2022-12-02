#version 330 

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;

uniform mat4 uWorldTransform;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec2 fragTexCoords;

void main() {
	fragTexCoords = inTexCoords;
	gl_Position = vec4(inPosition, 1.0) * uWorldTransform * uViewMatrix * uProjectionMatrix;
}