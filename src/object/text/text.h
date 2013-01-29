#ifndef INCLUDED_TEXT_
#define INCLUDED_TEXT_

#include <glm/glm.hpp>
#include "../object.h"
#include "../../shaderprogram/shaderprogram.h"


class Text : public Object
{
	GLuint d_vbo;
	GLuint d_vao;
	GLuint d_tex;

	std::string d_text;

    public:
        Text(ShaderProgram &shaderProgram, std::string const &text); // TODO: color
        ~Text();

        void setText(std::string const &text);

    private:
        virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &modelMat, glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline void Text::setText(std::string const &text)
{
    d_text = text;
}
        
#endif
