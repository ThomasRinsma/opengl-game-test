#ifndef INCLUDED_SCREENELEMENT_
#define INCLUDED_SCREENELEMENT_

#include <glm/glm.hpp> // for glm::vec2
#include "../drawable/drawable.h"
#include "../shaderprogram/shaderprogram.h"

class ScreenElement : public Drawable
{
	glm::vec2 d_position; // in pixels?

	public:
		ScreenElement(ShaderProgram &shaderProgram, glm::vec2 const &position);
		virtual ~ScreenElement();

		glm::vec2 const &position() const;
		void setPosition(glm::vec2 const &position);

		void draw();

	private:
		virtual void drawImpl(glm::mat4 const &modelMat, glm::mat4 const &viewMat, glm::mat4 const &projMat) = 0;
};

inline glm::vec2 const &ScreenElement::position() const
{
	return d_position;
}

inline void ScreenElement::setPosition(glm::vec2 const &position)
{
	d_position = position;
}
		
#endif
