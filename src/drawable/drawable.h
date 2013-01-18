#ifndef INCLUDED_DRAWABLE_
#define INCLUDED_DRAWABLE_

#include <glm/glm.hpp>
#include "../shaderprogram/shaderprogram.h"

class Drawable
{
	protected:
        glm::mat4 d_modelMat;
        glm::mat3 d_normalMat;

        glm::vec3 d_position;
        glm::vec3 d_rotation;
        glm::vec3 d_scale;

		ShaderProgram *d_shaderProgram;

    public:
    	virtual ~Drawable();
    	Drawable(ShaderProgram *shaderProgram);

    	void draw(glm::mat4 const &viewMat, glm::mat4 const &projMat);

    	void setPosition(glm::vec3 const &position);
        void setRotation(glm::vec3 const &rotation);
        void setScale(glm::vec3 const &scale);

    	glm::vec3 const &position() const;
        glm::vec3 const &rotation() const;
        glm::vec3 const &scale() const;

    private:
        void updateModelMat();
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};
        
#endif
