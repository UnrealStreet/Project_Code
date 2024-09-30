//
// Created by GOD婴宁 on 2024/8/13.
//
#include <iostream>
#include <vector>

using namespace std;
/*
 * 单例模式-懒汉式
 */

/*class shoppingCar {
public:
    static shoppingCar *getCar() {
        return car;
    }

    void addThing(string &fruit, int nums) {
        things.emplace_back(fruit, nums);
    }

    void printThing() {
        for (const auto &t: things) {
            cout << t.first << " " << t.second << endl;
        }
    }

    shoppingCar(const shoppingCar &car) = delete;

private:
    shoppingCar() = default;

    static shoppingCar *car;
    vector<pair<string, int>> things;
};

shoppingCar *shoppingCar::car = new shoppingCar();
 */

/*
 * 单例模式-饿汉式
 */
/*
class shoppingCar {
        public:
        static shoppingCar *getCar() {
            static shoppingCar car;
            return &car;
        }

        void addThing(string &fruit, int nums) {
            things.emplace_back(fruit, nums);
        }

        void printThing() {
            for (const auto &t: things) {
                cout << t.first << " " << t.second << endl;
            }
        }

        shoppingCar(const shoppingCar &car) = delete;

        private:
        shoppingCar() = default;

        vector<pair<string, int>> things;
};


int main() {
    shoppingCar *car = shoppingCar::getCar();
    string fruit;
    int nums;
    while (cin >> fruit >> nums) {
        car->addThing(fruit, nums);
        if (getchar() == ' ')
            break;
    }
    car->printThing();
    return 0;
}*/
