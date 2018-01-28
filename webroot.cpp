#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>

#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define UP "UP"
#define DOWN "DOWN"
#define DEPLOY "DEPLOY"


using namespace std;
typedef pair<int, int> pos;
typedef vector<vector<bool>> grid;
/**
 * Don't run into a player's light trail! Use your helper bots at strategic moments or as a last resort to be the last drone standing!
 **/

vector<pos> inline neighbor(pos position);
grid conn_region(grid board, const pos & start, const vector<pos> positions, 
    const int & myId, const int & playerCount, int avoid = 0);
set<pos> inline neighbor_step(pos position, int step);
int opposite(int dir);

vector<string> D = {"UP", "DOWN", "LEFT", "RIGHT", "DEPLOY"};

int main()
{
    int playerCount; // the number of at the start of this game
    cin >> playerCount; cin.ignore();
    int myId; // your bot's id
    cin >> myId; cin.ignore();
    grid board(15, vector<bool>(30));

    for (int r = 0; r < 15; r++)
        for (int c = 0; c < 30; c++)
            board[r][c] = 1;

    int laststep = 2;
    int loopcount = 0;
    bool survival = true;
    // game loop
    while (1) {
        int helperBots; // your number of charges left to deploy helper bots
        cin >> helperBots; cin.ignore();

        vector<pos> positions;

        for (int i = 0; i < playerCount; i++) {
            int x; // your bot's coordinates on the grid (0,0) is top-left
            int y;
            cin >> x >> y; cin.ignore();
            if (x != -1)
                board[y][x] = false;
            positions.push_back(make_pair(x, y));
        }

        int removalCount; // the amount walls removed this turn by helper bots
        cin >> removalCount; cin.ignore();

        for (int i = 0; i < removalCount; i++) {
            int removeX; // the coordinates of a wall removed this turn
            int removeY;
            cin >> removeX >> removeY; cin.ignore();
            board[removeY][removeX] = true;
            // cerr << removalCount << endl;
            // cerr << "RY, RX" << removeY << ',' << removeX << endl; 
        }
        for (auto p: positions) {
            if (p.first != -1)
                board[p.second][p.first] = false;
        }
        // cerr << "=============BOARDOUT=============" << endl;
        // for (auto row: board) {
        //     for (auto col: row) {
        //         cerr << col << ' ';
        //     }
        //     cerr << endl;
        // }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: // cerr << "Debug messages..." << endl;
        vector<grid> playerRegion(positions.size());
        vector<int> score(4);
        vector<int> avail(4);
        int maxIndex = 0;

        for (int i = 0; i < positions.size(); i++) {
            if (positions[i].first != -1)
                playerRegion[i] = conn_region(board, positions[i], positions, myId,\ 
                    positions.size(), (3 - loopcount / 15) > 1 ? (3 - loopcount / 15) : 1);
        }
        
        int dscore = 0;
        int odX, odY;
        int dX = positions[myId].first;
        int dY = positions[myId].second;
        grid boardcopy = board;
        bool useless = false;
        int oldls = laststep;

        switch (laststep) {
            case 0: // up
                boardcopy[(dY == 0) ? 14 : (dY - 1)][dX] = false;
                dY = (dY == 0) ? 14 : (dY - 1);
                odY = dY;
                odX = dX;
                while (true) {
                    dY = (dY == 0) ? 14 : (dY - 1);
                    if (!boardcopy[dY][dX]) {
                        for (int i = 0; i < positions.size(); i++) {
                            if (i != myId) {
                                if (make_pair(dX, dY) == positions[i] || make_pair(odX, odY) == positions[i]) {
                                    // cerr << "useless" << endl;
                                    useless = true;
                                    goto outofshit;
                                }
                            }
                        }
                        boardcopy[dY][dX] = 1;
                        break;
                    }    
                }
            break;

            case 1: // down
                boardcopy[(dY + 1) % 15][dX] = false;
                dY = (dY + 1) % 15;
                odY = dY;
                odX = dX;
                while (true) {
                    dY = (dY + 1) % 15;
                    if (!boardcopy[dY][dX]) {
                        for (int i = 0; i < positions.size(); i++) {
                            if (i != myId) {
                                if (make_pair(dX, dY) == positions[i] || make_pair(odX, odY) == positions[i]) {
                                    // cerr << "useless" << endl;
                                    useless = true;
                                    goto outofshit;
                                }
                            }
                        }
                                    
                        boardcopy[dY][dX] = 1;
                        break;
                    }    
                }
            break;

            case 2: // left
                boardcopy[dY][dX=((dX == 0) ? 29 : (dX - 1))] = false;
                odY = dY;
                odX = dX;
                while (true) {
                    dX = (dX == 0) ? 29 : (dX - 1);
                    if (!boardcopy[dY][dX]) {
                        for (int i = 0; i < positions.size(); i++) {
                            if (i != myId) {
                                if (make_pair(dX, dY) == positions[i] || make_pair(odX, odY) == positions[i]) {
                                    // cerr << "useless" << endl;
                                    useless = true;
                                    goto outofshit;
                                }
                            }
                        }
                        boardcopy[dY][dX] = 1;
                        break;
                    }    
                }
            break;

            case 3: // right
                boardcopy[dY][dX=((dX + 1) % 30)] =false;
                odY = dY;
                odX = dX;
                while (true) {
                    dX = (dX + 1) % 30;
                    if (!boardcopy[dY][dX]) {
                        for (int i = 0; i < positions.size(); i++) {
                            if (i != myId) {
                                if (make_pair(dX, dY) == positions[i] || make_pair(odX, odY) == positions[i]) {
                                    // cerr << "useless" << endl;
                                    useless = true;
                                    goto outofshit;
                                }
                            }
                        }
                        boardcopy[dY][dX] = 1;
                        break;
                    }    
                }
            break;

        }
        
outofshit:
        if (!useless) {
            grid newWorld = conn_region(boardcopy, make_pair(dX, dY), positions, myId, positions.size(), 1);
            for (auto row: newWorld) {
                for (auto col: row) {
                    if (col) {
                        dscore++;
                    }
                }
            }
        }

        vector<pos> nbhd = neighbor(positions[myId]);

        for (int i = 0; i < 4; i++) {
            // cerr << "i = " << i << ' ';
            if (!board[nbhd[i].second][nbhd[i].first]) {
                score[i] = INT_MIN;
                // cerr << "INT_MIN" << ' ';
            }
            else {
                for (int j = 0; j < positions.size(); j++) {
                    if (j == myId) {
                        score[i] = 0;
                        if (i == laststep && !survival)  
                            score[i]-=4;
                        for (pos p: neighbor(nbhd[i])) {
                            if (!board[p.second][p.first]) {
                                if (survival)
                                    score[i]+=2;
                                score[i]--;
                                //cerr << "SCORE++\n";
                            }
                        }
                        grid rgrid = conn_region(board, nbhd[i], positions, myId,\
                            positions.size(), (3 - loopcount / 30) > 1 ? (3 - loopcount / 30) : 1);
                        for (auto row: rgrid) {
                            for (auto col: row) {
                                if (col) {
                                    score[i]++;
                                    avail[i]++;
                                }
                            }
                        }
                    }
                    else if (positions[j].first != -1){
                        if (playerRegion[j][nbhd[i].second][nbhd[i].first]) {
                            score[i]++;
                        }
                        for (auto p: neighbor(positions[j])) {
                            if (p == nbhd[i]) {
                                score[i] -= 30;
                            }
                        }
                    }
                }
            }
            if (score[i] >= score[maxIndex]) {
                maxIndex = i;
                laststep = i;
            }
            // cerr << score[i] << endl;
        }
        // cerr << endl;

        // DOWN | LEFT | RIGHT | UP or DEPLOY (to clear walls)
        // cerr << maxIndex << endl;
        if (avail[maxIndex] >= 300) {
            survival = false;
        }
        else {
            survival = true;
        }
        if ((score[maxIndex] == INT_MIN 
            || (dscore*1.0/avail[maxIndex] >= 3.8 && avail[maxIndex] <= 200)
            || avail[maxIndex] <= 1) && helperBots > 0) {
            maxIndex = 4;
            survival = true;
            laststep = oldls;
        }

        loopcount++;

        cout << D[maxIndex] << endl;
    }
}

