#include "Header.h"

void Interface::print() {
    int x;
    cin >> x;

    sprintf(cmd_args, "%d", x);

    if (x == 0) {
        // basic
        board.print();

        int rem_a = player_a.remaining_parts;
        int rem_b = player_b.remaining_parts;
        if (rem_a == -1) rem_a = 0;
        if (rem_b == -1) rem_b = 0;
        cout << "PARTS REMAINING:: A : " << rem_a << " B : " << rem_b;
        cout << "\n";
        //cout << "REMAINING SHIPS:" << player_a.remaining_ships() << ", " << player_b.remaining_ships() << "\n";
    }
    else if (x == 1) {
        // extended
    }
}

void Interface::set_fleet() {
    char p;
    int car, bat, cru, des;
    cin >> p >> car >> bat >> cru >> des;

    sprintf(cmd_args, "%c %d %d %d %d", p, car, bat, cru, des);

    if (p == 'A') {
        player_a.set_fleet(car, bat, cru, des);
    }
    else if (p == 'B') {
        player_b.set_fleet(car, bat, cru, des);
    }
}

void Interface::next_player() {
    char p;
    cin >> p;

    sprintf(cmd_args, "%c", p);

    if (p != 'A' && p != 'B') return;
    np = p;
}

void Interface::place_ship() {
    char D;
    char C[STR_CLASS];
    int y, x, k;

    cin >> y >> x >> D >> k >> C;

    sprintf(cmd_args, "%d %d %c %d %s", y, x, D, k, C);

    int state[STR_STATE];
    for (int i = 0; i < STR_STATE - 1; i++) {
        state[i] = 1;
    }

    if(np == 'A') player_a.place_ship(board, C, k, x, y, D, state);
    else if (np == 'B') player_b.place_ship(board, C, k, x, y, D, state);
}

void Interface::shoot() {
    int y, x;
    cin >> y >> x;

    sprintf(cmd_args, "%d %d", y, x);

    if (player_a.remaining_ships() != 0 || player_b.remaining_ships() != 0) {
        throw_error((char*)"NOT ALL SHIPS PLACED");
    }

    if (np == 'A') {
        bool shot = board.shoot(x, y);
        if (shot) player_b.remaining_parts --;
    }
    else if (np == 'B') {
        bool shot = board.shoot(x, y);
        if (shot) player_a.remaining_parts --;
    }
}