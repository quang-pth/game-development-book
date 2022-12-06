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

struct PointLight {
	vec3 mPosition;
	vec3 mAmbient;
	vec3 mDiffuseColor;
	vec3 mSpecularColor;
	float mSpecularPower;
	float mConstant;
	float mLinear;
	float mQuadratic;
};

#define NR_POINT_LIGHTS 4

uniform vec3 uCameraPos;
uniform vec3 uAmbientLight;
uniform float uSpecularPower;
uniform DirectionalLight uDirLight;
uniform PointLight[NR_POINT_LIGHTS] uPointLights;

void main() {
	vec3 Phong = uAmbientLight;
	vec3 normal = normalize(fragNormal);
	vec3 fragToCamera = normalize(uCameraPos - fragWorldPos);

	// ========== DIRECTIONAL LIGHT =====================
	vec3 fragToDirLight = normalize(-uDirLight.mDirection);
	vec3 reflectDir = normalize(reflect(-fragToDirLight, normal));
	float normalDotFragToDirLight = dot(normal, fragToDirLight);
	if (normalDotFragToDirLight > 0) {
		vec3 diffuseColor = uDirLight.mDiffuseColor * normalDotFragToDirLight;
		vec3 specular = uDirLight.mSpecularColor * pow(max(0, dot(reflectDir, fragToCamera)), uSpecularPower);
		Phong += diffuseColor + specular;
	}
	// ========== DIRECTIONAL LIGHT =====================
	
	// ========== POINT LIGHT =====================
	for (int i = 0; i < NR_POINT_LIGHTS; i++) {
		PointLight pointLight = uPointLights[i];
		vec3 fragToPointLightDir = normalize(pointLight.mPosition - fragWorldPos);
		vec3 diffuseColor = pointLight.mDiffuseColor * max(0, dot(fragToPointLightDir, normal));
			
		vec3 reflectDir = normalize(reflect(-fragToPointLightDir, normal));
		vec3 specularColor = pointLight.mSpecularColor * pow(max(0, dot(reflectDir, fragToCamera)), pointLight.mSpecularPower);
			
		float fragToPointLightDistance = length(pointLight.mPosition - fragWorldPos);
		float attenuation = 1.0 / 
		(pointLight.mConstant + pointLight.mLinear * fragToPointLightDistance + pointLight.mQuadratic * fragToPointLightDistance * fragToPointLightDistance);

		Phong += (pointLight.mAmbient + diffuseColor + specularColor) * attenuation;
	}
	// ========== POINT LIGHT =====================

	FragColor = texture(uTexture, texCoords) * vec4(Phong, 1.0);
}