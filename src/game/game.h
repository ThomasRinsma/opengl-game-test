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
#include "../object/text/text.h"


class Game
{
    // Window stuff
    size_t d_winWidth;
    size_t d_winHeight;

    // Flags
    bool d_running = false;
    bool d_fullscreen = false;
    bool d_vsync = false;

    // SFML window
    sf::Window d_win;

    // Controller (keyboard + mouse)
    Controller d_controller;

    // Player object (camera)
    Player d_player;

    // Scene objects
    std::vector<Object *> d_objects;

    // Non-entity drawables (screen-space stuff)
    std::vector<Drawable *> d_screenElements;

    // Vector of shader program pointers
    std::vector<ShaderProgram *> d_shaderPrograms;

    // Projection matrices, TODO: put inside player?
    glm::mat4 d_projMat;
    glm::mat4 d_orthoProjMat;
    float d_fov = 45.0f;

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

        void setProjMat(float fov, float near, float far);

        // These are directly called from run()
        void handleEvents();    // handles events, doh
        void stepGame();        // step game logic
        void draw();            // draw opengl stuff
};
        
#endif
