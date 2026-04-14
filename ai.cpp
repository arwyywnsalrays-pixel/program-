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

    // this is needed for set
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

    // blocked cells 
    if (x == 4 && (y == 7 || y == 8))
        return false;

    return true;
}

// print state in simple way
void printState(State s) {
    cout << "(" << s.x << "," << s.y << "," << s.fuel << ","
         << s.c1 << "," << s.c2 << "," << s.c3 << "," << s.c4 << ")\n";
}

// generate next possible states
vector<State> getNextStates(State s) {

    vector<State> next;

    // possible moves: right, left, up, down
    vector<pair<int,int>> moves = {
        {1,0}, {-1,0}, {0,1}, {0,-1}
    };

    for (auto m : moves) {

        int nx = s.x + m.first;
        int ny = s.y + m.second;

        // check valid move
        if (!isValid(nx, ny))
            continue;

        // if no fuel, cannot move
        if (s.fuel == 0)
            continue;

        State ns = s;

        // move to new position
        ns.x = nx;
        ns.y = ny;

        // decrease fuel
        ns.fuel--;

        // fuel station 
        if (nx == 4 && ny == 9) {
            ns.fuel =20;
        }

        // coins locations
        if (nx == 2 && ny == 2) ns.c1 = true;
        if (nx == 3 && ny == 3) ns.c2 = true;
        if (nx == 5 && ny == 7) ns.c3 = true;
        if (nx == 6 && ny == 5) ns.c4 = true;

        next.push_back(ns);
    }

    return next;
}

// Breadth First Search
void BFS(State start) {

    queue<State> q;
    set<State> visited;

    q.push(start);

    cout << "\n--- BFS ---\n";

    while (!q.empty()) {

        State cur = q.front();
        q.pop();

        // skip if already visited
        if (visited.count(cur))
            continue;

        visited.insert(cur);

        printState(cur);

        // check goal
        if (isGoal(cur)) {
            cout << "Goal reached!\n";
            return;
        }

        // add next states
        for (auto s : getNextStates(cur)) {
            q.push(s);
        }
    }
}



int main() {

    // starting state
    State start(5,8,6,false,false,false,false);
     BFS(start);
}
