#version 330 

layout (location = 0) out vec4 FragColor;

in vec2 fragTexCoords;

uniform sampler2D uTexture;

void main() {
	FragColor = texture(uTexture, fragTexCoords);
}