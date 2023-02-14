//
// Created by Rick Mercer on 2019-01-02.
// Updated 17-Feb
//

#include "GameOfLife.cpp"
// This #define tells Catch to provide a main(). Only do this once
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

/**
 *  Unit test for Game Of Life.
 */
TEST_CASE("Grow Cell") {
    GameOfLife society(4, 4);
    society.growCellAt(1, 1);
    society.growCellAt(2, 2);
    REQUIRE(society.cellAt(1, 1));
    REQUIRE(society.cellAt(2, 2));
    REQUIRE(not society.cellAt(0, 0));
}

TEST_CASE("Grow Cell 2", "[testGrowCellAt]") {
    GameOfLife society(10, 16);
    // Put cells in a diagonal
    society.growCellAt(1, 1);
    society.growCellAt(2, 2);
    society.growCellAt(3, 3);
    society.growCellAt(4, 4);
    society.growCellAt(5, 5);
    society.growCellAt(6, 6);
    society.growCellAt(7, 7);
    society.growCellAt(8, 8);
    society.growCellAt(9, 9);
    for (int i = 1; i <= 9; i++) {
        REQUIRE(society.cellAt(i, i));
    }

    // Check the corners where there should be no cell
    REQUIRE(!society.cellAt(0, 0));
    REQUIRE(!society.cellAt(0, 15));
    REQUIRE(!society.cellAt(9, 15));
    REQUIRE(!society.cellAt(0, 0));
}

TEST_CASE("Neighbors ", "[testNeighborsSimple]") {
    GameOfLife society(6, 6);
    society.growCellAt(2, 2);
    society.growCellAt(3, 2);
    society.growCellAt(4, 2);

    // Row above all cells
    REQUIRE(society.neighborCount(1, 1) == 1);
    REQUIRE(society.neighborCount(1, 2) == 1);
    REQUIRE(society.neighborCount(1, 3) == 1);

    // Row with 1 cell
    REQUIRE(society.neighborCount(2, 1) == 2);
    REQUIRE(society.neighborCount(2, 2) == 1);
    REQUIRE(society.neighborCount(2, 3) == 2);

    REQUIRE(society.neighborCount(3, 1) == 3);
    REQUIRE(society.neighborCount(3, 2) == 2);
    REQUIRE(society.neighborCount(3, 3) == 3);

    REQUIRE(society.neighborCount(4, 1) == 2);
    REQUIRE(society.neighborCount(4, 2) == 1);
    REQUIRE(society.neighborCount(4, 3) == 2);
}

