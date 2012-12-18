#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include <SFML/Window.hpp> // for sf::Window
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/glm.hpp> // for glm::mat4

#include "../input/input.h"

class Game
{
    // Keyboard input class
    Input d_input;

    // Flags
    bool d_running = false;
    bool d_initialized = false;

    // SFML stuff
    sf::Window *d_win;
    sf::Clock d_clock;

    // OpenGL stuff
    GLuint d_vertexShader, d_fragmentShader;
    GLuint d_shaderProgram;
    GLuint d_modelMatRef, d_viewMatRef, d_projMatRef;
    glm::mat4 d_modelMat, d_viewMat, d_projMat;

    public:
        Game() = default;
        ~Game();

        void initWindow(size_t width, size_t height);
        void run();

    private:
        // These are directly called from run()
        virtual void initGame();        // initializes game logic
        virtual void initGraphics();    // initializes opengl stuff
        virtual void handleEvents();    // handles events, doh
        virtual void stepGame();        // step game logic
        virtual void draw();            // draw opengl stuff

        // Helper functions
        bool loadShaders(std::string vertPath, std::string fragPath);
};
        
#endif
