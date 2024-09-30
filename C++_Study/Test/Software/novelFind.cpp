//
// Created by GOD婴宁 on 2024/8/6.
//
#include <iostream>
#include <fstream>
#include <string>

#define INPUT "F:\\Software_Data\\Clion\\Input\\bestMe.txt"
#define OUTPUT "F:\\Software_Data\\Clion\\Output\\bestMe.txt"

void findAndWrite(const std::string &novelPath, const std::string &outputPath, const std::string &target) {
    std::ifstream novel(novelPath, std::ios::in);
    std::ofstream output(outputPath, std::ios::trunc);

    if (!novel.is_open() || !output.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    int lineNum = 0;
    std::string preLine;
    std::string line;
    std::string nextLine;
    while (std::getline(novel, line)) {
        lineNum++;
        if (line.find(target) != std::string::npos) {
            output << '\t' << preLine << std::endl;
            output << "Line " << lineNum << ": " << line << std::endl;
            std::streampos oldPos = novel.tellg();
            // 读取下两行
            std::getline(novel, nextLine);
            std::getline(novel, nextLine);
            // 输出下两行的内容
            output << "\t" << nextLine << '\n' << std::endl;
            // 将文件指针移回到原来的位置
            novel.seekg(oldPos);
        }
        if (line.size() > 1)
            preLine = line;
    }
    novel.close();
    output.close();
}

int main() {
    findAndWrite(INPUT, OUTPUT, "瑟拉丝");
    return 0;
}