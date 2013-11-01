#ifndef INCLUDED_RESOURCEMANAGER_
#define INCLUDED_RESOURCEMANAGER_

#include <string>
#include <memory>
#include <unordered_map>
#include "model.h"
#include "texture.h"
#include "shaderprogram.h"

// This is a singleton
class ResourceManager
{
	std::unordered_map<std::string, std::unique_ptr<Model>> d_models;
	std::unordered_map<std::string, std::unique_ptr<Texture>> d_textures;
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> d_shaderPrograms;

	std::string const d_resourcePath = "./";
	
	public:
		enum class Type
		{
			MODEL,
			TEXTURE,
			SHADERPROGRAM
		};

		static ResourceManager &instance();

		void loadAll();
		void loadModels();
		void loadTextures();
		void loadShaders();
		void load(ResourceManager::Type type, std::string const &name);

		Model &model(std::string const &name);
		Texture &texture(std::string const &name);
		ShaderProgram &shaderProgram(std::string const &name);

	private:
		// private constructor
		ResourceManager();

		// No copying
		ResourceManager(const ResourceManager &) = delete;
		ResourceManager(const ResourceManager &&) = delete;
		void operator=(ResourceManager const &) = delete;
};

inline Model &ResourceManager::model(std::string const &name)
{
	if (d_models.find(name) == d_models.end())
		throw std::string("requested model '" + name + "' is not loaded.");

	return *d_models[name];
}

inline Texture &ResourceManager::texture(std::string const &name)
{
	if (d_textures.find(name) == d_textures.end())
		throw std::string("requested texture '" + name + "' is not loaded.");

	return *d_textures[name];
}

inline ShaderProgram &ResourceManager::shaderProgram(std::string const &name)
{
	if (d_shaderPrograms.find(name) == d_shaderPrograms.end())
		throw std::string("requested shader program '" + name + "' is not loaded.");

	return *d_shaderPrograms[name];
}
		
#endif
