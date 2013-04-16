#ifndef INCLUDED_SHADERPROGRAM_
#define INCLUDED_SHADERPROGRAM_

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp> // for opengl stuff
#include <unordered_map>
#include <iosfwd>

struct ShaderProgram
{
	private:
		GLuint d_vertexShader, d_fragmentShader;
	    GLuint d_shaderProgram;

        std::unordered_map<std::string, GLuint> d_uniforms;
        std::unordered_map<std::string, GLuint> d_attributes;

    public:
        ShaderProgram(std::string const &shaderPath);

        GLuint attribute(std::string const &attributeName) const;
        GLuint uniform(std::string const &uniformName) const;

        void use() const;

    private:
    	void loadShaders(std::string const &vertPath, std::string const &fragPath);
    	void linkShaders();
};
        
#endif