TEST_CASE("Grow on Corner ", "[testFailedGrowCellAtCorner]") {
    GameOfLife society(7, 7);
    REQUIRE(!society.cellAt(5, 6));
    REQUIRE(!society.cellAt(6, 6));
    REQUIRE(!society.cellAt(0, 6));
    REQUIRE(!society.cellAt(5, 5));
    REQUIRE(!society.cellAt(6, 5));
    REQUIRE(!society.cellAt(0, 5));
    REQUIRE(!society.cellAt(5, 0));
    REQUIRE(!society.cellAt(6, 0));
    REQUIRE(!society.cellAt(0, 0));

    society.growCellAt(6, 6);

    REQUIRE(society.cellAt(6, 6));
    REQUIRE(!society.cellAt(5, 6));
    REQUIRE(!society.cellAt(0, 6));
    REQUIRE(!society.cellAt(5, 5));
    REQUIRE(!society.cellAt(6, 5));
    REQUIRE(!society.cellAt(0, 5));
    REQUIRE(!society.cellAt(5, 0));
    REQUIRE(!society.cellAt(6, 0));
    REQUIRE(!society.cellAt(0, 0));

    GameOfLife g(8, 9);
    g.growCellAt(2, 2);
    g.growCellAt(2, 3);
    g.growCellAt(2, 4);

    REQUIRE(g.neighborCount(1, 1) == 1);
    REQUIRE(g.neighborCount(1, 2) == 2);
    REQUIRE(g.neighborCount(1, 3) == 3);
    REQUIRE(g.neighborCount(1, 4) == 2);
    REQUIRE(g.neighborCount(1, 5) == 1);
    REQUIRE(g.neighborCount(1, 6) == 0);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
////////// test neigborCount(int row, int col) ///////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

TEST_CASE("NeighborCount wrap ", "[testFailedNeighborCountToTheNorthNoWraparound]") {
    GameOfLife g(8, 9);
    g.growCellAt(2, 2);
    g.growCellAt(2, 3);
    g.growCellAt(2, 4);
    REQUIRE(g.neighborCount(3, 1) == 1);
    REQUIRE(g.neighborCount(3, 2) == 2);
    REQUIRE(g.neighborCount(3, 3) == 3);
    REQUIRE(g.neighborCount(3, 4) == 2);
    REQUIRE(g.neighborCount(3, 5) == 1);
    REQUIRE(g.neighborCount(3, 6) == 0);
}

TEST_CASE("NeighborCount wrap 2", "[testFailedNeighborCountToTheEastNoWraparound]") {
    GameOfLife g(8, 9);
    g.growCellAt(2, 2);
    g.growCellAt(3, 2);
    g.growCellAt(4, 2);
    REQUIRE(g.neighborCount(1, 3) == 1);
    REQUIRE(g.neighborCount(2, 3) == 2);
    REQUIRE(g.neighborCount(3, 3) == 3);
    REQUIRE(g.neighborCount(4, 3) == 2);
    REQUIRE(g.neighborCount(5, 3) == 1);
    REQUIRE(g.neighborCount(6, 3) == 0);
}

TEST_CASE("NeighborCount wrap 3", "[testFailedNeighborCountToTheWestNoWraparound]") {
    GameOfLife g(8, 9);
    g.growCellAt(2, 2);
    g.growCellAt(3, 2);
    g.growCellAt(4, 2);
    REQUIRE(g.neighborCount(1, 1) == 1);
    REQUIRE(g.neighborCount(2, 1) == 2);
    REQUIRE(g.neighborCount(3, 1) == 3);
    REQUIRE(g.neighborCount(4, 1) == 2);
    REQUIRE(g.neighborCount(5, 1) == 1);
    REQUIRE(g.neighborCount(6, 1) == 0);
}

TEST_CASE("NeighborCount wrap 4", "[testFailedNeighborCountWithWraparound]") {
    GameOfLife g(8, 9);
    g.growCellAt(0, 0);
    g.growCellAt(0, 1);
    g.growCellAt(1, 0);
    g.growCellAt(1, 1);
    REQUIRE(g.neighborCount(0, 0) == 3);

    g.growCellAt(0, 8);
    g.growCellAt(1, 8);
    g.growCellAt(7, 1);
    g.growCellAt(7, 0);
    g.growCellAt(7, 8);
    REQUIRE(g.neighborCount(0, 0) == 8);
}

TEST_CASE("NeighborCount wrap 5", "[testFailedNeighborcountWrapUpperLeftLowerRight]") {
    GameOfLife society(10, 16);
    society.growCellAt(6, 6);
    society.growCellAt(6, 7);
    society.growCellAt(7, 6);
    society.growCellAt(5, 5);

    society.growCellAt(0, 1);
    society.growCellAt(1, 0);
    society.growCellAt(9, 15);

    REQUIRE(society.neighborCount(0, 15) == 2);
}

TEST_CASE("NeighborCount wrap 6", "[testNeighborsWrapping]") {
    GameOfLife society(10, 18);

    society.growCellAt(3, 3);
    society.growCellAt(3, 4);
    society.growCellAt(3, 5);

    REQUIRE(society.neighborCount(2, 1) == 0);
    REQUIRE(society.neighborCount(2, 2) == 1);
    REQUIRE(society.neighborCount(2, 3) == 2);
    REQUIRE(society.neighborCount(2, 4) == 3);

    society.growCellAt(0, 15);
    society.growCellAt(0, 16);
    society.growCellAt(1, 16);
    society.growCellAt(8, 17);
    society.growCellAt(9, 17);

    REQUIRE(society.neighborCount(0, 7) == 0);
    REQUIRE(society.neighborCount(0, 8) == 0);
    REQUIRE(society.neighborCount(0, 9) == 0);
    REQUIRE(society.neighborCount(0, 17) == 3);
    REQUIRE(society.neighborCount(1, 17) == 2);
    REQUIRE(society.neighborCount(2, 17) == 1);
    REQUIRE(society.neighborCount(7, 17) == 1);
    REQUIRE(society.neighborCount(2, 16) == 1);
    REQUIRE(society.neighborCount(8, 16) == 2);
    REQUIRE(society.neighborCount(9, 16) == 4);
    REQUIRE(society.neighborCount(1, 15) == 3);
    REQUIRE(society.neighborCount(2, 15) == 1);
    REQUIRE(society.neighborCount(8, 15) == 0);
    REQUIRE(society.neighborCount(9, 15) == 2);
    REQUIRE(society.neighborCount(9, 14) == 1);
}

TEST_CASE("neoghbor count") {
    GameOfLife society(7, 7);
    society.growCellAt(2, 6);
    society.growCellAt(3, 6);
    society.growCellAt(4, 6);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(1, 0) == 1);
    REQUIRE(society.neighborCount(2, 0) == 2);
    REQUIRE(society.neighborCount(0, 0) == 0);
}

