#include <SDL2/SDL.h>  
#include <SDL_keycode.h>
#include "defines.h"


class Snake
{
public:
    Snake();
	Snake(int x, int y, SDL_Texture* texture);
	~Snake(void);

public:
	void setCenterX(int x) { center_x = x; }
	void setCenterY(int y) { center_y = y; }
	int getCenterX() const { return this->center_x; }
	int getCenterY() const { return this->center_y; }
    
	//控制蛇的位置改变量
	int changeCenterX(bool add,int num);
	int changeCenterY(bool add,int num);
	void Draw(SDL_Renderer* renderer);


private:

	int center_x;
	int center_y;

};


