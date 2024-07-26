#include "game.h"

// ... (假设Snake类和SnakePart结构体已经定义)

// 游戏状态
void Game::handleKeyEvent(SDL_Event &e, bool flag) {
  switch (e.key.keysym.sym) {
  case SDLK_LEFT:
    if (snake.getCurrentDirection() != Direction::RIGHT && flag) {
      snake.setDirection(Direction::LEFT);
    }
    break;
  case SDLK_RIGHT:
    if (snake.getCurrentDirection() != Direction::LEFT && flag) {
      snake.setDirection(Direction::RIGHT);
    }
    break;
  case SDLK_UP:
    if (snake.getCurrentDirection() != Direction::DOWN && flag) {
      snake.setDirection(Direction::UP);
    }
    break;
  case SDLK_DOWN:
    if (snake.getCurrentDirection() != Direction::UP && flag) {
      snake.setDirection(Direction::DOWN);
    }
    break;
  default:
    break;
  }
}

bool Game::initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    SDL_DestroyWindow(window);
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    return false;
  }

  return true;
}

Game::Game() {
  if (!initSDL()) {
    // 如果初始化失败，让程序崩溃
    std::cerr << "Failed to initialize SDL and create window/renderer!"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

Game::~Game() {
  // 销毁窗口、渲染器和退出SDL
  // 释放资源并退出
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::run() {
  SDL_Event e;
  bool flag = true; // 上一次的方向  有没有需要添加的方块
  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = false;
      } else if (e.type == SDL_KEYDOWN) {
        handleKeyEvent(e, flag);
        flag = false;
      }
    }

    // 更新游戏状态（移动蛇等）
    int collision =
        snake.move(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE);
    /* 需要屏幕大小、蛇身体宽度/高度等参数 */
    if (collision == 0) {
      snake_eat_food(snake, food, renderer);
      // 渲染游戏到屏幕
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF,
                             0xFF); // 清除屏幕为白色
      SDL_RenderClear(renderer);
      snake.render(renderer);
      food.Draw(renderer);
      SDL_RenderPresent(renderer);

      // 简单的速度控制
      SDL_Delay(200);

      flag = true; // 标记是否蛇体更新完成
    } else {
      // 在屏幕输出游戏结束信息
      std::cout << "Game over!You hit the edge or yourself！" << std::endl;
      running = false;
    }
  }
}
void Game::snake_eat_food(Snake &s, Food &f, SDL_Renderer *renderer) {
  if (s.getx() == f.getCenterX() && s.gety() == f.getCenterY()) {
    // 蛇身变长1
    s.addone(SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE);
    // 生成新食物
    f.getnewfood();
    f.Draw(renderer);
    // 更新屏幕
    SDL_RenderPresent(renderer);
  }
}
