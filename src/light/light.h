#ifndef INCLUDED_LIGHT_
#define INCLUDED_LIGHT_

#include "../entity/entity.h"

struct Light : public Entity
{
	glm::vec3 color;
	glm::vec3 spec;
	float constAtt;
	float linAtt;
	float quadAtt;
	glm::vec3 spotDir;
	float spotCutoff;
	float spotExp;

    public:
        Light(glm::vec3 const &position = glm::vec3(0.0f),
        	  glm::vec3 const &color = glm::vec3(1.0f),
        	  glm::vec3 const &spec = glm::vec3(1.0f),
        	  float constAtt = 0.0f,
        	  float linAtt = 1.0f,
        	  float quadAtt = 0.0f,
        	  glm::vec3 const &spotDir = glm::vec3(0.0f),
        	  float spotCutoff = 130.0f,
        	  float spotExp = 0.0f);

    private:
    	void updateImpl(float deltaTime);
};
        
#endif
