#include "light.h"

using namespace std;

Light::Light(glm::vec3 const &position, glm::vec3 const &color, glm::vec3 const &spec,
			  float constAtt, float linAtt, float quadAtt,
			  glm::vec3 const &spotDir, float spotCutoff, float spotExp)
:
	Entity(position),
	color(color),
	spec(spec),
	constAtt(constAtt),
	linAtt(linAtt),
	quadAtt(quadAtt),
	spotDir(spotDir),
	spotCutoff(spotCutoff),
	spotExp(spotExp)
{}

void Light::updateImpl(float deltaTime)
{

}