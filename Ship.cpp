#include "Header.h"

Ship::Ship() {
	intf = NULL;

	placed = false;
	direction = 'B';
	start_x = -1;
	start_y = -1;
	end_x = -1;
	end_y = -1;
	size = -1;

	for (int i = 0; i < STR_STATE - 1; i++) {
		state[i] = -1;
	}
	for (int i = 0; i < STR_CLASS - 1; i++) {
		C[i] = -1;
	}
}

bool Ship::set_position(Board &board, int min_x, int max_x, int min_y, int max_y, int start_x, int start_y, int state[STR_STATE]) {	
	int end_x, end_y;
	if (direction == 'S') {
		end_y = start_y - size + 1;
		if (end_y < min_y) return true;

		this->end_x = start_x;
		this->end_y = end_y;

		board.place_ship(start_x, start_y, start_x, end_y, state);
	}
	else if (direction == 'N') {
		end_y = start_y + size - 1;
		if (end_y > max_y) return true;

		this->end_x = start_x;
		this->end_y = end_y;

		board.place_ship(start_x, start_y, start_x, end_y, state);
	}
	else if (direction == 'E') {
		end_x = start_x - size + 1;
		if (end_x < min_x) return true;

		this->end_x = end_x;
		this->end_y = start_y;

		board.place_ship(start_x, start_y, end_x, start_y, state);
	}
	else if (direction == 'W') {
		end_x = start_x + size - 1;
		if (end_x > max_x) return true;

		this->end_x = end_x;
		this->end_y = start_y;

		board.place_ship(start_x, start_y, end_x, start_y, state);
	}
	else return true;

	this->start_x = start_x;
	this->start_y = start_y;

	return false;
}

void Ship::set_class(int size) {
	if (size < DES || size > CAR) return;
	this->size = size;
}

bool Ship::set_direction(char direction) {
	if (direction != 'N' && direction != 'S' && direction != 'W' && direction != 'E') return true;
	this->direction = direction;
	return false;
}

bool Ship::place_ship(Board &board, int min_x, int max_x, int min_y, int max_y, int x, int y, char direction, int state[STR_STATE]) {
	bool dir = set_direction(direction);
	if (dir) return true;

	bool pos = set_position(board, min_x, max_x, min_y, max_y, x, y, state);
	if (pos) {
		intf->throw_error((char*)"NOT IN STARTING POSITION");
		return true;
	}
	if (x < 0 || x > board.width || y < 0 || y > board.height) {
		intf->throw_error((char*)"SHIP WENT FROM BOARD");
	}
	//cout << "PLACED:" << intf->cmd_args << "\n";
	placed = true;
	return false;
}

int Ship::get_state(char c) {
	if (c == SHIP_CHAR) return 1;
	if (c == DESTROYED_CHAR) return 0;
	if (c == FREE_CHAR) return -1;
	return -2;
}

void Ship::set_state(Board board) {
	int k = 0;
	if (start_x == end_x) {
		if (end_y > start_y) {
			for (int y = start_y; y <= end_y; y++) {
				this->state[k] = get_state(board.board[y][start_x]);
				k++;
			}
		}
		else {
			for (int y = start_y; y >= end_y; y--) {
				this->state[k] = get_state(board.board[y][start_x]);
				k++;
			}
		}
	}
	else if (start_y == end_y) {
		if (end_x > start_x) {
			for (int x = start_x; x <= end_x; x++) {
				this->state[k] = get_state(board.board[start_y][x]);
				k++;
			}
		}
		else {
			for (int x = start_x; x >= end_x; x--) {
				this->state[k] = get_state(board.board[start_y][x]);
				k++;
			}
		}
	}
}