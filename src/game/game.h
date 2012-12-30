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
    // Player object (camera)
    Player d_player;

    // Controller (keyboard + mouse)
    Controller *d_controller;

    // Drawable objects
    std::vector<Drawable*> d_drawables;

    // SFML stuff
    sf::Window *d_win;

    // Vector of shader program pointers
    std::vector<ShaderProgram *> d_shaderPrograms;

    // Projection matrix
    glm::mat4 d_projMat;

    // Flags
    bool d_running = false;
    bool d_initialized = false;

    public:
        Game();
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

};
        
#endif
