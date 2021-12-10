#include "Header.h"

void Interface::move() {
    int k;
    char C[STR_CLASS];
    char x;
    cin >> k >> C >> x;

    sprintf(cmd_args, "%d %s %c", k, C, x);

    if (np == 'A') player_a.move(board, k, C, x);
    else if (np == 'B') player_b.move(board, k, C, x);
}