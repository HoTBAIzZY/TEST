#include "snake.h"  
#include "defines.h"
#include "iostream"

// 构造函数和析构函数  
Snake::Snake() {

	// 创建头部  
 
        int x = rand() % SCREEN_xgezi;
        int y = rand() % SCREEN_ygezi;

        head = new SnakePart(x,y, BLOCK_SIZE, BLOCK_SIZE);  
        tail = head;  // 初始时，头部和尾部是同一个部分  
  
        // 根据长度创建剩余的身体部分  
        for (int i = 1; i < length; ++i) {  
            // 假设蛇是向右移动的，所以每个新部分的x坐标都增加width  
            SnakePart* newPart = new SnakePart(x - i , y, BLOCK_SIZE, BLOCK_SIZE);  
              
            // 设置前一个部分的next指针指向新部分  
            if (tail != nullptr) {  
                tail->next = newPart;  
            }  
  
            // 设置新部分的prev指针指向前一个部分（除了头部）  
            if (i > 0) {  
                newPart->prev = tail;  
            }  
  
            // 更新尾部为新部分  
            tail = newPart;
			 tail->next = nullptr;  
        }  
  
        // 设置初始方向  
        currentDirection = Direction::RIGHT; 
}  
  
Snake::~Snake() {  
    // 清理链表  
    while (head) {  
        SnakePart* temp = head;  
        head = head->next;  
        delete temp;  
    }  
}  
   
// 辅助函数：在链表tou添加一个新部分  
void Snake::appendPart(int x, int y, int width, int height) {  
        SnakePart* newPart = new SnakePart(x, y, width, height);  
        if (!head) {  
            head = newPart;  
			tail = newPart;
        } else {  
			head->prev=newPart;
			
			newPart->next=head;

			head=newPart; 
        }  
        length++;  
}  
  
    // 辅助函数：从链表wei部移除一个部分  
void Snake::removeHead() {  

		if(tail){
			SnakePart* toDelete = tail;
			tail=tail->prev;
			if(tail){
				tail->next=nullptr;
			}else{
				head=nullptr;
			}

			delete toDelete;  
            length--;  
		}
}  
  
    // 设置方向（这里简化了处理逻辑）  
void Snake::setDirection(Direction newDirection) {  
        // 这里可以添加逻辑来防止立即反向等  
        currentDirection = newDirection;  
}  

Direction Snake::getCurrentDirection() const {  
    return currentDirection;  
} 
    // 移动蛇（根据当前方向）  
int Snake::move(int screenWidth, int screenHeight, int partWidth, int partHeight) {  
        int newX = head->rect.x;  
        int newY = head->rect.y;  
  
        switch (currentDirection) {  
            case Direction::LEFT:  
                newX -= 1;  
                break;  
            case Direction::RIGHT:  
                newX += 1;  
                break;  
            case Direction::UP:  
                newY -= 1;  
                break;  
            case Direction::DOWN:  
                newY += 1;  
                break;  
            default:  
                break;  
        }  
  
        
  
        
        // 这里省略了碰撞检测的逻辑  
  
        // 如果没有碰撞，则添加新部分并移动蛇  
        appendPart(newX, newY, partWidth, partHeight);  
        removeHead(); // 假设总是移动头部，并删除尾部  
        
        // 检查是否撞墙或撞到自己   checkCollision(head, newX, newY)
         if(newX <= 0 || newX >= SCREEN_xgezi || newY <= 0 || newY >= SCREEN_ygezi||check_collision_self()) {  
             //处理碰撞逻辑（比如游戏结束等）    
             std::cout << "Game Over!" << std::endl;  
             return 1;  
         }  
        return 0;
}  

 // 移动蛇（根据当前方向）  
int Snake::addone(int screenWidth, int screenHeight, int partWidth, int partHeight) {  
        int newX = head->rect.x;  
        int newY = head->rect.y;  
  
        switch (currentDirection) {  
            case Direction::LEFT:  
                newX -= 1;  
                break;  
            case Direction::RIGHT:  
                newX += 1;  
                break;  
            case Direction::UP:  
                newY -= 1;  
                break;  
            case Direction::DOWN:  
                newY += 1;  
                break;  
            default:  
                break;  
        }  
  

  
        // 添加新部分并移动蛇  
        appendPart(newX, newY, partWidth, partHeight);  
        return 0;
}  

bool Snake::check_collision_self() {
    SnakePart* current = head->next;
    while (current != nullptr) {
        if (head->rect.x == current->rect.x && head->rect.y == current->rect.y) {
            return true; //Collision detected
        }
        current = current->next;
    }
    return false;
}
    // 渲染蛇（需要SDL_Renderer*）  
void Snake::render(SDL_Renderer* renderer) {  
        SnakePart* current = head;  
		
        while (current) {  
            SDL_Rect rect = {current->rect.x*BLOCK_SIZE, current->rect.y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};

            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // 红色  
            SDL_RenderFillRect(renderer, &rect);
            current = current->next;  
        }  
}  
