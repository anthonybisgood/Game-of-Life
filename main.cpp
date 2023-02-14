/*
 * RunGameMain.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: mercer
 */
#include <iostream>

#include "GameOfLife.cpp"
using namespace std;

// int mainRUN () { need this when running a unit test
int main() {
    GameOfLife society(5, 11);
    society.growCellAt(3, 2);
    society.growCellAt(4, 3);
    society.growCellAt(0, 3);
    society.growCellAt(1, 2);
    society.growCellAt(1, 3);
    cout << society.toString() << endl;

    string ch;
    for (int count = 1; count <= 10; count++) {
        cout << society.toString() << endl;

        society.update();
    }
    return 0;
}
