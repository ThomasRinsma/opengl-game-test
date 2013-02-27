#ifndef INCLUDED_DRAWABLE_ENTITY_
#define INCLUDED_DRAWABLE_ENTITY_

#include <glm/glm.hpp> // for glm::mat4
#include "../drawable/drawable.h"
#include "../entity/entity.h"
#include "../shaderprogram/shaderprogram.h"

class DrawableEntity : public Drawable, public Entity
{
	public:
		DrawableEntity(ShaderProgram &shaderProgram);
		virtual ~DrawableEntity();

	private:
		virtual void updateImpl(float deltaTime) = 0;
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};
        
#endif
