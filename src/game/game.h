#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include <SFML/Window.hpp> // for sf::Window
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/glm.hpp> // for glm::mat4
#include <vector> // for vector, doh

#include "../controller/controller.h"
#include "../player/player.h"
#include "../drawable/drawable.h"

class Game
{
    // Window stuff, TODO: move to seperate class?
    size_t d_winWidth;
    size_t d_winHeight;

    // SFML window
    sf::Window d_win;

    // Controller (keyboard + mouse)
    Controller d_controller;

    // Player object (camera)
    Player d_player;

    // Drawable objects
    std::vector<Drawable*> d_drawables;

    // Vector of shader program pointers
    std::vector<ShaderProgram *> d_shaderPrograms;

    // Projection matrix
    glm::mat4 d_projMat;

    // Flags
    bool d_running = false;
    bool d_fullscreen = false;


    public:
        Game();                              // full screen
        Game(size_t width, size_t height);   // windowed
        ~Game();

        void run();

    private:
        void initWindow();
        void initGame();        // initializes game logic
        void initGraphics();    // initializes opengl stuff

        // These are directly called from run()
        void handleEvents();    // handles events, doh
        void stepGame();        // step game logic
        void draw();            // draw opengl stuff
};
        
#endif