TEST_CASE("NeighborCount again") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 0);
    society.growCellAt(1, 0);
    society.growCellAt(6, 0);
    REQUIRE(society.neighborCount(0, 6) == 3);
    REQUIRE(society.neighborCount(1, 6) == 2);
    REQUIRE(society.neighborCount(0, 0) == 2);
    REQUIRE(society.neighborCount(6, 0) == 1);
    REQUIRE(society.neighborCount(6, 6) == 2);
    REQUIRE(society.neighborCount(5, 6) == 1);
    REQUIRE(society.neighborCount(4, 6) == 0);
}

TEST_CASE("Count neigbors wraparound") {
    GameOfLife society(7, 7);

    society.growCellAt(6, 5);
    society.growCellAt(6, 6);
    society.growCellAt(6, 0);
    REQUIRE(society.neighborCount(5, 6) == 3);
    REQUIRE(society.neighborCount(0, 6) == 3);
    REQUIRE(society.neighborCount(5, 5) == 2);
    REQUIRE(society.neighborCount(6, 6) == 2);
    REQUIRE(society.neighborCount(6, 0) == 1);
    REQUIRE(society.neighborCount(0, 0) == 2);
    REQUIRE(society.neighborCount(0, 4) == 1);
    REQUIRE(society.neighborCount(4, 6) == 0);
}

TEST_CASE("neighbor count 2") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 5);
    society.growCellAt(0, 6);
    society.growCellAt(0, 0);
    REQUIRE(society.neighborCount(1, 6) == 3);
    REQUIRE(society.neighborCount(6, 6) == 3);
    REQUIRE(society.neighborCount(1, 5) == 2);
    REQUIRE(society.neighborCount(0, 6) == 2);
    REQUIRE(society.neighborCount(0, 0) == 1);
    REQUIRE(society.neighborCount(6, 0) == 2);
    REQUIRE(society.neighborCount(6, 4) == 1);
    REQUIRE(society.neighborCount(2, 6) == 0);

    GameOfLife society2(7, 7);
    society2.growCellAt(0, 6);
    society2.growCellAt(1, 6);
    society2.growCellAt(6, 6);
    REQUIRE(3 == society2.neighborCount(0, 0));
    REQUIRE(2 == society2.neighborCount(1, 0));
    REQUIRE(2 == society2.neighborCount(0, 6));
    REQUIRE(1 == society2.neighborCount(6, 6));
    REQUIRE(2 == society2.neighborCount(6, 0));
    REQUIRE(1 == society2.neighborCount(5, 0));
    REQUIRE(0 == society2.neighborCount(4, 0));
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/////////////////// Test upDate ////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

TEST_CASE("test update 1") {
    GameOfLife society(10, 16);
    society.growCellAt(6, 6);
    society.growCellAt(6, 7);
    society.growCellAt(7, 6);
    society.growCellAt(5, 5);

    society.growCellAt(9, 1);
    society.growCellAt(8, 0);
    REQUIRE(society.neighborCount(9, 0) == 2);
    society.growCellAt(0, 15);

    society.update();
    REQUIRE(society.cellAt(9, 0));
    REQUIRE(!society.cellAt(9, 1));
    REQUIRE(!society.cellAt(8, 0));
    REQUIRE(society.neighborCount(0, 9) == 0);
}

