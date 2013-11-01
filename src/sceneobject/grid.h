#ifndef INCLUDED_GRID_
#define INCLUDED_GRID_

#include <glm/glm.hpp>
#include "../sceneobject.h"
#include "../shaderprogram.h"


class Grid : public SceneObject
{
	GLuint d_vbo;
	GLuint d_vao;

	public:
		Grid(); // TODO: color
		~Grid();

	private:
		virtual void updateImpl(float deltaTime);
		virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};
	
#endif
