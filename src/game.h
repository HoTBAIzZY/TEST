#include <SDL2/SDL.h>  
#include <SDL_keycode.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector> 
#include <iostream>
#include "snake.h" 
#include "food.h"
#include "defines.h"
  
// ... (假设Snake类和SnakePart结构体已经定义)  
  
// 游戏状态  
class Game {  
private:  
    SDL_Window* window = nullptr;  
    SDL_Renderer* renderer = nullptr;  
    bool running = true;  
    Snake snake; // 假设Snake类已经定义，并且具有move和render方法  
    Food food;
    // 处理键盘事件以更新蛇的方向  
    void handleKeyEvent(SDL_Event& e) {  
        switch (e.key.keysym.sym) {  
            case SDLK_LEFT:  
                if (snake.getCurrentDirection() != Direction::RIGHT) {  
                    snake.setDirection(Direction::LEFT);  
                }  
                break;  
            case SDLK_RIGHT:  
                if (snake.getCurrentDirection() != Direction::LEFT) {  
                    snake.setDirection(Direction::RIGHT);  
                }  
                break;  
            case SDLK_UP:  
                if (snake.getCurrentDirection() != Direction::DOWN) {  
                    snake.setDirection(Direction::UP);  
                }  
                break;  
            case SDLK_DOWN:  
                if (snake.getCurrentDirection() != Direction::UP) {  
                    snake.setDirection(Direction::DOWN);  
                }  
                break;  
            default:  
                break;  
        }  
    }  
    
    bool initSDL() {  
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {  
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;  
            return false;  
        }  
  
        window = SDL_CreateWindow("Snake Game",  
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);  
        if (window == nullptr) {  
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;  
            return false;  
        }  
  
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  
        if (renderer == nullptr) {  
            SDL_DestroyWindow(window);  
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;  
            return false;  
        }  

  
        return true;  
    }  
  
public:  
    Game() {  
        if (!initSDL()) {  
            // 如果初始化失败，你可能想要在这里做一些清理工作，但在这，我们直接让程序崩溃  
            std::cerr << "Failed to initialize SDL and create window/renderer!" << std::endl;  
            exit(EXIT_FAILURE);  
        }    
    }  
  
    ~Game() {  
        // 销毁窗口、渲染器和退出SDL（省略）
            // 释放资源并退出  
        SDL_DestroyRenderer(renderer);  
        SDL_DestroyWindow(window);  
        SDL_Quit();  
    }  
  
    void run() {  
        SDL_Event e;  
        while (running) {  
            while (SDL_PollEvent(&e)) {  
                if (e.type == SDL_QUIT) {  
                    running = false;  
                } else if (e.type == SDL_KEYDOWN) {  
                    handleKeyEvent(e);   
                }  
                // 处理其他事件（省略）  
            }  
  
            // 更新游戏状态（移动蛇等）  
           int collision=snake.move(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE);  
                /* 需要屏幕大小、蛇身体宽度/高度等参数 */
            if(collision==0){
                 snake_eat_food(snake, food, renderer);
            // 渲染游戏到屏幕  
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // 清除屏幕为白色  
            SDL_RenderClear(renderer);  
            snake.render(renderer);  
            food.Draw(renderer);
            SDL_RenderPresent(renderer);  

            
            // 简单的速度控制  
            SDL_Delay(400); 
            }else{
                //在屏幕输出游戏结束信息
                std::cout << "game over" << std::endl;
                running=false;
            }
               
            
                
            
            
            
        }  
    }  
    void snake_eat_food(Snake& s,Food& f,SDL_Renderer* renderer){
        if(s.getx() == f.getCenterX() && s.gety() == f.getCenterY()){
            //蛇身变长1
            s.addone(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE);
            //生成新食物 
            f.getnewfood();           
            f.Draw(renderer);        
            // 更新屏幕  
            SDL_RenderPresent(renderer);    
        }
    

}
};  
  
// 注意：Snake类需要有一个getCurrentDirection()方法来获取当前方向，  
// 以及一个move()方法来根据当前方向移动蛇（这个方法将处理蛇身的增长和可能的碰撞检测）。  
  
// 在main函数中创建Game对象并调用其run()方法来开始游戏循环。