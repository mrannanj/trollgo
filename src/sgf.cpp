#include "sgf.h"
#include <fstream>
#include <sstream>

using namespace std;

bool readSGF(const char *filename, GameState &gs) {
    ifstream f(filename);
    if (!f.good()) {
        f.close();
        return false;
    }
    stringstream s;
    s << f.rdbuf();
    f.close();
    string text(s.str());

    size_t idx1 = 0, idx2 = 0;
    size_t row, col;
    bool black = true;
    while (true) {
        idx1 = text.find(black ? ";B[" : ";W[", idx2);
        if (idx1 == string::npos)
            break;
        idx2 = text.find("]", idx1);
        if (idx2 == string::npos)
            return false;
        if (idx2 - idx1 == 3) {
            // Pass
            row = -1;
            col = -1;
        } else if (idx2 - idx1 == 5) {
            row = text[idx1 + 3 + 1] - 'a';
            col = text[idx1 + 3 + 0] - 'a';
        } else {
            // Invalid
            return false;
        }
        gs.attemptMove(row, col, true);
        black = !black;
    }
    return true;
}
