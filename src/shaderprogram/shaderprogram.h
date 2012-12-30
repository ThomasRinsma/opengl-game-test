#ifndef INCLUDED_SHADERPROGRAM_
#define INCLUDED_SHADERPROGRAM_

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
        ShaderProgram(std::string shaderName, std::vector<std::string> uniformNames);

        GLuint attribLocation(std::string const &attrName);
        void use();

    private:
    	bool loadShaders(std::string vertPath, std::string fragPath);
    	void linkShaders(std::vector<std::string> &uniformNames);
};
        
#endif
