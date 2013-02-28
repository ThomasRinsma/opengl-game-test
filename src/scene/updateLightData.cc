#include "scene.ih"

void Scene::updateLightData()
{
	// Update light positions (only one now) in all shaders that use lighting (only one now)
	ShaderProgram &sp = ResourceManager::instance().shaderProgram("simpleTexture");
	sp.use();

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
	Light &light = *d_lights[0];
	glUniform3f(sp.uniforms["light.pos"], light.position().x, light.position().y, light.position().z);
	glUniform3f(sp.uniforms["light.color"], light.color.x, light.color.y, light.color.z);
	glUniform3f(sp.uniforms["light.spec"], light.spec.x, light.spec.y, light.spec.z);
	glUniform1f(sp.uniforms["light.constAtt"], light.constAtt);
	glUniform1f(sp.uniforms["light.linAtt"], light.linAtt);
	glUniform1f(sp.uniforms["light.quadAtt"], light.quadAtt);
	glUniform3f(sp.uniforms["light.spotDir"], light.spotDir.x, light.spotDir.y, light.spotDir.z);
	glUniform1f(sp.uniforms["light.spotCutoff"], light.spotCutoff);
	glUniform1f(sp.uniforms["light.spotExp"], light.spotExp);
}