#include <SDL2/SDL.h>  
#include <SDL_keycode.h>
#include "snake.h"
#include "defines.h"
#include <iostream>  

  
int main(int argc, char* argv[]) {  
    SDL_Window* window = nullptr;  
    SDL_Renderer* renderer = nullptr;  
    SDL_Event e;  
    bool quit = false;  
  
    // 初始化SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {  
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;  
        return 1;  
    }  
  
    // 创建窗口  
    window = SDL_CreateWindow("SDL2 Game Example",  
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
                              SCREEN_WIDTH, SCREEN_HEIGHT,  
                              SDL_WINDOW_SHOWN);  
    if (window == nullptr) {  
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;  
        SDL_Quit();  
        return 1;  
    }  
  
    // 创建渲染器  
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
    if (renderer == nullptr) {  
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;  
        SDL_DestroyWindow(window);  
        SDL_Quit();  
        return 1;  
    }  
    
  //初始化蛇
   Square s;
  
    // 游戏主循环  
    while (!quit) {  
        // 处理事件  
        while (SDL_PollEvent(&e) != 0) {  
            if (e.type == SDL_QUIT) {  
                quit = true;  
            } else if (e.type == SDL_KEYDOWN) {  
                switch (e.key.keysym.sym) {  
                    case SDLK_UP:  
                        blockY -= 10;  
                        break;  
                    case SDLK_DOWN:  
                        blockY += 10;  
                        break;  
                    case SDLK_LEFT:  
                        blockX -= 10;  
                        break;  
                    case SDLK_RIGHT:  
                        blockX += 10;  
                        break;  
                }




                
            }  
        }  
  
        // 清除屏幕  
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  
        SDL_RenderClear(renderer);  



        // 绘制方块  
        
        s.Draw(renderer);

        // 更新屏幕  
        SDL_RenderPresent(renderer);  
  
        // 控制游戏速度  
        SDL_Delay(10);  
    }  
  
    // 释放资源并退出  
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window);  
    SDL_Quit();  
  
    return 0;  
}