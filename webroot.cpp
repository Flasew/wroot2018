#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef pos pair<int, int>;
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

        vector<pos> positions;

        for (int i = 0; i < playerCount; i++) {
            int x; // your bot's coordinates on the grid (0,0) is top-left
            int y;
            cin >> x >> y; cin.ignore();
            if (i == playerCount)   myPos = make_pair(x, y);
        }

        int removalCount; // the amount walls removed this turn by helper bots
        cin >> removalCount; cin.ignore();
        for (int i = 0; i < removalCount; i++) {
            int removeX; // the coordinates of a wall removed this turn
            int removeY;
            cin >> removeX >> removeY; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // DOWN | LEFT | RIGHT | UP or DEPLOY (to clear walls)
        cout << "DOWN" << endl;
    }
}
