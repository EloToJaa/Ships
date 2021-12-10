#include "Header.h"

Interface::Interface() {
    initialize();
    
    int type = -1, curr_type;
    while (cin >> cmd) {
        curr_type = command_type(cmd);
        if ((curr_type == PLAYER_A && np == 'B') || (curr_type == PLAYER_B && np == 'A')) {
            strncpy(cmd_args, "", 1);
            throw_error((char*)"THE OTHER PLAYER EXPECTED");
            break;
        }
        if (curr_type == EXE_CMD) {
            run_command(type, cmd);
        }
        else if (curr_type == type) {
            if (type == PLAYER_A) np = 'B';
            else if (type == PLAYER_B) np = 'A';
        }
        else {
            type = curr_type;
            player_a.reset_moves();
            player_b.reset_moves();
        }
        if (player_a.remaining_parts == 0) {
            cout << "B won\n";
            break;
        }
        if (player_b.remaining_parts == 0) {
            cout << "A won\n";
            break;
        }
    }
    board.free_memory();
}

void Interface::initialize() {
    board.allocate_memory(21, 10);

    player_a.min_x = 0;
    player_a.max_x = 9;
    player_a.min_y = 0;
    player_a.max_y = 9;

    player_b.min_x = 0;
    player_b.max_x = 9;
    player_b.min_y = 11;
    player_b.max_y = 20;

    strncpy(cmd_args, "", 1);

    assign_pointers();
    np = 'A';
}

void Interface::assign_pointers() {
    board.intf = this;
    player_a.point(this);
    player_b.point(this);
}

void Interface::throw_error(char* msg) {
    cout << "INVALID OPERATION \"" << cmd << " " << cmd_args << "\": " << msg;
    // cout << "\n";
    exit(1);
}

int Interface::get_number_of_command(char command[MAX_CMD]) {
    const int numberOfCommands = 17;
    const char commands[numberOfCommands][MAX_CMD] = {
        "PRINT",
        "SET_FLEET",
        "NEXT_PLAYER",
        "BOARD_SIZE",
        "INIT_POSITION",
        "REEF",
        "SHIP",
        "EXTENDED_SHIPS",
        "SET_AI_PLAYER",
        "SRAND",
        "SAVE",
        "AUTO_SHOOTING",
        "INFORMATION",
        "PLACE_SHIP",
        "SHOOT",
        "MOVE",
        "SPY"
    };

    for (int i = 0; i < numberOfCommands; i++) {
        if (strcmp(command, commands[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int Interface::command_type(char cmd[MAX_CMD]) {
    if (strcmp(cmd, "[state]") == 0) {
        return 0;
    }
    if (strcmp(cmd, "[playerA]") == 0) {
        return 1;
    }
    if (strcmp(cmd, "[playerB]") == 0) {
        return 2;
    }
    return -1;
}

int Interface::min_val(int a, int b) {
    if (a < b) return a;
    return b;
}

int Interface::max_val(int a, int b) {
    if (a > b) return a;
    return b;
}

void Interface::run_command(int type, char command[MAX_CMD]) {
    
    switch (get_number_of_command(command)) {
    case 0:
        print();
        break;

    case 1:
        set_fleet();
        break;

    case 2:
        next_player();
        break;

    case 3:
        board_size();
        break;

    case 4:
        init_position();
        break;

    case 5:
        reef();
        break;

    case 6:
        ship_cmd();
        break;

    case 10:
        save();
        break;

    case 13:
        place_ship();
        break;

    case 14:
        shoot();
        break;

    case 15:
        move();
        break;

    default:
        cout << "Invalid command\n";
        break;
    }
}