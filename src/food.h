#include <SDL2/SDL.h>  
#include <SDL_keycode.h>
#include "defines.h"


class Food
{
public:
    Food();
	~Food();

public:
    void getnewfood();
	void setCenterX(int x) { center_x = x; }
	void setCenterY(int y) { center_y = y; }
	int getCenterX() const { return this->center_x; }
	int getCenterY() const { return this->center_y; }
    
	//控制食物的位置改变量
	void changeCenterX(bool add,int num);
	void changeCenterY(bool add,int num);
	void Draw(SDL_Renderer* renderer);


private:

	int center_x;
	int center_y;

};


