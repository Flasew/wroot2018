#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
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
grid conn_region(grid board, const vector<pos> positions, 
    const int & myId, const int & playerCount, bool avoid = true);

vector<string> D = {"UP", "DOWN", "LEFT", "RIGHT"};

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

    // game loop
    while (1) {
        int helperBots; // your number of charges left to deploy helper bots
        cin >> helperBots; cin.ignore();

        vector<pos> positions(playerCount);

        for (int i = 0; i < playerCount; i++) {
            int x; // your bot's coordinates on the grid (0,0) is top-left
            int y;
            cin >> x >> y; cin.ignore();
            board[y][x] = false;
            positions[i] = make_pair(x, y);
        }

        int removalCount; // the amount walls removed this turn by helper bots
        cin >> removalCount; cin.ignore();

        for (int i = 0; i < removalCount; i++) {
            int removeX; // the coordinates of a wall removed this turn
            int removeY;
            cin >> removeX >> removeY; cin.ignore();
            board[removeY][removeX] = true;
            cerr << "RY, RX" << removeY << ',' << removeX << endl; 
        }
        cerr << "=============BOARDOUT=============" << endl;
        for (auto row: board) {
            for (auto col: row) {
                cerr << col << ' ';
            }
            cerr << endl;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        vector<grid> playerRegion(playerCount);
        vector<int> score(4);
        int maxIndex = 0;

        for (int i = 0; i < playerCount; i++) {
            playerRegion[i] = conn_region(board, positions, myId, playerCount);
        }
        
        vector<pos> nbhd = neighbor(positions[myId]);

        for (int i = 0; i < 4; i++) {
            cerr << "i = " << i << ' ';
            if (!board[nbhd[i].second][nbhd[i].first]) {
                score[i] = INT_MIN;
                cerr << "INT_MIN" << ' ';
            }
            else {
                for (int j = 0; j < playerCount; j++) {
                    if (playerRegion[j][nbhd[i].second][nbhd[i].first]) {
                        if (j == myId) {
                            score[i] -= 4;
                            for (pos p: neighbor(nbhd[i])) {
                                if (!board[p.second][p.first]) {
                                    score[i]++;
                                    cerr << "SCORE++\n";
                                }
                            }
                        }
                        else {
                            score[i]++;
                        }  
                    }
                }
            }
            if (score[i] > score[maxIndex]) {
                maxIndex = i;
            }
            cerr << score[i] << endl;
        }
        cerr << endl;

        // DOWN | LEFT | RIGHT | UP or DEPLOY (to clear walls)
        cerr << maxIndex << endl;
        cout << D[maxIndex] << endl;
    }
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

grid conn_region(grid board, const vector<pos> positions, 
    const int & myId, const int & playerCount, bool avoid) {
    
    cerr << "============BOARD==============" << endl;
    for (auto row: board) {
        for (auto col: row) {
            cerr << col << ' ';
        }
        cerr << endl;
    }
    cerr << "==============RESBOARD============" << endl;
    
    grid resboard(15, vector<bool>(30));

    if (avoid) {
        // remove the neighbor points of other players
        for (int i = 0; i < playerCount; i++) {
            if (i != myId) {
                for (pos p: neighbor(positions[i])) {
                    board[p.second][p.first] = 0;
                }
            }
        }
    }

    queue<pos> sq;
    sq.push(positions[myId]);

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
    
    for (auto row: resboard) {
        for (auto col: row) {
            cerr << col << ' ';
        }
        cerr << endl;
    }
    return resboard;
    cerr << "==========================" << endl;
}


