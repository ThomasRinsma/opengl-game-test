#ifndef INCLUDED_TEXT_
#define INCLUDED_TEXT_

#include <glm/glm.hpp>
#include "../drawable.h"
#include "../../texture/texture.h"
#include "../../shaderprogram/shaderprogram.h"


class Text : public Drawable
{
	GLuint d_vbo;
	GLuint d_vao;
	
    Texture &d_texture;

	std::string d_text;

    protected:
        glm::mat4 d_modelMat;

    public:
        Text(std::string const &text = ""); // TODO: color
        ~Text();

        void setText(std::string const &text);

        void setModelMat(glm::mat4 const &modelMat);
        //glm::mat4 const &modelMat() const;

    protected:
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline void Text::setText(std::string const &text)
{
    d_text = text;
}

inline void Text::setModelMat(glm::mat4 const &modelMat)
{
    d_modelMat = modelMat;
}
/*
inline glm::mat4 const &Text::modelMat() const
{
    return d_modelMat;
}
*/      
#endif
