#include "Header.h"

Board::Board() {
	height = -1;
	width = -1;

	board = NULL;
	intf = NULL;

	not_close = false;
};

void Board::allocate_memory(int board_height, int board_width) {
	height = board_height;
	width = board_width;

	board = (char**)calloc(height + 1, sizeof(char*));
	if (board == NULL) exit(0);
	for (int i = 0; i < height; i++) {
		board[i] = (char*)calloc(width + 1, sizeof(char));
		if (board[i] == NULL) exit(0);
		for (int j = 0; j < width; j++) {
			board[i][j] = FREE_CHAR;
		}
	}
}

void Board::print() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << board[i][j];
		}
		cout << "\n";
	}
}

void Board::free_memory() {
	for (int i = 0; i < height; i++) {
		free(board[i]);
	}
	free(board);
}

char Board::get_char(int state) {
	if (state == 1) return SHIP_CHAR;
	if (state == 0) return DESTROYED_CHAR;
	if (state == -1) return FREE_CHAR;
	return '#';
}

void Board::place_ship(int start_x, int start_y, int end_x, int end_y, int state[STR_STATE]) {
	// place ship on board
	//cout << "PLACE: (" << start_x << "," << start_y << ") (" << end_x << "," << end_y << ")\n";
	int k = 0;
	if (start_x == end_x) {
		if (end_y > start_y) {
			for (int y = start_y; y <= end_y; y++) {
				if (board[y][start_x] == REEF_CHAR) {
					intf->throw_error((char*)"PLACING SHIP ON REEF");
				}
			}

			for (int y = start_y; y <= end_y; y++) {
				if (close_to_ship(start_x, y)) {
					intf->throw_error((char*)"PLACING SHIP TOO CLOSE TO OTHER SHIP");
				}
			}

			for (int y = start_y; y <= end_y; y++) {
				board[y][start_x] = get_char(state[k]);
				k++;
			}
		}
		else {
			for (int y = start_y; y >= end_y; y--) {
				if (board[y][start_x] == REEF_CHAR) {
					intf->throw_error((char*)"PLACING SHIP ON REEF");
				}
			}

			for (int y = start_y; y >= end_y; y--) {
				if (close_to_ship(start_x, y)) {
					intf->throw_error((char*)"PLACING SHIP TOO CLOSE TO OTHER SHIP");
				}
			}

			for (int y = start_y; y >= end_y; y--) {
				board[y][start_x] = get_char(state[k]);
				k++;
			}
		}
	}
	else if (start_y == end_y) {
		if (end_x > start_x) {
			for (int x = start_x; x <= end_x; x++) {
				if (board[start_y][x] == REEF_CHAR) {
					intf->throw_error((char*)"PLACING SHIP ON REEF");
				}
			}

			for (int x = start_x; x <= end_x; x++) {
				if (close_to_ship(x, start_y)) {
					intf->throw_error((char*)"PLACING SHIP TOO CLOSE TO OTHER SHIP");
				}
			}

			for (int x = start_x; x <= end_x; x++) {
				board[start_y][x] = get_char(state[k]);
				k++;
			}
		}
		else {
			for (int x = start_x; x >= end_x; x--) {
				if (board[start_y][x] == REEF_CHAR) {
					intf->throw_error((char*)"PLACING SHIP ON REEF");
				}
			}

			for (int x = start_x; x >= end_x; x--) {
				if (close_to_ship(x, start_y)) {
					intf->throw_error((char*)"PLACING SHIP TOO CLOSE TO OTHER SHIP");
				}
			}

			for (int x = start_x; x >= end_x; x--) {
				board[start_y][x] = get_char(state[k]);
				k++;
			}
		}
	}
}

bool Board::shoot(int x, int y) {
	// validate x and y cords
	if (x < 0 || x >= width || y < 0 || y >= height) {
		intf->throw_error((char*)"FIELD DOES NOT EXIST");
	}
	//cout << "SHOOT: " << y << " " << x << " C="<<board[y][x]<< "\n";
	if (board[y][x] == SHIP_CHAR) {
		board[y][x] = DESTROYED_CHAR;
		return true;
	}
	return false;
}

bool Board::close_to_ship(int x, int y) {
	if (not_close) return false;
	if (x != 0 && board[y][x - 1] == SHIP_CHAR) return true;
	if (x != width - 1 && board[y][x + 1] == SHIP_CHAR) return true;
	if (y != 0 && board[y - 1][x] == SHIP_CHAR) return true;
	if (y != height - 1 && board[y + 1][x] == SHIP_CHAR) return true;
	return false;
}

void Board::place_reef(int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height) {
		intf->throw_error((char*)"REEF IS NOT PLACED ON BOARD");
	}

	board[y][x] = REEF_CHAR;
}
