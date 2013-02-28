#ifndef INCLUDED_DRAWABLE_
#define INCLUDED_DRAWABLE_

#include <glm/glm.hpp> // for glm::mat4
#include "../shaderprogram/shaderprogram.h"

class Drawable
{
    public:
    	virtual ~Drawable();

        void draw(glm::mat4 const &viewMat, glm::mat4 const &projMat);

    private:
        virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};
        
#endif
