#include "food.h"  
#include "defines.h"

Food::Food(){

		center_x = rand() % SCREEN_xgezi;  
        center_y = rand() % SCREEN_ygezi;  
}

void Food::getnewfood(){
	center_x = rand() % SCREEN_xgezi;  
        center_y = rand() % SCREEN_ygezi;  
}
void Food::changeCenterX(bool add,int num){
	if(add){
		center_x +=num;
	}else{
		center_x -=num;
	}
}
void Food::changeCenterY(bool add,int num){
	if(add){
		center_y +=num;
	}else{
		center_y -=num;
	}
}


void Food::Draw(SDL_Renderer* renderer){
     //绘制方块
         
    SDL_Rect rect = {center_x*BLOCK_SIZE, center_y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);  
  //  SDL_RenderDrawRect(renderer, &rect);
}

Food::~Food(void){
	// nothing to do
}
