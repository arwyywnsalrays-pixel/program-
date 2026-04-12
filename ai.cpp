#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <tuple>

using namespace std;

// This struct represents one state in the problem
struct State {
    int x, y;          // position
    int fuel;          // fuel amount
    bool c1, c2, c3, c4; // coins

    // constructor
    State(int x, int y, int fuel, bool c1, bool c2, bool c3, bool c4) {
        this->x = x;
        this->y = y;
        this->fuel = fuel;
        this->c1 = c1;
        this->c2 = c2;
        this->c3 = c3;
        this->c4 = c4;
    }

    // this is needed for set (to avoid repeated states)
    bool operator<(const State& o) const {
        return tie(x,y,fuel,c1,c2,c3,c4) < tie(o.x,o.y,o.fuel,o.c1,o.c2,o.c3,o.c4);
    }
};

// check if we reached the goal
bool isGoal(State s) {
    return (s.x == 1 && s.y == 1 && s.c1 && s.c2 && s.c3 && s.c4);
}

// check if position is inside the grid and not blocked
bool isValid(int x, int y) {

    // grid limits
    if (x < 1 || x > 6 && y < 1 || y > 9)
        return false;

    // blocked cells (black cells)
    if (x == 4 && (y == 7 || y == 8))
        return false;

    return true;
}

// print state in simple way
void printState(State s) {
    cout << "(" << s.x << "," << s.y << "," << s.fuel << ","
         << s.c1 << "," << s.c2 << "," << s.c3 << "," << s.c4 << ")\n";
}


