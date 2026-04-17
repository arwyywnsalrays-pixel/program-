#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <tuple>
#include <fstream>

using namespace std;

// This struct represents one state in the problem
struct State {
    int x, y;          // position
    int fuel;          // fuel amount
    bool c1, c2, c3, c4; // coins

    // constructor
    State(int x=0, int y=0, int fuel=0, bool c1=false, bool c2=false, bool c3=false, bool c4=false) {
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
    if (x < 1 ||  x > 6 || y < 1 || y > 9)
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
        if (!isValid(nx, ny)||s.fuel <=0)
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

        // fuel station (refill fuel)
        if (nx == 4 && ny == 9) {
            ns.fuel =20;
        }

        // coins locations
        if (nx == 4 && ny == 9)ns.fuel = 20;
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
    int nodes =0;

    cout << "\n--- BFS ---\n";

    while (!q.empty()) {

        State cur = q.front();
        q.pop();

        // skip if already visited
        if (visited.count(cur))
            continue;

        visited.insert(cur);
        nodes ++;

        printState(cur);

        // check goal
        if (isGoal(cur)) {
            cout << "Goal reached!\n"<<nodes<<endl;
            return;
        }

        // add next states
        for (auto s : getNextStates(cur)) {
            q.push(s);
        }
    }
}

// Depth First Search
void DFS(State start) {

    stack<State> st;
    set<State> visited;
     int nodes = 0;

    st.push(start);

    cout << "\n--- DFS ---\n";

    while (!st.empty()) {

        State cur = st.top();
        st.pop();

        // skip if visited
        if (visited.count(cur))
            continue;

        visited.insert(cur);
        nodes ++;

       // printState(cur);

        // check goal
        if (isGoal(cur)) {
            cout << "Goal reached!"<<nodes<<endl;
            return;
        }

        // add next states
        for (auto s : getNextStates(cur)) {
            st.push(s);
        }
    }
}

// Depth Limited Search (used in IDDFS)
bool DLS(State cur, int depth, set<State>& visited) {

    if (visited.count(cur))
        return false;

    visited.insert(cur);

   // printState(cur);

    if (isGoal(cur)) {
        cout << "Goal reached!\n";
        return true;
    }

    // stop when depth = 0
    if (depth == 0)
        return false;

    for (auto s : getNextStates(cur)) {
        if (DLS(s, depth - 1, visited))
            return true;
    }

    return false;
}

// Iterative Deepening DFS
void IDDFS(State start) {

    cout <<
    "\n--- IDDFS ---\n";

    for (int depth = 0; depth <= 50; depth++) {

        cout << "\nDepth = " << depth << endl;

        set<State> visited;

        if (DLS(start, depth, visited)) {
            cout << "Solved at depth: " << depth << endl;
            return;
        }
    }
}

int main() {

    ifstream file("input.txt");
    if(!file){
        cout<<"Error:create'input.txt'first!\n";
        return 1;
    }
    int x,y,f,c1,c2,c3,c4;
    while (file>> x>> y>> f >> c1 >> c2 >> c3 >> c4)
    {
        State start(x,y,f,(c1 ==1),(c2 ==1),(c3 ==1),(c4 ==1));
        cout<<"\n>>>Testing State:(" <<x <<","<<y<<")Fuel: " <<f<<endl;

    
    


    

    BFS(start);
    DFS(start);
    IDDFS(start);
    cout<<"----------------"<<endl;
}
file.close();


    return 0;
}