set<pos> inline neighbor_step(pos position, int step) {

    queue<pair<pos, int>> sq;
    set<pos> result;

    int count = 0;
    sq.push(make_pair(position, count));
    
    while (!sq.empty()) {

        if (count == step)
            break;
        count++;

        auto currp = sq.front();
        sq.pop();

        for (auto p: neighbor(currp.first)) {
            result.insert(p);
            sq.push(make_pair(p, count));
        }

    }

    return result;
}

vector<pos> inline neighbor(pos position) {
    vector<pos> res;
    // order: up, down, left, right
    res.push_back(make_pair(position.first, position.second == 0 ? 14 : position.second - 1));
    res.push_back(make_pair(position.first, (position.second + 1) % 15));
    res.push_back(make_pair(position.first == 0 ? 29 : position.first - 1, position.second));
    res.push_back(make_pair((position.first + 1) % 30, position.second));
    
    return res;
}

grid conn_region(grid board, const pos & start, const vector<pos> positions, 
    const int & myId, const int & playerCount, int avoid) {
    
    // cerr << "============BOARD==============" << endl;
    // for (auto row: board) {
    //     for (auto col: row) {
    //         cerr << col << ' ';
    //     }
    //     cerr << endl;
    // }
    // cerr << "==============RESBOARD============" << endl;
    
    grid resboard(15, vector<bool>(30));

    if (avoid != 0) {
        // remove the neighbor points of other players
        for (int i = 0; i < positions.size(); i++) {
            if (i != myId) {
                if (positions[i].first != -1) {
                    for (pos p: neighbor_step(positions[i], avoid)) {
                        board[p.second][p.first] = 0;
                    }
                }
            }
        }
    }

    queue<pos> sq;
    sq.push(start);

    // BFS
    while (!sq.empty()) {

        pos curr = sq.front();
        sq.pop();

        for (pos p: neighbor(curr)) {
            if (!resboard[p.second][p.first]) {
                if (board[p.second][p.first]) {
                    resboard[p.second][p.first] = 1;
                    sq.push(p);
                }
            }
        } // for
    } // while
    
    // for (auto row: resboard) {
    //     for (auto col: row) {
    //         cerr << col << ' ';
    //     }
    //     cerr << endl;
    // }
    return resboard;
    // cerr << "==========================" << endl;
}

int opposite(int dir) {
    switch(dir) {
        case 0: return 1; break;
        case 1: return 0; break;
        case 2: return 3; break;
        case 3: return 2; break;
    }
}
