#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <iostream>

using namespace std;

#define EXE_CMD -1
#define PLAYER_A 1
#define PLAYER_B 2

#define MAX_SHIPS 10
#define MAX_SIZE 6
#define MAX_CMD 16

#define STR_CLASS 4
#define STR_STATE 6

#define DES 2
#define CRU 3
#define BAT 4
#define CAR 5

#define FREE_CHAR ' '
#define SHIP_CHAR '+'
#define DESTROYED_CHAR 'x'
#define REEF_CHAR '#'

#define FORWARD 'F'
#define LEFT 'L'
#define RIGHT 'R'

#pragma once
class Interface;

#pragma once
class Board {
public:
	Interface* intf;
	char** board;
	int height, width;
	bool not_close;

	Board();
	void allocate_memory(int board_height, int board_width);
	void print();
	void place_ship(int start_x, int start_y, int end_x, int end_y, int state[STR_STATE]);
	bool shoot(int x, int y);
	void place_reef(int x, int y);
	void free_memory();
	bool close_to_ship(int x, int y);
	char get_char(int state);
};

#pragma once
class Ship
{
private:
	bool set_position(Board& board, int min_x, int max_x, int min_y, int max_y, int start_x, int start_y, int state[STR_STATE]);
	bool set_direction(char direction);

public:
	Interface* intf;
	bool placed;
	int start_x, start_y, end_x, end_y, size;
	char direction;
	int state[STR_STATE];
	char C[STR_CLASS];

	Ship();
	void set_class(int size);
	bool place_ship(Board& board, int min_x, int max_x, int min_y, int max_y, int x, int y, char direction, int state[STR_STATE]);
	void set_state(Board board);
	int get_state(char c);
};

#pragma once
class Player {
private:
	Ship ship[MAX_SIZE][MAX_SHIPS];

public:
	Interface* intf;

	int numberOfShips[MAX_SIZE], maxMoves[MAX_SIZE], numOfShips[MAX_SIZE];

	int remaining_parts;
	int min_x, max_x;
	int min_y, max_y;

	Player();
	int class_to_size(char C[STR_CLASS]);
	void set_fleet(int car, int bat, int cru, int des);
	int remaining_ships();
	void place_ship(Board& board, char C[STR_CLASS], int k, int x, int y, char direction, int state[STR_STATE]);
	void point(Interface* ptr);
	void move(Board& board, int k, char C[STR_CLASS], char direction);
	void reset_moves();
	void info(Board board, char p);
};

#pragma once
class Interface
{
private:
	Board board;
	Player player_a;
	Player player_b;
	char cmd[MAX_CMD];

	void initialize();

	// BASIC

	// State
	void print();
	void set_fleet();
	void next_player();

	// Player
	void place_ship();
	void shoot();

	// EXTENDED

	// State
	void ship_cmd();
	void init_position();
	void reef();
	void board_size();
	void save();

	// Player
	void move();

public:
	char cmd_args[100];
	char np;

	Interface();
	void run_command(int type, char command[MAX_CMD]);
	int get_number_of_command(char command[MAX_CMD]);
	int command_type(char cmd[MAX_CMD]);
	void assign_pointers();
	void throw_error(char* msg);
	int min_val(int a, int b);
	int max_val(int a, int b);
};