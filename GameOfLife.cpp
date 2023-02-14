/*
 * Filename: GameOfLife.cpp
 *
 *  Authors Rick Mercer and Anthony Bisgood
 *
 * This class models a society of cells growing according
 * to the rules of John Conway's Game of Life.
 *
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// This class allows a society of cells to grow according
// to the rules from John Conway's Game of Life
class GameOfLife {
    // --Data Member
   private:
    vector<std::vector<bool>> theSociety;

   public:
    // Construct a board that is rows by cols size
    // with all elements set to false
    GameOfLife(unsigned rows, unsigned cols) {
        for (int i = 0; i < rows; i++) {
            vector<bool>temp;
            for (int j = 0; j < cols; j++) {
                temp.push_back(false);
            }
            theSociety.push_back(temp);
        }
    }

    // Grow a cell at the given location
    void growCellAt(unsigned row, unsigned col) {
        theSociety[row][col] = true;
    }

    // Check to see if a cell is at the given location
    bool cellAt(unsigned row, unsigned col) const {
        return theSociety[row][col];
    }

    // Returns the colony as one big string
    string toString() const {
        string res = "";
        for (int i = 0; i < theSociety.size()-1; i++) {
            for (int j = 0; j < theSociety[i].size()-1; j++) {
                if (theSociety[i][j]) {
                    res += "O ";
                } else {
                    res += ".  ";
                }
            }
            res += "\n";
        }
        return res;
    }

    // Count the neighbors around the given location. Use wraparound. A cell in row 0
    // has neighbors in the last row if a cell is in the same column, or the column to
    // the left or right. In this example, cell 0,5 has two neighbors in the last row,
    // cell 2,8  has four neighbors, cell 2,0 has four neighbors, cell 1,0 has three
    // neighbors. The cell at 3,8 has 3 neighbors. The potential location for a cell
    // at 4,8 would have three neighbors.
    //
    // .....O..O
    // O........
    // O.......O
    // O.......O
    // ....O.O..
    //
    // The return values should always be in the range of 0 through 8.
    // Return the number of neighbors around any cell using wrap around.
    int neighborCount(int row, int col) const {
        int up = row - 1;
        int down = row + 1;
        int left = col - 1;
        int right = col + 1;
        int count = 0;
        if (down >= theSociety.size()) {
            down = 0;
        } else if (up < 0) {
            up = theSociety.size() - 1;
        }
        if (right >= theSociety[0].size()) {
            right = 0;
        } else if (left < 0) {
            left = theSociety[0].size() - 1;
        }
        if (theSociety[up][left]) {
            count++;
        }
        if (theSociety[up][col]) {
            count++;
        }
        if (theSociety[up][right]) {
            count++;
        }
        if (theSociety[row][left]) {
            count++;
        }
        if (theSociety[row][right]) {
            count++;
        }
        if (theSociety[down][left]) {
            count++;
        }
        if (theSociety[down][col]) {
            count++;
        }
        if (theSociety[down][right]) {
            count++;
        }
        return count;
    }

    // Change the state to the next society of cells
    void update() {
        int rows = theSociety.size();
        int cols = theSociety[0].size();
        vector<vector<bool>> newSociety(rows, vector<bool>(cols));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int nCount = neighborCount(i, j);
                if (cellAt(i, j)) {
                    if (nCount == 2 || nCount == 3) {
                        newSociety[i][j] = true;
                    }
                    if (nCount < 2 || nCount > 3) {
                        newSociety[i][j] = false;
                    }
                } else {
                    if (nCount == 3) {
                        newSociety[i][j] = true;
                    } else {
                        newSociety[i][j] = false;
                    }
                }
            }
        }
        theSociety = newSociety;
    }
};
