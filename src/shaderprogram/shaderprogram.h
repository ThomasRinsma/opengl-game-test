#ifndef INCLUDED_SHADERPROGRAM_
#define INCLUDED_SHADERPROGRAM_

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp> // for opengl stuff
#include <unordered_map>
#include <vector>
#include <iosfwd>

struct ShaderProgram
{
	std::unordered_map<std::string, GLint> uniforms;

	private:
		GLuint d_vertexShader, d_fragmentShader;
	    GLuint d_shaderProgram;

	    bool d_error = false;

    public:
        ShaderProgram(std::string const &shaderPath);

        GLuint attribLocation(std::string const &attrName) const;
        void use() const;

    private:
    	bool loadShaders(std::string const &vertPath, std::string const &fragPath);
    	void linkShaders(std::vector<std::string> const &uniformNames);
};
        
#endif
