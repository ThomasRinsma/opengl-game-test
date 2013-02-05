#ifndef INCLUDED_SCENEOBJECT_
#define INCLUDED_SCENEOBJECT_

#include <glm/glm.hpp> // for glm::mat4
#include "../drawable/drawable.h"
#include "../entity/entity.h"
#include "../shaderprogram/shaderprogram.h"

class SceneObject : public Entity, public Drawable
{
	public:
		SceneObject(ShaderProgram &shaderProgram);
		virtual ~SceneObject();

	private:
		virtual void updateImpl(float deltaTime) = 0;
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
		virtual void modelMatUpdated();
};

inline void SceneObject::modelMatUpdated()
{
	// generate Entity's model matrix and
	// set is as ours (Drawable's)
	d_modelMat = modelMat(); 
}
        
#endif
