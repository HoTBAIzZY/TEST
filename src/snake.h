#include <SDL2/SDL.h>  

// 假设我们使用简单的struct来表示蛇的每一部分  
struct SnakePart {  
    SDL_Rect rect; // SDL_Rect用于表示蛇身体部分的位置和大小  
    SnakePart* prev = nullptr;  
    SnakePart* next = nullptr;  
  
    SnakePart(int x, int y, int width, int height) : rect({x, y, width, height}) {}  
};  

enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };  
class Snake {  
private:  
    SnakePart* head = nullptr;  
    SnakePart* tail = nullptr;  
    int length = 6;  
    // 假设方向使用枚举表示  
    
    Direction currentDirection = Direction::STOP;  
    bool check_collision_self();
    // 辅助函数：在链表末尾添加一个新部分  
    void appendPart(int x, int y, int width, int height);
    // 辅助函数：从链表头部移除一个部分  
    void removeHead();
  
public:  
    // 构造函数和析构函数  
    Snake();
    ~Snake();
  
    // 设置方向（这里简化了处理逻辑）  
    void setDirection(Direction newDirection);
	//	返回蛇的方向
	Direction getCurrentDirection() const;
	//返回蛇头位置
	int getx(){
		return head->rect.x;
	}

	int gety(){
		return head->rect.y;
	}
    // 移动蛇（根据当前方向）  
    int move(int screenWidth, int screenHeight, int partWidth, int partHeight);
    int addone(int screenWidth, int screenHeight, int partWidth, int partHeight);
    // 渲染蛇（需要SDL_Renderer*）  
    void render(SDL_Renderer* renderer);
};  
