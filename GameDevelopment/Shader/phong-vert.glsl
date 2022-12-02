#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;

out vec3 fragNormal;
out vec3 fragWorldPos;
out vec2 texCoords;

uniform mat4 uWorldTransform;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main() {
	vec4 worldPos = vec4(inPosition, 1.0) * uWorldTransform;
	fragWorldPos = worldPos.xyz;

	fragNormal = (vec4(inNormal, 0.0) * uWorldTransform).xyz;
	texCoords = inTexCoords;

	gl_Position = worldPos * uViewMatrix * uProjectionMatrix;
}