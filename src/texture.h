#ifndef INCLUDED_TEXTURE_
#define INCLUDED_TEXTURE_

#include <GL/gl.h>
#include <string>

class Texture
{
	GLuint d_tex;

	public:
		Texture(std::string const &path);
		~Texture();

		void bind();

	private:
};
		
#endif
