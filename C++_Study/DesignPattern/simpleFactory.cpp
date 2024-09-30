//
// Created by GOD婴宁 on 2024/9/23.
//
#include <iostream>
#include <memory>

using namespace std;
#if 0
class abstractCar {
public:
    virtual void speed() = 0;

    virtual void aspect() = 0;

    virtual ~abstractCar() = default;;
};

class benZ : public abstractCar {
public:
    void speed() override {
        cout << "my limit-speed is 240km/h" << endl;
    }

    void aspect() override {
        cout << "my style is Atmospheric,high-end" << endl;
    }

    ~benZ() override = default;
};

class mayBach : public abstractCar {
public:
    void speed() override {
        cout << "my limit-speed is 380km/h" << endl;
    }

    void aspect() override {
        cout << "my style is luxurious,low-key" << endl;
    }

    ~mayBach() override = default;
};

class Koenigsegg : public abstractCar {
public:
    void speed() override {
        cout << "my limit-speed is 480km/h" << endl;
    }

    void aspect() override {
        cout << "my style is limit,self-esteem" << endl;
    }

    ~Koenigsegg() override = default;
};

enum class Car : char {
    benZ,
    mayBach,
    Koenigsegg
};

class abstractFactory {
public:
    virtual abstractCar *creatCar() = 0;

    virtual ~abstractFactory() = default;
};

class benZFactory : public abstractFactory {
public:
    abstractCar *creatCar() override {
        return new benZ;
    }

    ~benZFactory() override = default;
};

class mayBachFactory : public abstractFactory {
public:
    abstractCar *creatCar() override {
        return new mayBach;
    }

    ~mayBachFactory() override = default;

};

class KoenigseggFactory : public abstractFactory {
public:
    abstractCar *creatCar() override {
        return new Koenigsegg;
    }

    ~KoenigseggFactory() override = default;

};

int main() {
    abstractFactory *koenigsegg = new KoenigseggFactory;
    abstractCar *car1 = koenigsegg->creatCar();
    car1->speed();
    car1->aspect();
    delete car1;
    delete koenigsegg;
    return 0;
}
#endif

// 简单工厂模式
class abstractBlock {
public:
    virtual void show(int nums) = 0;

    virtual ~abstractBlock() = default;
};

class circleBlock : public abstractBlock {
public:
    void show(int nums) override {
        for (int i = 0; i < nums; i++) {
            cout << "Circle Block" << endl;
        }
    }

    ~circleBlock() override = default;
};

class squareBlock : public abstractBlock {
public:
    void show(int nums) override {
        for (int i = 0; i < nums; i++) {
            cout << "Square Block" << endl;
        }
    }

    ~squareBlock() override = default;
};

enum class BLOCK : char {
    CIRCLE, SQUARE
};

class blockFactory {
public:
    abstractBlock *makeBlock(BLOCK type) {
        abstractBlock *block = nullptr;
        switch (type) {
            case BLOCK::CIRCLE:
                block = new circleBlock;
                break;
            case BLOCK::SQUARE:
                block = new squareBlock;
                break;
        }
        return block;
    }
};

int main() {
    auto *factory = new blockFactory;
    int count = 0, nums;
    string type;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> type >> nums;
        if (type == "Circle") {
            unique_ptr<abstractBlock> circle(factory->makeBlock(BLOCK::CIRCLE));
            circle->show(nums);
        } else{
            unique_ptr<abstractBlock> square(factory->makeBlock(BLOCK::SQUARE));
            square->show(nums);
        }
    }
    delete factory;
    return 0;
}
















