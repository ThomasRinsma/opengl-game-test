#ifndef INCLUDED_SCREENELEMENT_
#define INCLUDED_SCREENELEMENT_

#include <glm/glm.hpp> // for glm::mat4
#include "drawable.h"
#include "entity.h"
#include "shaderprogram.h"

class ScreenElement : public Drawable, public Entity
{
	public:
		ScreenElement(ShaderProgram &shaderProgram);
		virtual ~ScreenElement();

		//bool needsLighting() const;

	private:
		virtual void updateImpl(float deltaTime) = 0;
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};
		
#endif
