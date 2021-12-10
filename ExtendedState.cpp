#include "Header.h"

void Interface::ship_cmd() {
    char p, D;
    char C[STR_CLASS], a[STR_STATE];
    int y, x, k;

    cin >> p >> y >> x >> D >> k >> C >> a;

    sprintf(cmd_args, "%c %d %d %c %d %s %s", p, y, x, D, k, C, a);

    int state[STR_STATE];
    for (int i = 0; i < player_a.class_to_size(C); i++) {
        state[i] = (a[i] - 48);
    }

    if (p == 'A') player_a.place_ship(board, C, k, x, y, D, state);
    else if (p == 'B') player_b.place_ship(board, C, k, x, y, D, state);
}

void Interface::init_position() {
    char p;
    int y1, x1, y2, x2;

    cin >> p >> y1 >> x1 >> y2 >> x2;

    sprintf(cmd_args, "%c %d %d %d %d", p, y1, x1, y2, x2);

    int mnX = min_val(x1, x2);
    int mxX = max_val(x1, x2);
    int mnY = min_val(y1, y2);
    int mxY = max_val(y1, y2);

    if (p == 'A') {
        player_a.min_x = mnX;
        player_a.max_x = mxX;
        player_a.min_y = mnY;
        player_a.max_y = mxY;
    }
    else if (p == 'B') {
        player_b.min_x = mnX;
        player_b.max_x = mxX;
        player_b.min_y = mnY;
        player_b.max_y = mxY;
    }
}

void Interface::reef() {
    int y, x;
    cin >> y >> x;

    sprintf(cmd_args, "%d %d", y, x);

    board.place_reef(x, y);
}

void Interface::board_size() {
    int y, x;
    cin >> y >> x;

    sprintf(cmd_args, "%d %d", y, x);

    board.free_memory();
    board.allocate_memory(y, x);
}

void Interface::save() {
    sprintf(cmd_args, "");

    // state
    cout << "[state]\n";
    cout << "BOARD_SIZE " << board.height << " " << board.width << "\n";
    cout << "NEXT_PLAYER " << np << "\n";

    player_a.info(board, 'A');
    player_b.info(board, 'B');

    cout << "[state]\n";
}