#include "include/Texture.h"
#include<SDL2/SDL.h>
#include<GL/glew.h>

Texture::~Texture()
{
}

bool Texture::Load(const std::string& filePath)
{
	int channels = 0;
	unsigned char* image = SOIL_load_image(filePath.c_str(), &mWidth, &mHeight, 
		&channels, SOIL_LOAD_AUTO /*auto for any image type*/);
	
	if (image == nullptr) {
		SDL_Log("Cannot load the image with path: %s", filePath);
		return false;
	}
	
	std::uint16_t format = GL_RGB;
	if (channels == 4) {
		format = GL_RGBA;
	}
	// Copy image to OpenGL
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(image);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}