TEST_CASE("test update 2") {
    GameOfLife society(10, 16);
    society.growCellAt(6, 6);
    society.growCellAt(6, 7);
    society.growCellAt(7, 6);
    society.growCellAt(5, 5);

    society.growCellAt(3, 0);
    society.growCellAt(3, 15);
    REQUIRE(society.neighborCount(3, 15) == 1);
    REQUIRE(society.neighborCount(3, 0) == 1);
    society.growCellAt(4, 0);
    society.growCellAt(4, 15);
    REQUIRE(society.neighborCount(3, 15) == 3);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(4, 15) == 3);
    REQUIRE(society.neighborCount(4, 0) == 3);
    society.update();
    REQUIRE(society.neighborCount(3, 15) == 3);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(4, 15) == 3);
    REQUIRE(society.neighborCount(4, 0) == 3);

    society.growCellAt(5, 0);
    society.update();
    REQUIRE(society.cellAt(5, 15));
    REQUIRE(society.cellAt(5, 15));
    REQUIRE(society.cellAt(4, 1));
    REQUIRE(!society.cellAt(4, 15));
}

TEST_CASE("test update 3") {
    GameOfLife society(5, 6);
    society.growCellAt(1, 1);
    society.growCellAt(1, 2);
    society.growCellAt(1, 3);
    society.growCellAt(2, 2);
    society.growCellAt(2, 3);
    society.growCellAt(3, 2);

    society.update();
    // Verify two new cells have been "born" (had precisely 3 neighbors)
    REQUIRE(society.cellAt(0, 2));
    REQUIRE(society.cellAt(3, 3));

    // Verify three cells remained alive (had 2 or 3 neighbors)
    REQUIRE(society.cellAt(1, 1));
    REQUIRE(society.cellAt(1, 3));
    REQUIRE(society.cellAt(3, 2));

    // Verify three cells have "died" (had 4 or more neighbors)
    REQUIRE(!society.cellAt(1, 2));
    REQUIRE(!society.cellAt(2, 2));
    REQUIRE(!society.cellAt(2, 3));
}

TEST_CASE("test update 4") {
    GameOfLife society(5, 9);
    society.growCellAt(0, 5);
    society.growCellAt(0, 8);
    society.growCellAt(1, 0);
    society.growCellAt(2, 0);
    society.growCellAt(2, 8);
    society.growCellAt(3, 0);
    society.growCellAt(3, 8);
    society.growCellAt(4, 6);
    society.growCellAt(4, 4);

    society.update();
    // Only assert the live cells after upDate
    REQUIRE(society.cellAt(0, 5));
    REQUIRE(society.cellAt(1, 0));
    REQUIRE(society.cellAt(2, 1));
    REQUIRE(society.cellAt(3, 0));
    REQUIRE(society.cellAt(3, 7));
    REQUIRE(society.cellAt(3, 8));
    REQUIRE(society.cellAt(4, 0));
    REQUIRE(society.cellAt(4, 5));
    REQUIRE(society.cellAt(4, 7));
    REQUIRE(society.cellAt(4, 8));
}

TEST_CASE("test update 5") {
    GameOfLife society(10, 16);
    society.growCellAt(6, 6);
    society.growCellAt(6, 7);
    society.growCellAt(7, 6);
    society.growCellAt(5, 5);
    society.growCellAt(9, 2);
    society.growCellAt(9, 3);
    society.growCellAt(9, 4);
    society.update();
    REQUIRE(society.cellAt(8, 3));
    REQUIRE(society.cellAt(9, 3));
    REQUIRE(society.cellAt(0, 3));
}

TEST_CASE("test update 6") {
    GameOfLife g(6, 6);
    g.growCellAt(2, 2);
    g.growCellAt(2, 3);
    g.growCellAt(2, 4);
    // ......
    // ......
    // ..OOO.
    // ......
    // ......
    // ......
    g.update();
    // ......
    // ...O..
    // ...O..
    // ...O..
    // ......
    // ......
    REQUIRE(g.cellAt(1, 3));
    REQUIRE(g.cellAt(2, 3));
    REQUIRE(g.cellAt(3, 3));
    REQUIRE(!g.cellAt(2, 2));
    REQUIRE(!g.cellAt(2, 4));

    g.update();
    REQUIRE(g.cellAt(2, 2));
    REQUIRE(g.cellAt(2, 3));
    REQUIRE(g.cellAt(2, 4));
    REQUIRE(!g.cellAt(1, 3));
    REQUIRE(!g.cellAt(3, 3));

    g.update();
    REQUIRE(g.cellAt(1, 3));
    REQUIRE(g.cellAt(2, 3));
    REQUIRE(g.cellAt(3, 3));
    REQUIRE(!g.cellAt(2, 2));
    REQUIRE(!g.cellAt(2, 4));
}

