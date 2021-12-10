#include "Header.h"

Player::Player() {
    // set default values
    set_fleet(1, 2, 3, 4);

    intf = NULL;

    min_x = -1;
    max_x = -1;
    min_y = -1;
    max_y = -1;
}

void Player::set_fleet(int car, int bat, int cru, int des) {
    numberOfShips[0] = numOfShips[0] = 0;
    numberOfShips[1] = numOfShips[1] = 0;
    
    numberOfShips[DES] = numOfShips[DES] = des;
    numberOfShips[CRU] = numOfShips[CRU] = cru;
    numberOfShips[BAT] = numOfShips[BAT] = bat;
    numberOfShips[CAR] = numOfShips[CAR] = car;

    remaining_parts = -1;

    for (int i = DES; i <= CAR; i++) {
        for (int j = 0; j < MAX_SHIPS; j++) {
            ship[i][j].set_class(i);
        }
    }
}

int Player::remaining_ships() {
    int sum = 0;
    for (int i = DES; i <= CAR; i++) {
        sum += numberOfShips[i];
    }
    return sum;
}

int Player::class_to_size(char C[STR_CLASS]) {
    if (strcmp(C, "CAR") == 0) return CAR;
    if (strcmp(C, "BAT") == 0) return BAT;
    if (strcmp(C, "CRU") == 0) return CRU;
    if (strcmp(C, "DES") == 0) return DES;
    return -1;
}

void Player::place_ship(Board &board, char C[STR_CLASS], int k, int x, int y, char direction, int state[STR_STATE]) {
    int size = class_to_size(C);
    if (size == -1) return;

    if (ship[size][k].placed) {
        intf->throw_error((char*)"SHIP ALREADY PRESENT");
    }
    if (numberOfShips[size] == 0) {
        intf->throw_error((char*)"ALL SHIPS OF THE CLASS ALREADY SET");
    }

    if (remaining_parts == -1) remaining_parts = 0;
    for (int i = 0; i < size; i++) {
        remaining_parts += state[i];
    }
    numberOfShips[size] --;

    for (int i = 0; i < STR_CLASS - 1; i++) {
        ship[size][k].C[i] = C[i];
    }

    ship[size][k].set_class(size);
    ship[size][k].place_ship(board, min_x, max_x, min_y, max_y, x, y, direction, state);
}

void Player::point(Interface* ptr) {
    intf = ptr;
    for (int i = 0; i <= CAR; i++) {
        for (int j = 0; j < MAX_SHIPS; j++) {
            ship[i][j].intf = intf;
        }
    }
}

void Player::move(Board& board, int k, char C[STR_CLASS], char direction) {
    int state[STR_STATE];
    int size = class_to_size(C);

    if (maxMoves[size] == 0) {
        intf->throw_error((char*)"SHIP MOVED ALREADY");
    }
    maxMoves[size] --;

    ship[size][k].set_state(board);
    ship[size][k].placed = false;
    numberOfShips[size] += 2;

    Ship curr_ship = ship[size][k];

    // remove the ship
    for (int i = 0; i < size; i++) {
        state[i] = -1;
    }

    board.not_close = true;
    place_ship(board, C, k, curr_ship.start_x, curr_ship.start_y, curr_ship.direction, state);

    ship[size][k].placed = false;
    board.not_close = false;

    for (int i = 0; i < size; i++) {
        state[i] = curr_ship.state[i];
    }

    // place the ship again
    if (direction == FORWARD) {
        if (curr_ship.direction == 'N')
            place_ship(board, C, k, curr_ship.start_x, curr_ship.start_y - 1, curr_ship.direction, state);
        else if (curr_ship.direction == 'S')
            place_ship(board, C, k, curr_ship.start_x, curr_ship.start_y + 1, curr_ship.direction, state);
        else if (curr_ship.direction == 'E')
            place_ship(board, C, k, curr_ship.start_x + 1, curr_ship.start_y, curr_ship.direction, state);
        else if (curr_ship.direction == 'W')
            place_ship(board, C, k, curr_ship.start_x - 1, curr_ship.start_y, curr_ship.direction, state);
    }

    else if (direction == RIGHT) {
        if (curr_ship.direction == 'N')
            place_ship(board, C, k, curr_ship.start_x + size - 1, curr_ship.start_y - 1, 'E', state);
        else if (curr_ship.direction == 'S')
            place_ship(board, C, k, curr_ship.start_x - size + 1, curr_ship.start_y + 1, 'W', state);
        else if (curr_ship.direction == 'E')
            place_ship(board, C, k, curr_ship.start_x + 1, curr_ship.start_y + size - 1, 'S', state);
        else if (curr_ship.direction == 'W')
            place_ship(board, C, k, curr_ship.start_x - 1, curr_ship.start_y - size + 1, 'N', state);
    }

    else if (direction == LEFT) {
        if (curr_ship.direction == 'N')
            place_ship(board, C, k, curr_ship.start_x - size + 1, curr_ship.start_y - 1, 'W', state);
        else if (curr_ship.direction == 'S')
            place_ship(board, C, k, curr_ship.start_x + size - 1, curr_ship.start_y + 1, 'E', state);
        else if (curr_ship.direction == 'E')
            place_ship(board, C, k, curr_ship.start_x + 1, curr_ship.start_y - size + 1, 'N', state);
        else if (curr_ship.direction == 'W')
            place_ship(board, C, k, curr_ship.start_x - 1, curr_ship.start_y + size - 1, 'S', state);
    }

}

void Player::reset_moves() {
    maxMoves[0] = 0;
    maxMoves[1] = 0;
    maxMoves[DES] = 3;
    maxMoves[CRU] = 3;
    maxMoves[BAT] = 3;
    maxMoves[CAR] = 2;
}

void Player::info(Board board, char p) {
    cout << "INIT_POSITION "<< p << " " << min_y << " " << min_x << " " << max_y << " " << max_x << "\n";
    cout << "SET_FLEET " << p << " " << numOfShips[CAR] << " " << numOfShips[BAT] << " " << numOfShips[CRU] << " " << numOfShips[DES] << "\n";
    for (int i = CAR; i >= DES; i--) {
        for (int j = 0; j < MAX_SHIPS; j++) {
            if (ship[i][j].placed) {
                cout << "SHIP "<< p << " " << ship[i][j].start_y << " " << ship[i][j].start_x << " " << ship[i][j].direction << " " << j << " ";
                for (int k = 0; k < STR_CLASS - 1; k++) {
                    cout << ship[i][j].C[k];
                }
                cout << " ";
                ship[i][j].set_state(board);
                for (int k = 0; k < ship[i][j].size; k++) {
                    cout << ship[i][j].state[k];
                }
                cout << "\n";
            }
        }
    }
}