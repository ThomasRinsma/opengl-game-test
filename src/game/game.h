#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include <SFML/Window.hpp> // for sf::Window
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/glm.hpp> // for glm::mat4
#include <vector> // for vector

#include "../controller/controller.h"
#include "../player/player.h"
#include "../drawable/drawable.h"
#include "../drawable/text2d/text2d.h"
#include "../scene/scene.h"


class Game
{
    // Flags
    bool d_fullscreen;
    bool d_paused = true;
    bool d_vsync = false;

    // SFML window
    sf::Window d_win;
    sf::Clock d_timer;

    // Controller (keyboard + mouse)
    Controller d_controller;

    // Player object (camera)
    Player d_player;

    // Scene objects
    Scene d_scene;

    // Non-entity drawables (screen-space stuff)
    std::vector<Drawable *> d_screenElements;

    // Vector of shader program pointers
    std::vector<ShaderProgram *> d_shaderPrograms;

    // TODO: put this in some GUI class
    glm::mat4 d_orthoProjMat;

    // Current fps
    float d_fps;
    Text2D *d_debugText;

    public:
        Game();                              // full screen max res
        Game(size_t width, size_t height);   // windowed
        ~Game();

        void run();

    private:
        void initWindow();
        void initGame();        // initializes game logic
        void initGraphics();    // initializes opengl stuff

        void pause();
        void unpause();

        // These are directly called from run()
        void handleEvents();    // handles events, doh
        void stepGame();        // step game logic
        void draw();            // draw opengl stuff
};


inline void Game::pause()
{
    d_paused = true;
    d_win.setMouseCursorVisible(true);
}

inline void Game::unpause()
{
    d_paused = false;
    d_win.setMouseCursorVisible(false);
}
        
#endif
