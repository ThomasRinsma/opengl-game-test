#include <iostream>
#include <dirent.h>
#include "resourcemanager.h"

using namespace std;

ResourceManager::ResourceManager()
{}

ResourceManager &ResourceManager::instance()
{
	// guaranteed to be destroyed,
	// instantiated on first use
	static ResourceManager instance;

	return instance;
}

void ResourceManager::loadAll()
{
	loadModels();
	loadTextures();
	loadShaders();
}

void ResourceManager::loadModels()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "models").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and name.substr(name.length()-3, 3) == "obj")
				load(Type::MODEL, name);
		}
		closedir(dir);
	}
	else
		throw string("model folder not found at '" + d_resourcePath + "models'.");
}

void ResourceManager::loadShaders()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "shaders").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and ent->d_type == DT_DIR)
				load(Type::SHADERPROGRAM, name);
		}
		closedir(dir);
	}
	else
		throw string("shaders folder not found at '" + d_resourcePath + "shaders'.");
}

void ResourceManager::loadTextures()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "textures").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and name.substr(name.length()-3, 3) == "png")
				load(Type::TEXTURE, name);
		}
		closedir(dir);
	}
	else
		throw string("texture folder not found at '" + d_resourcePath + "textures'.");
}

void ResourceManager::load(ResourceManager::Type type, std::string const &name)
{
	switch (type)
	{
		case Type::MODEL:
		{
			if (d_models.find(name) != d_models.end())
				throw string("already loaded the model '" + name + "'.");

			Model *model = new Model(d_resourcePath + "models/" + name);
			d_models.emplace(name.substr(0, name.length() - 4), unique_ptr<Model>(model));
			cout << "Loaded model '" << name.substr(0, name.length() - 4) << "'" << endl;
		}
		break;

		case Type::TEXTURE:
		{
			if (d_textures.find(name) != d_textures.end())
				throw string("already loaded the texture '" + name + "'.");

			Texture *texture = new Texture(d_resourcePath + "textures/" + name);
			d_textures.emplace(name.substr(0, name.length() - 4), unique_ptr<Texture>(texture));
			cout << "Loaded texture '" << name.substr(0, name.length() - 4) << "'" << endl;
		}
		break;

		case Type::SHADERPROGRAM:
		{
			if (d_shaderPrograms.find(name) != d_shaderPrograms.end())
				throw string("already loaded the shader program '" + name + "'.");

			ShaderProgram *shaderProgram = new ShaderProgram(d_resourcePath + "shaders/" + name);
			d_shaderPrograms.emplace(name, unique_ptr<ShaderProgram>(shaderProgram));
			cout << "Loaded shader program '" << name << "'" << endl;
		}
		break;

		default:
			throw string("invalid resource type given");
	}
}

