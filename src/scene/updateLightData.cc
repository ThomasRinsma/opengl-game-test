#include "scene.ih"
#include <iostream>
void Scene::updateLightData(DrawableEntity *drawableEntity)
{
	// Check if the entity needs lighting at all
	if (not drawableEntity->needsLighting())
		return;

	// Switch to the entity's shader
	ShaderProgram &sp = drawableEntity->shaderProgram();
	sp.use();

	// Sort lights in new vector, ordered by distance to drawableEntity.
	vector<Light *> closestLights(d_lights);
	sort(closestLights.begin(), closestLights.end(),
		[&drawableEntity](Light *a, Light *b)
		{
			return glm::distance(drawableEntity->position(), a->position()) <
				glm::distance(drawableEntity->position(), b->position());
		}
	);

	// Only pass the first
	//     min(s_lightsPerObject, amount of lights)
	// lights to the shader.
	for (size_t idx = 0; idx != s_lightsPerObject and idx != closestLights.size(); ++idx)
	{
		Light &light = *closestLights[idx];

		// Only send data to shader if entity's position changed,
		// or if light's position changed.
		if ((not drawableEntity->positionChanged()) and (not light.positionChanged()))
			continue;

		string lightName = "light" + to_string(idx);

		glUniform3f(sp.uniform(lightName + ".pos"), light.position().x, light.position().y, light.position().z);
		glUniform3f(sp.uniform(lightName + ".color"), light.color.x, light.color.y, light.color.z);
		glUniform3f(sp.uniform(lightName + ".spec"), light.spec.x, light.spec.y, light.spec.z);
		glUniform1f(sp.uniform(lightName + ".constAtt"), light.constAtt);
		glUniform1f(sp.uniform(lightName + ".linAtt"), light.linAtt);
		glUniform1f(sp.uniform(lightName + ".quadAtt"), light.quadAtt);
		glUniform3f(sp.uniform(lightName + ".spotDir"), light.spotDir.x, light.spotDir.y, light.spotDir.z);
		glUniform1f(sp.uniform(lightName + ".spotCutoff"), light.spotCutoff);
		glUniform1f(sp.uniform(lightName + ".spotExp"), light.spotExp);
	}
}


/*
	struct lightData
	{
		vec3 pos;
		vec3 color;
		vec3 spec;
		float constAtt;
		float linAtt;
		float quadAtt;

		vec3 spotDir;
		float spotCutoff;
		float spotExp;
	};
*/