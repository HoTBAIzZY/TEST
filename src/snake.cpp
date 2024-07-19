#include "snake.h"  

Square::Square()
{
	center_x = SCREEN_WIDTH / 2 - BLOCK_SIZE / 2; ;
	center_y = SCREEN_HEIGHT / 2 - BLOCK_SIZE / 2;
}

Square::Square(int x, int y, SDL_Texture* texture):
	texture(texture)
{
	center_x = SCREEN_WIDTH / 2 - BLOCK_SIZE / 2; ;
	center_y = SCREEN_HEIGHT / 2 - BLOCK_SIZE / 2;
}


void Square::Draw(SDL_Renderer* renderer)
{
	   
     //绘制方块
	SDL_Rect blockRect = {center_x, center_y, BLOCK_SIZE, BLOCK_SIZE};  
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);  
    SDL_RenderFillRect(renderer, &blockRect);  

}

Square::~Square(void)
{
	// nothing to do
}
