#include "texture.ih"

Texture::~Texture()
{
	glDeleteTextures(1, &d_tex);
}