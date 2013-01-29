#ifndef INCLUDED_OBJECT_
#define INCLUDED_OBJECT_

#include <glm/glm.hpp> // for glm::mat4
#include "../drawable/drawable.h"
#include "../entity/entity.h"
#include "../shaderprogram/shaderprogram.h"

class Object : public Entity, public Drawable
{
	public:
		Object(ShaderProgram &shaderProgram);
		virtual ~Object();

	private:
		virtual void updateImpl(float deltaTime) = 0;
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
		virtual void modelMatUpdated();
};

inline void Object::modelMatUpdated()
{
	// generate Entity's model matrix and
	// set is as ours (Drawable's)
	d_modelMat = modelMat(); 
}
        
#endif
