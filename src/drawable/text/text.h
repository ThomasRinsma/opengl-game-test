#ifndef INCLUDED_TEXT_
#define INCLUDED_TEXT_


#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Text : public Drawable
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

	std::string d_text;

    public:
        Text(ShaderProgram *shaderProgram, std::string const &text); // TODO: color
        ~Text();

        // TODO: setText()

    private:
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
