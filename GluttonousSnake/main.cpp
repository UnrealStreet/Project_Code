#include <iostream>
#include <deque>
#include <easyx.h>
#include <mutex>
#include <condition_variable>

using std::cin;
using std::cout;
using std::deque;

#define SIZE 20
#define DELAY 100

std::condition_variable cv;
std::mutex cv_m;

const int WIDTH = 640;
const int HEIGHT = 480;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake(int x, int y, Direction dir) : x(x), y(y), dir(dir) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    Direction getDir() const {
        return dir;
    }

    void setDir(Direction dir) {
        this->dir = dir;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

private:
    int x;
    int y;
    Direction dir;
};

class Food {
public:
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

private:
    int x;
    int y;
};

//绘制蛇身
void drawSnake(deque<Snake> &snake) {
    setfillcolor(RGB(0, 255, 0));
    for (const auto &body: snake) {
        fillrectangle(body.getX() * SIZE, body.getY() * SIZE, (body.getX() + 1) * SIZE, (body.getY() + 1) * SIZE);
    }
    //控制蛇的移动速度
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait_for(lk, std::chrono::milliseconds(DELAY));
}

//判断游戏是否结束
bool isGameOver(const deque<Snake> &snake) {
    //获取蛇头
    auto head = snake.front();
    //判断蛇头是否撞墙
    if (head.getX() < 0 || head.getX() >= WIDTH / SIZE || head.getY() < 0 || head.getY() >= HEIGHT / SIZE) {
        return true;
    }
    //判断蛇头是否撞到自己
    for (auto it = snake.begin() + 1; it != snake.end(); ++it) {
        if (head.getX() == it->getX() && head.getY() == it->getY()) {
            return true;
        }
    }
    return false;
}

//游戏结束信息
void gameOver(bool win) {
    if (win) {
        settextcolor(RGB(255, 0, 0));//设置字体颜色
        //设置当前文字样式，指定高度50，宽度0表示自适应，字体宋体，_T支持UNICODE编码
        settextstyle(100, 0, _T("宋体"));
        TCHAR endStr[16];
        _stprintf(endStr, _T("Game Over!!!"));
        //输出文字到指定位置
        outtextxy(WIDTH / SIZE, HEIGHT / SIZE, endStr);
        Sleep(3000);
        closegraph();//关闭图形窗口
        //退出程序
        exit(0);
    }
}

//蛇移动 1.蛇头移动 2.蛇身移动 3.判断游戏是否结束 4.判断是否吃到食物 5.绘制蛇
void moveSnake(deque<Snake> &snake, bool grow = false) {
    //获取蛇头
    auto newHead = snake.front();
    //获取蛇尾
    auto tail = snake.back();
    //蛇头移动
    switch (newHead.getDir()) {
        case UP:
            newHead.setY(newHead.getY() - 1);
            break;
        case DOWN:
            newHead.setY(newHead.getY() + 1);
            break;
        case LEFT:
            newHead.setX(newHead.getX() - 1);
            break;
        case RIGHT:
            newHead.setX(newHead.getX() + 1);
            break;
    }
    //将蛇头插入到双端队列头部
    snake.push_front(newHead);
    //判断游戏是否结束
    gameOver(isGameOver(snake));
    //判断是否吃到食物 grow为true表示吃到食物 为false表示普通移动
    if (!grow) {
        //没吃到食物
        //删除蛇尾,将蛇尾的矩形框清除
        clearrectangle(tail.getX() * SIZE, tail.getY() * SIZE, (tail.getX() + 1) * SIZE, (tail.getY() + 1) * SIZE);
        //从双端队列尾部删除蛇尾
        snake.pop_back();
    }
    //绘制蛇
    drawSnake(snake);
}

//生成食物，食物不能在蛇身上
void createFood(deque<Snake> &snake, Food &food) {
    //生成食物,直到食物不在蛇身上为止
    while (true) {
        //随机生成食物
        food.setX(rand() % (WIDTH / SIZE));
        food.setY(rand() % (HEIGHT / SIZE));
        //用一个变量储存食物是否在蛇身上
        bool isOnSnake = false;
        //遍历蛇身
        for (const auto &body: snake) {
            //判断食物是否在蛇身上
            if (food.getX() == body.getX() && food.getY() == body.getY()) {
                //食物在蛇身上,跳出循环，重新生成食物
                isOnSnake = true;
                break;
            }
        }
        //食物不在蛇身上
        if (!isOnSnake) {
            //绘制食物
            setfillcolor(RGB(255, 0, 0));
            fillrectangle(food.getX() * SIZE, food.getY() * SIZE, (food.getX() + 1) * SIZE, (food.getY() + 1) * SIZE);
            break;
        }
    }
}


//检测是否吃到食物
bool isEatFood(const deque<Snake> &snake, const Food &food) {
    //获取蛇头
    auto head = snake.front();
    //判断蛇头是否吃到食物
    if (head.getX() == food.getX() && head.getY() == food.getY()) {
        return true;
    }
    return false;
}
void scoreShow(int& score){
    //设置得分信息
    //1.颜色
    settextcolor(RGB(255, 255, 255));
    //2.字体
    settextstyle(20, 0, _T("宋体"));
    TCHAR scoreStr[16];
    _stprintf(scoreStr, _T("Score: %d"), score);
    //3.输出文字
    outtextxy(0, 0, scoreStr);
}

//更改蛇移动方向
void changeDirection(deque<Snake> &snake,Food &food,int &score) {
    ExMessage msg = {0};
    //获取键盘消息
    while (peekmessage(&msg, EX_KEY)) {
        //判断按键
        if (msg.message == WM_KEYDOWN) {
            cv.notify_one();
            switch (msg.vkcode) {
                case 'w':
                case 'W':
                case VK_UP:
                    //不可以反方向移动
                    if (snake.front().getDir() != DOWN)
                        snake.front().setDir(UP);
                    break;
                case 's':
                case 'S':
                case VK_DOWN:
                    //不可以反方向移动
                    if (snake.front().getDir() != UP)
                        snake.front().setDir(DOWN);
                    break;
                case 'a':
                case 'A':
                case VK_LEFT:
                    //不可以反方向移动
                    if (snake.front().getDir() != RIGHT)
                        snake.front().setDir(LEFT);
                    break;
                case 'd':
                case 'D':
                case VK_RIGHT:
                    //不可以反方向移动
                    if (snake.front().getDir() != LEFT)
                        snake.front().setDir(RIGHT);
                    break;
            }
            //判断是否吃到食物
            if (isEatFood(snake, food)) {
                //吃到食物分数加一
                score++;
                //生成食物
                createFood(snake, food);
                //蛇移动
                moveSnake(snake, true);
            }
            //设置得分信息
            scoreShow(score);
            //绘制蛇
            moveSnake(snake);
        }
    }
}
int main() {
    initgraph(WIDTH, HEIGHT);//初始化图形窗口
    //定义一条蛇
    deque<Snake> snake;
    //初始化蛇
    //在双端队列头部插入蛇头
    snake.emplace_front(WIDTH / SIZE / 2, HEIGHT / SIZE / 2, RIGHT);
    Food food;
    //生成食物
    createFood(snake, food);
    drawSnake(snake);

    int score = 0;
    while (true) {
        moveSnake(snake);
        //更改蛇移动方向
        changeDirection(snake, food, score);
        //判断是否吃到食物
        if (isEatFood(snake, food)) {
            //吃到食物分数加一
            score++;
            //生成食物
            createFood(snake, food);
            //蛇移动
            moveSnake(snake, true);
        }
        //设置得分信息
        scoreShow(score);
    }
    return 0;
}
