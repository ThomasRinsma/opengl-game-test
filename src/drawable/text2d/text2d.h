#ifndef INCLUDED_TEXT2D_
#define INCLUDED_TEXT2D_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../shaderprogram/shaderprogram.h"


class Text2D : public Drawable
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

    glm::vec2 d_position;

	std::string d_text;

    public:
        Text2D(ShaderProgram &shaderProgram, glm::vec2 const &position,
            glm::vec2 const &scale, std::string const &text); // TODO: color
        ~Text2D();

        void setText(std::string const &text);

    private:
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline void Text2D::setText(std::string const &text)
{
    d_text = text;
}
        
#endif
