#include "texture.ih"

Texture::Texture(std::string const &path)
{
	// Load texture
	glGenTextures(1, &d_tex);
	glBindTexture(GL_TEXTURE_2D, d_tex);

	sf::Image texImage;
	if (not texImage.loadFromFile(path))
		throw string("failed to load texture '" + path + "' from file.");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		texImage.getSize().x, texImage.getSize().y, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, texImage.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
