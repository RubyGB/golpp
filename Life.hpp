#pragma once

#include <vector>

class Life {
private:
	unsigned int boardSize;
	std::vector<std::vector<bool>> board;

	int wrap(int k) const; // wrap boundary
	unsigned int numLiveNeighbors(int x, int y) const;
	bool lives(int x, int y) const;
public:
	Life(int boardSize);
	void update();
	void toggle(int x, int y);

	const std::vector<std::vector<bool>> &getBoard() const;
};
