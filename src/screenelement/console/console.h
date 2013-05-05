#ifndef INCLUDED_CONSOLE_
#define INCLUDED_CONSOLE_

#include <glm/glm.hpp> // for glm::vec3
#include "../screenelement.h"
#include "../../controller/controller.h"
#include "../../drawable/text/text.h"
#include "../../resourcemanager/resourcemanager.h"

class Console : public ScreenElement
{
	Controller const &d_controller;

	Text d_consoleText;

	GLuint d_vbo;
	GLuint d_vao;

	bool d_consoleDown;
	bool d_toggleKeyDown;

    public:
    	Console(Controller const &controller);

    private:
		virtual void updateImpl(float deltaTime);
	    virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);

	    // helper functions for drawImpl()
	    void drawBackground(glm::mat4 const &viewMat, glm::mat4 const &projMat);
	    void drawText(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
        
#endif
