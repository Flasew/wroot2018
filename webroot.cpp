#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define UP "UP"
#define DOWN "DOWN"
#define DEPLOY "DEPLOY"

#define X first
#define Y second

using namespace std;
typedef pair<int, int> pos;
typedef vector<vector<bool>> grid;
/**
 * Don't run into a player's light trail! Use your helper bots at strategic moments or as a last resort to be the last drone standing!
 **/

int main()
{
    int playerCount; // the number of at the start of this game
    cin >> playerCount; cin.ignore();
    int myId; // your bot's id
    cin >> myId; cin.ignore();

    // game loop
    while (1) {
        int helperBots; // your number of charges left to deploy helper bots
        cin >> helperBots; cin.ignore();

        vector<pos> positions(playerCount);

        for (int i = 0; i < playerCount; i++) {
            int x; // your bot's coordinates on the grid (0,0) is top-left
            int y;
            cin >> x >> y; cin.ignore();
            positions[i] = make_pair(x, y);
        }

        int removalCount; // the amount walls removed this turn by helper bots
        cin >> removalCount; cin.ignore();

        grid board(15, vector<bool>(30));

        for (int r = 0; r < 15; r++)
            for (int c = 0; c < 30; c++)
                board[r][c] = 1;

        for (int i = 0; i < removalCount; i++) {
            int removeX; // the coordinates of a wall removed this turn
            int removeY;
            cin >> removeX >> removeY; cin.ignore();
            board[removeY][removeX] =  0;
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // DOWN | LEFT | RIGHT | UP or DEPLOY (to clear walls)
        cout << DOWN << endl;
    }
}

vector<pos> inline neighbor(pos position) {
    vector<pos> res;
    res.push_back(make_pair(position.X, (position.Y + 1) % 15));
    res.push_back(make_pair(position.X, (position.Y == 0 ? 14 : position.Y - 1)));
    res.push_back(make_pair((position.X + 1) % 30, position.Y));
    res.push_back(make_pair((position.X == 0 ? 29 : position.X - 1)), position.Y);
    return result;
}

void conn_region(grid board, const vector<pos> positions,
                 const int & myId) {

}


