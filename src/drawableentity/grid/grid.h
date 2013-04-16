#ifndef INCLUDED_GRID_
#define INCLUDED_GRID_

#include <glm/glm.hpp>
#include "../drawableentity.h"
#include "../../shaderprogram/shaderprogram.h"


class Grid : public DrawableEntity
{
	GLuint d_vbo;
	GLuint d_vao;

    public:
        Grid(); // TODO: color
        ~Grid();

        virtual bool needsLighting() const;

    private:
    	virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline bool Grid::needsLighting() const
{
	return false;
}
        
#endif
