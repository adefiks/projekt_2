/*
!!! Game.h !!!
    * main class for all object in game
*/
#ifndef GAME_H
#define GAME_H

#include "common.h"

// Forward declaration
class ColliderComponent;

//  main class for all object in game
class Game
{
private:
  // SDL window for game
  SDL_Window *window;

  int cnt = 0;

public:
  Game();
  ~Game();

  // initialize for game -> title (game title), xpos,ypos (center), width,height (size of window ), fullscreen (bool)
  void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

  // for handling a events like key input
  void handleEvents();

  // for updating game (position of player, object, enemys etc), and chacking of collisions
  void update();

  // for rendering graphics
  void render();

  // for cleaning the game after escape
  void clean();

  // is game still running (bool)
  bool running() { return isRunning; };

  // main renderer
  static SDL_Renderer *renderer;

  // event handler
  static SDL_Event event;

  // is game running
  static bool isRunning;

  // position for camera
  static SDL_Rect camera;

  // grouping for objects
  enum groupLabels : size_t
  {
    groupMap,
    groupPlayer,
    groupEnemy,
    groupCollider
  };
};

#endif /* GAME_H */