TEST_CASE("test udpdate 7") {
    GameOfLife society2(8, 12);
    society2.growCellAt(3, 5);
    society2.growCellAt(4, 6);
    society2.growCellAt(4, 7);
    society2.growCellAt(5, 6);
    // ............
    // ............
    // ............
    // .....O......
    // ......OO....
    // ......O.....
    // ............
    // ............

    society2.update();

    REQUIRE(society2.cellAt(3, 6));
    REQUIRE(society2.cellAt(4, 5));
    REQUIRE(society2.cellAt(4, 6));
    REQUIRE(society2.cellAt(4, 7));
    REQUIRE(society2.cellAt(5, 6));
    REQUIRE(society2.cellAt(5, 7));
}

TEST_CASE("update 8") {
    GameOfLife society(7, 7);
    society.growCellAt(2, 0);
    society.growCellAt(3, 0);
    society.growCellAt(4, 0);
    society.update();
    REQUIRE(society.cellAt(3, 6));
    REQUIRE(society.cellAt(3, 0));
    REQUIRE(society.cellAt(3, 1));
    REQUIRE(!society.cellAt(2, 0));
    REQUIRE(!society.cellAt(4, 0));
}

TEST_CASE("test update 9") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 2);
    society.growCellAt(0, 3);
    society.growCellAt(0, 4);
    society.update();
    REQUIRE(society.cellAt(6, 3));
    REQUIRE(society.cellAt(0, 3));
    REQUIRE(society.cellAt(1, 3));
    REQUIRE(!society.cellAt(0, 2));
    REQUIRE(!society.cellAt(0, 4));
}

TEST_CASE("test update 10") {
    GameOfLife society(7, 7);
    society.growCellAt(2, 6);
    society.growCellAt(3, 6);
    society.growCellAt(4, 6);
    society.update();
    REQUIRE(society.cellAt(3, 5));
    REQUIRE(society.cellAt(3, 6));
    REQUIRE(society.cellAt(3, 0));
    REQUIRE(!society.cellAt(2, 6));
    REQUIRE(!society.cellAt(4, 6));
}

TEST_CASE("test update 11") {
    GameOfLife society(7, 7);
    society.growCellAt(6, 2);
    society.growCellAt(6, 3);
    society.growCellAt(6, 4);
    society.update();
    REQUIRE(society.cellAt(5, 3));
    REQUIRE(society.cellAt(6, 3));
    REQUIRE(society.cellAt(0, 3));
    REQUIRE(!society.cellAt(6, 2));
    REQUIRE(!society.cellAt(6, 4));
}

TEST_CASE("test update 12") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 0);
    society.growCellAt(1, 0);
    society.growCellAt(6, 0);
    society.update();
    REQUIRE(society.cellAt(0, 1));
    REQUIRE(society.cellAt(0, 0));
    REQUIRE(society.cellAt(0, 6));
    REQUIRE(!society.cellAt(1, 0));
    REQUIRE(!society.cellAt(6, 0));
}

TEST_CASE("test update 13") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 0);
    society.growCellAt(0, 1);
    society.growCellAt(0, 6);
    society.update();
    REQUIRE(society.cellAt(1, 0));
    REQUIRE(society.cellAt(0, 0));
    REQUIRE(society.cellAt(6, 0));
    REQUIRE(!society.cellAt(0, 1));
    REQUIRE(!society.cellAt(0, 6));
}

TEST_CASE("TestUpdateWhenCellsAreInCorners") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 0);
    society.growCellAt(5, 0);
    society.growCellAt(6, 0);
    society.update();
    REQUIRE(society.cellAt(6, 1));
    REQUIRE(society.cellAt(6, 6));
    REQUIRE(society.cellAt(6, 0));
    REQUIRE(!society.cellAt(5, 0));
    REQUIRE(!society.cellAt(0, 0));
}

