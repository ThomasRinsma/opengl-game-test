#include <algorithm>
#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "resourcemanager.h"
#include "scene.h"

using namespace std;

Scene::Scene(Player &player)
:
	d_player(player)
{}

void Scene::update(float deltaTime)
{
	for (auto &pair : d_sceneObjects)
		pair.second->update(deltaTime);

	for (auto &pair : d_portals)
		pair.second->update(deltaTime);

	handleCollisions();
}

void Scene::handleCollisions()
{
	for (auto &pair : d_portals)
	{
		Portal &portal = *pair.second;

		if (glm::distance(d_player.position(), portal.position()) < s_teleportThreshold)
		{
			glm::vec3 relPos = portal.position() - d_player.position();
			d_player.setPosition(portal.destination()->position() + relPos);
			break;
		}
	}
}

void Scene::add(string const name, SceneObject *object)
{
	// TODO: sort based on shader program, texture, etc? Maybe some sort of tree
	d_sceneObjects[name] = unique_ptr<SceneObject>(object);
}

void Scene::add(string const name, Portal *portal)
{
	d_portals[name] = unique_ptr<Portal>(portal);
}

void Scene::add(string const name, Light *light)
{
	d_lights[name] = unique_ptr<Light>(light);
}

void Scene::add(string const name, Collidable *collidable)
{
	d_collidables[name] = unique_ptr<Collidable>(collidable);
}

void Scene::draw()
{
	// Start the recursion
	size_t maxRecursionLevel = 5;
	drawRecursivePortals(d_player.viewMat(), d_player.projMat(), maxRecursionLevel);
}


void Scene::drawNonPortals(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	// Draw all objects that aren't portals
	for (auto &pair : d_sceneObjects)
	{
		updateLightData(*pair.second);
		pair.second->draw(viewMat, projMat);
	}
}

void Scene::drawRecursivePortals(glm::mat4 const &viewMat, glm::mat4 const &projMat, size_t maxRecursionLevel, size_t recursionLevel)
{
	for (auto &pair : d_portals)
	{
		Portal &portal = *pair.second;

		// Disable color and depth drawing
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		// Disable depth test
		glDisable(GL_DEPTH_TEST);

		// Enable stencil test, to prevent drawing outside
		// region of current portal depth
		glEnable(GL_STENCIL_TEST);

		// Fail stencil test when inside of outer portal
		// (fail where we should be drawing the inner portal)
		glStencilFunc(GL_NOTEQUAL, recursionLevel, 0xFF);

		// Increment stencil value on stencil fail
		// (on area of inner portal)
		glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);

		// Enable (writing into) all stencil bits
		glStencilMask(0xFF);

		// Draw portal into stencil buffer
		portal.draw(viewMat, projMat);
		
		
		// Calculate view matrix as if the player was already teleported
		glm::mat4 destView = viewMat * portal.modelMat()
			* glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f) * portal.orientation())
			* glm::inverse(portal.destination()->modelMat());

		// Base case, render inside of inner portal
		if (recursionLevel == maxRecursionLevel)
		{
			// Enable color and depth drawing
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDepthMask(GL_TRUE);
			
			// Clear the depth buffer so we don't interfere with stuff
			// outside of this inner portal
			glClear(GL_DEPTH_BUFFER_BIT);

			// Enable the depth test
			// So the stuff we render here is rendered correctly
			glEnable(GL_DEPTH_TEST);

			// Enable stencil test
			// So we can limit drawing inside of the inner portal
			glEnable(GL_STENCIL_TEST);

			// Disable drawing into stencil buffer
			glStencilMask(0x00);

			// Draw only where stencil value == recursionLevel + 1
			// which is where we just drew the new portal
			glStencilFunc(GL_EQUAL, recursionLevel + 1, 0xFF);

			// Draw scene objects with destView, limited to stencil buffer
			// use an edited projection matrix to set the near plane to the portal plane
			drawNonPortals(destView, portal.clippedProjMat(destView, projMat));
			//drawNonPortals(destView, projMat);
		}
		else
		{
			// Recursion case
			// Pass our new view matrix and the clipped projection matrix (see above)
			drawRecursivePortals(destView, portal.clippedProjMat(destView, projMat), maxRecursionLevel, recursionLevel + 1);
		}

		// Disable color and depth drawing
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		// Enable stencil test and stencil drawing
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0xFF);

		// Fail stencil test when inside of our newly rendered
		// inner portal
		glStencilFunc(GL_NOTEQUAL, recursionLevel + 1, 0xFF);

		// Decrement stencil value on stencil fail
		// This resets the incremented values to what they were before,
		// eventually ending up with a stencil buffer full of zero's again
		// after the last (outer) step.
		glStencilOp(GL_DECR, GL_KEEP, GL_KEEP);

		// Draw portal into stencil buffer
		portal.draw(viewMat, projMat);
	}

	// Disable the stencil test and stencil writing
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0x00);

	// Disable color writing
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// Enable the depth test, and depth writing.
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Make sure we always write the data into the buffer
	glDepthFunc(GL_ALWAYS);

	// Clear the depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

	// Draw portals into depth buffer
	for (auto &pair : d_portals)
		pair.second->draw(viewMat, projMat);

	// Reset the depth function to the default
	glDepthFunc(GL_LESS);

	// Enable stencil test and disable writing to stencil buffer
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0x00);

	// Draw at stencil >= recursionlevel
	// which is at the current level or higher (more to the inside)
	// This basically prevents drawing on the outside of this level.
	glStencilFunc(GL_LEQUAL, recursionLevel, 0xFF);

	// Enable color and depth drawing again
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);

	// And enable the depth test
	glEnable(GL_DEPTH_TEST);

	// Draw scene objects normally, only at recursionLevel
	drawNonPortals(viewMat, projMat);

}

void Scene::updateLightData(SceneObject &sceneObject)
{
	// Check if the entity needs lighting at all
	if (not sceneObject.needsLighting())
		return;

	// Switch to the entity's shader
	ShaderProgram &sp = sceneObject.shaderProgram();
	sp.use();

	// Sort lights in new vector, ordered by distance to sceneObject.
	vector<Light *> closestLights;
	for (auto &pair : d_lights)
		closestLights.push_back(pair.second.get());

	sort(closestLights.begin(), closestLights.end(),
		[&sceneObject](Light *a, Light *b)
		{
			return glm::distance(sceneObject.position(), a->position()) <
				glm::distance(sceneObject.position(), b->position());
		}
	);

	// s_lightsPerObject is the maximum number of lights
	// the shader accepts, defined as a constant in the shader.
	for (size_t idx = 0; idx != s_lightsPerObject; ++idx)
	{
		Light &light = *closestLights[idx];
		string lightName = "light[" + to_string(idx) + "]";

		// If there's less lights than s_lightsPerObject, disable them for the shader
		if (idx >= closestLights.size())
		{
			glUniform1i(sp.uniform(lightName + ".enabled"), 0);
			continue;
		}

		// Only send data to shader if entity's position changed,
		// or if light's position changed.
		if ((not sceneObject.positionChanged()) and (not light.positionChanged()))
			continue;

		glUniform1i(sp.uniform(lightName + ".enabled"), 1);
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