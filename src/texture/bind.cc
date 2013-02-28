#include "texture.ih"

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, d_tex);
}