TEST_CASE("test update 14") {
    GameOfLife society(7, 7);
    society.growCellAt(0, 0);
    society.growCellAt(0, 5);
    society.growCellAt(0, 6);
    society.update();
    REQUIRE(society.cellAt(1, 6));
    REQUIRE(society.cellAt(6, 6));
    REQUIRE(society.cellAt(0, 6));
    REQUIRE(!society.cellAt(0, 5));
    REQUIRE(!society.cellAt(0, 0));
}

TEST_CASE("test update 15") {
    GameOfLife society(10, 16);
    society.growCellAt(9, 2);
    society.growCellAt(9, 3);
    society.growCellAt(9, 4);
    society.update();
    REQUIRE(society.cellAt(8, 3));
    REQUIRE(society.cellAt(9, 3));
    REQUIRE(society.cellAt(0, 3));
}

TEST_CASE("test update 16") {
    GameOfLife society(10, 16);
    society.growCellAt(9, 1);
    society.growCellAt(8, 0);
    REQUIRE(society.neighborCount(9, 0) == 2);
    society.growCellAt(0, 15);

    society.update();
    REQUIRE(society.cellAt(9, 0));
    REQUIRE(!society.cellAt(9, 1));
    REQUIRE(!society.cellAt(8, 0));
    REQUIRE(society.neighborCount(0, 9) == 0);
}

TEST_CASE("test update 17") {
    GameOfLife society(10, 16);
    society.growCellAt(0, 1);
    society.growCellAt(1, 0);
    society.growCellAt(9, 15);
    REQUIRE(2 == society.neighborCount(0, 15));

    society.update();
    REQUIRE(society.cellAt(0, 0));
    REQUIRE(!society.cellAt(0, 1));
    REQUIRE(!society.cellAt(1, 0));
    REQUIRE(0 == society.neighborCount(0, 0));
}

TEST_CASE("testFailedNeighborsWrapping18") {
    GameOfLife society(10, 16);
    society.growCellAt(3, 0);
    society.growCellAt(3, 15);
    REQUIRE(society.neighborCount(3, 15) == 1);
    REQUIRE(society.neighborCount(3, 0) == 1);
    REQUIRE(society.neighborCount(2, 0) == 2);
    REQUIRE(society.neighborCount(4, 0) == 2);
    REQUIRE(society.neighborCount(2, 15) == 2);
    REQUIRE(society.neighborCount(4, 15) == 2);
}

TEST_CASE("test update 19") {
    GameOfLife society(10, 16);

    society.growCellAt(3, 0);
    society.growCellAt(3, 15);
    REQUIRE(society.neighborCount(3, 15) == 1);
    REQUIRE(society.neighborCount(3, 0) == 1);
    society.growCellAt(4, 0);
    society.growCellAt(4, 15);
    REQUIRE(society.neighborCount(3, 15) == 3);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(4, 15) == 3);
    REQUIRE(society.neighborCount(4, 0) == 3);
    society.update();
    REQUIRE(society.neighborCount(3, 15) == 3);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(4, 15) == 3);
    REQUIRE(society.neighborCount(4, 0) == 3);

    society.growCellAt(5, 0);
    society.update();
    REQUIRE(society.cellAt(5, 15));
    REQUIRE(society.cellAt(5, 15));
    REQUIRE(society.cellAt(4, 1));
    REQUIRE(!society.cellAt(4, 15));
}

TEST_CASE("test neighborcount no wrapping") {
    GameOfLife society(5, 9);
    society.growCellAt(0, 1);
    society.growCellAt(1, 0);
    society.growCellAt(1, 1);
    society.growCellAt(0, 8);
    society.growCellAt(1, 8);
    society.growCellAt(4, 0);
    society.growCellAt(4, 1);
    society.growCellAt(4, 8);
    REQUIRE(society.neighborCount(0, 0) == 8);
}

TEST_CASE("test neighborcount with wrapping") {
    GameOfLife society(5, 9);
    society.growCellAt(0, 5);
    society.growCellAt(0, 8);
    society.growCellAt(1, 0);
    society.growCellAt(2, 0);
    society.growCellAt(2, 8);
    society.growCellAt(3, 0);
    society.growCellAt(3, 8);
    society.growCellAt(4, 4);
    society.growCellAt(4, 6);
    REQUIRE(society.neighborCount(0, 5) == 2);
    REQUIRE(society.neighborCount(2, 8) == 4);
    REQUIRE(society.neighborCount(2, 0) == 4);
    REQUIRE(society.neighborCount(1, 0) == 3);
    REQUIRE(society.neighborCount(4, 8) == 3);
    REQUIRE(society.neighborCount(3, 8) == 3);
}

