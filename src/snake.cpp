#include "snake.h"  

Snake::Snake(){
	center_x = SCREEN_WIDTH / 2 - BLOCK_SIZE / 2; ;
	center_y = SCREEN_HEIGHT / 2 - BLOCK_SIZE / 2;
}

Snake::Snake(int x, int y){
	center_x = SCREEN_WIDTH / 2 - BLOCK_SIZE / 2; ;
	center_y = SCREEN_HEIGHT / 2 - BLOCK_SIZE / 2;
}

void Snake::changeCenterX(bool add,int num){
	if(add){
		center_x +=num;
	}else{
		center_x -=num;
	}
}
void Snake::changeCenterY(bool add,int num){
	if(add){
		center_y +=num;
	}else{
		center_y -=num;
	}
}


void Snake::Draw(SDL_Renderer* renderer){
	   
     //绘制方块
	SDL_Rect blockRect = {center_x, center_y, BLOCK_SIZE, BLOCK_SIZE};  
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);  
    SDL_RenderFillRect(renderer, &blockRect);  

}

Snake::~Snake(void){
	// nothing to do
}
