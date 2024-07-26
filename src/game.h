#include <SDL2/SDL.h>  
#include <SDL_keycode.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector> 
#include <iostream>
#include "snake.h" 
#include "food.h"
#include "defines.h"

  
// 游戏状态  
class Game {  
private:  
    SDL_Window* window = nullptr;  
    SDL_Renderer* renderer = nullptr;  
    bool running = true;  
    Snake snake; 
    Food food;
  
    void handleKeyEvent(SDL_Event& e,bool flag); 
    bool initSDL();
  
public:  
    Game(); 
    ~Game(); 
    void run();
    void snake_eat_food(Snake& s,Food& f,SDL_Renderer* renderer);
};  
  