TEST_CASE("test neighborcount wrapping 2") {
    GameOfLife society(7, 9);
    society.growCellAt(2, 8);
    society.growCellAt(3, 8);
    society.growCellAt(4, 8);
    REQUIRE(society.neighborCount(0, 0) == 0);
    REQUIRE(society.neighborCount(1, 0) == 1);
    REQUIRE(society.neighborCount(2, 0) == 2);
    REQUIRE(society.neighborCount(3, 0) == 3);
    REQUIRE(society.neighborCount(4, 0) == 2);
    REQUIRE(society.neighborCount(5, 0) == 1);
    REQUIRE(society.neighborCount(6, 0) == 0);
}

TEST_CASE("NeghborCount") {
    GameOfLife society(7, 9);
    society.growCellAt(0, 7);
    society.growCellAt(0, 8);
    society.growCellAt(1, 8);
    REQUIRE(2 == society.neighborCount(0, 0));
    REQUIRE(2 == society.neighborCount(1, 0));
    REQUIRE(1 == society.neighborCount(2, 0));
}

TEST_CASE("Test Neigborcount Again") {
    GameOfLife society(7, 9);
    society.growCellAt(0, 0);
    society.growCellAt(0, 7);
    society.growCellAt(0, 8);
    society.growCellAt(1, 8);
    REQUIRE(society.neighborCount(6, 8) == 3);
    REQUIRE(society.neighborCount(6, 7) == 2);
    REQUIRE(society.neighborCount(0, 0) == 2);
    REQUIRE(society.neighborCount(1, 0) == 3);
    REQUIRE(society.neighborCount(1, 8) == 3);
}

TEST_CASE("Test update") {
    GameOfLife gol(5, 7);
    gol.growCellAt(1, 2);
    gol.growCellAt(1, 4);
    gol.growCellAt(2, 2);
    gol.growCellAt(2, 3);
    gol.growCellAt(2, 4);

    // Go to the next time
    gol.update();

    // Check the four existing cells exist still
    REQUIRE(gol.cellAt(1, 2));
    REQUIRE(gol.cellAt(1, 4));
    REQUIRE(gol.cellAt(2, 2));
    REQUIRE(gol.cellAt(2, 4));

    // This cell died off
    REQUIRE(!gol.cellAt(2, 3));

    // This cell grew
    REQUIRE(gol.cellAt(3, 3));

    // These cells should remain unaffected in the neighborhood
    REQUIRE(!gol.cellAt(1, 1));
    REQUIRE(!gol.cellAt(1, 3));
    REQUIRE(!gol.cellAt(1, 5));
    REQUIRE(!gol.cellAt(2, 1));
    REQUIRE(!gol.cellAt(2, 5));

    // first row
    REQUIRE(!gol.cellAt(0, 0));
    REQUIRE(!gol.cellAt(0, 1));
    REQUIRE(!gol.cellAt(0, 2));
    REQUIRE(!gol.cellAt(0, 3));
    REQUIRE(!gol.cellAt(0, 4));
    REQUIRE(!gol.cellAt(0, 5));

    REQUIRE(!gol.cellAt(4, 0));
    REQUIRE(!gol.cellAt(4, 1));
    REQUIRE(!gol.cellAt(4, 2));
    REQUIRE(!gol.cellAt(4, 3));
    REQUIRE(!gol.cellAt(4, 4));
    REQUIRE(!gol.cellAt(4, 5));

    REQUIRE(!gol.cellAt(1, 0));
    REQUIRE(!gol.cellAt(2, 0));
    REQUIRE(!gol.cellAt(3, 0));
    REQUIRE(!gol.cellAt(4, 0));

    REQUIRE(!gol.cellAt(1, 6));
    REQUIRE(!gol.cellAt(2, 6));
    REQUIRE(!gol.cellAt(3, 6));
    REQUIRE(!gol.cellAt(4, 6));
}