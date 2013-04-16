#include "resourcemanager.ih"

void ResourceManager::load(ResourceManager::Type type, std::string const &name)
{
	switch (type)
	{
		case Type::MODEL:
		{
			if (d_models.find(name) != d_models.end())
				throw string("already loaded the model '" + name + "'.");

			Model *model = new Model(d_resourcePath + "models/" + name);
			d_models.emplace(name.substr(0, name.length() - 4), shared_ptr<Model>(model));
			cout << "Loaded model '" << name.substr(0, name.length() - 4) << "'" << endl;
		}
		break;

		case Type::TEXTURE:
		{
			if (d_textures.find(name) != d_textures.end())
				throw string("already loaded the texture '" + name + "'.");

			Texture *texture = new Texture(d_resourcePath + "textures/" + name);
			d_textures.emplace(name.substr(0, name.length() - 4), shared_ptr<Texture>(texture));
			cout << "Loaded texture '" << name.substr(0, name.length() - 4) << "'" << endl;
		}
		break;

		case Type::SHADERPROGRAM:
		{
			if (d_shaderPrograms.find(name) != d_shaderPrograms.end())
				throw string("already loaded the shader program '" + name + "'.");

			ShaderProgram *shaderProgram = new ShaderProgram(d_resourcePath + "shaders/" + name);
			d_shaderPrograms.emplace(name, shared_ptr<ShaderProgram>(shaderProgram));
			cout << "Loaded shader program '" << name << "'" << endl;
		}
		break;

		default:
			throw string("invalid resource type given");
	}
}

