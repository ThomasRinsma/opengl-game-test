#ifndef INCLUDED_SCENE_OBJECT_
#define INCLUDED_SCENE_OBJECT_

#include <glm/glm.hpp> // for glm::mat4
#include "../drawable/drawable.h"
#include "../entity/entity.h"
#include "../shaderprogram/shaderprogram.h"

class SceneObject : public Drawable, public Entity
{
	public:
		SceneObject(ShaderProgram &shaderProgram);
		virtual ~SceneObject();

		//virtual bool needsLighting() const;

	private:
		virtual void updateImpl(float deltaTime) = 0;
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};
        
#endif
