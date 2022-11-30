#version 330 

layout (location = 0) out vec4 FragColor;

in vec3 fragColor;
in vec2 fragTexCoords;

uniform sampler2D uTexture;

void main() {
	vec4 textureColor = texture(uTexture, fragTexCoords);
	vec4 fragColorV4 = vec4(fragColor, 0.0);
	FragColor = (textureColor + fragColorV4) / 2;
}