#version 330

layout (location = 0) out vec4 FragColor;

in vec3 fragNormal;
in vec3 fragWorldPos;
in vec2 texCoords;

uniform sampler2D uTexture;

struct DirectionalLight {
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecularColor;
};

uniform vec3 uCameraPos;
uniform vec3 uAmbientLight;
uniform float uSpecularPower;
uniform DirectionalLight uDirLight;

void main() {
	vec3 normal = normalize(fragNormal);
	vec3 fragToDirLight = normalize(-uDirLight.mDirection);
	vec3 fragToCamera = normalize(uCameraPos - fragWorldPos);
	vec3 reflectDir = normalize(reflect(-fragToDirLight, normal));

	vec3 Phong = uAmbientLight;
	float normalDotFragToDirLight = dot(normal, fragToDirLight);
	if (normalDotFragToDirLight > 0) {
		vec3 diffuseColor = uDirLight.mDiffuseColor * normalDotFragToDirLight;
		vec3 specular = uDirLight.mSpecularColor * pow(max(0, dot(reflectDir, fragToCamera)), uSpecularPower);
		
		Phong += diffuseColor + specular;
	}

	FragColor = texture(uTexture, texCoords) * vec4(Phong, 1.0);
}