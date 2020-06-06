//"俄罗斯方块"V1.0
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "Schedule.h"
#include "Control.h"
#include "Windows.h"

using namespace std;

void gotoXY(HANDLE hOut, int x, int y);//移动光标
void printBlock(HANDLE hOut, int block[4][4], int x, int y);//打印方块
void myStop(HANDLE hOut, int block[4][4]);//游戏暂停
int main() {
    Windows windows;
    Mechanism mechanism(windows);
    Schedule schedule(windows, mechanism);
    Control control(windows, mechanism);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出设备句柄
    windows.initialWindow(hOut);
    initial:
    windows.gotoXY(hOut, 0, 0);
    windows.initialPrint(hOut);
    check = true;
    val = 50;
    fraction = 0;
    checkpoint = 1;
    times = val;
    for (int i = 0; i < 20; ++i) {
        for (int j = 1; j < 11; ++j) {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i < 20; ++i) {
        map[i][0] = map[i][11] = 1;
    }
    for (int i = 0; i < 12; ++i) {
        map[20][i] = 1;
    }

    srand((unsigned) time(NULL));
    mechanism.roundBlock(hOut, blockA);
    while (true) {
        if (check) {
            mechanism.eliminateRow(hOut, map, val, fraction, checkpoint);
            check = false;
            positionX = -3;
            positionY = 4;
            if (mechanism.collisionDetection(blockA, map, positionX, positionY)) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        blockB[i][j] = blockA[i][j];
                    }
                }
                mechanism.roundBlock(hOut, blockA);
            } else {
                schedule.gameOver(hOut, blockA, map);
                goto initial;
            }
        }
        printBlock(hOut, blockB, positionX, positionY);
        if (_kbhit()) {
            key = _getch();
            switch (key) {
                case 72:
                    control.myUp(hOut, blockB, map, positionX, positionY);
                    break;
                case 75:
                    control.myLeft(hOut, blockB, map, positionX, positionY);
                    break;
                case 77:
                    control.myRight(hOut, blockB, map, positionX, positionY);
                    break;
                case 80:
                    switch (control.myDown(hOut, blockB, map, positionX, positionY)) {
                        case 0:
                            check = false;
                            break;
                        case 1:
                            check = true;
                            break;
                        case 2:
                            schedule.gameOver(hOut, blockB, map);
                            goto initial;
                        default:
                            break;
                    }
                    break;
                case 32:
                    myStop(hOut, blockA);
                    break;
                case 27:
                    exit(0);
                default:
                    break;
            }
        }
        Sleep(20);
        if (0 == --times) {
            switch (control.myDown(hOut, blockB, map, positionX, positionY)) {
                case 0:
                    check = false;
                    break;
                case 1:
                    check = true;
                    break;
                case 2:
                    schedule.gameOver(hOut, blockB, map);
                    goto initial;
                default:
                    break;
            }
            times = val;
        }
    }
    cin.get();
    return 0;
}





