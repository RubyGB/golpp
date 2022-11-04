#include "Life.hpp"
#include <stdexcept>
#include <iostream>

// Wrap x into the range [0, boardSize).
int Life::wrap(int k) const {
	while(k < 0) { k += boardSize; }
	while(k >= boardSize) { k -= boardSize; }
	return k;
}

unsigned int Life::numLiveNeighbors(int x, int y) const {
	unsigned int count = 0;
	int top = wrap(y-1), bottom = wrap(y+1);
	for(int i = -1; i <= 1; i++) {
		if(board[wrap(x+i)][top]) count++;
		if(board[wrap(x+i)][bottom]) count++;
	}
	if(board[wrap(x-1)][y]) count++;
	if(board[wrap(x+1)][y]) count++;
	return count;
}

bool Life::lives(int x, int y) const {
	int live = numLiveNeighbors(x,y);
	if(!board[x][y] && live == 3) {
		return true;
	}
	if(board[x][y] && !(live == 2 || live == 3)) {
		return false;
	}
	return board[x][y];
}

Life::Life(int bSize) : boardSize((unsigned int)bSize) {
	if(boardSize < 3) {
		throw std::runtime_error("Board size for periodic Game of Life must be at least 3.");
	}
	
	// Initialize board with all off entries.
	for(int i = 0; i < boardSize; i++) {
		std::vector<bool> column;
		for(int j = 0; j < boardSize; j++) {
			column.push_back(false);
		}
		board.push_back(column);
	}
}

void Life::update() {
	std::vector<std::vector<bool>> nextStage;
	for(int x = 0; x < boardSize; x++) {
		std::vector<bool> col;
		for(int y = 0; y < boardSize; y++) {
			col.push_back(lives(x,y));
		}
		nextStage.push_back(col);
	}
	board.swap(nextStage);
}

void Life::toggle(int x, int y) {
	board[x][y] = !board[x][y];
}

const std::vector<std::vector<bool>> &Life::getBoard() const {
	return board;
}
