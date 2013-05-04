#ifndef INCLUDED_DEBUGTEXT_
#define INCLUDED_DEBUGTEXT_

#include <glm/glm.hpp> // for glm::vec3
#include "../screenelement.h"
#include "../../drawable/text/text.h"

class DebugText : public Text, public ScreenElement
{
	glm::vec3 const &d_coords;
    // TODO: add velocity and/or other stuff
	float d_fps;

    public:
    	DebugText(glm::vec3 const &coords);

    	void setFPS(float fps);

    private:
    	virtual void updateImpl(float deltaTime);
        virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline void DebugText::setFPS(float fps)
{
	d_fps = fps;
}

inline void DebugText::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
    Text::d_modelMat = modelMat(); // set Text's modelMat
    Text::drawImpl(viewMat, projMat);
}

        
#endif
