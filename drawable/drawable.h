#ifndef INCLUDED_DRAWABLE_
#define INCLUDED_DRAWABLE_

#include <glm/glm.hpp>
#include "../shaderprogram/shaderprogram.h"

class Drawable
{
	protected:
		glm::vec3 d_position;
		ShaderProgram *d_shaderProgram;

    public:
    	virtual ~Drawable();
    	Drawable(glm::vec3 position, ShaderProgram *shaderProgram);
    	void draw(glm::mat4 viewProjMat);

    private:
    	virtual void drawImpl(glm::mat4 viewProjMat) = 0;
};
        
#endif
