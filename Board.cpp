#include "Board.hpp"

#include <iostream>
#include <ftxui/dom/elements.hpp>

#include "ftxui/component/component.hpp"
#include "ftxui/dom/canvas.hpp"
//#include "ftxui/component/mouse.hpp"

Board::Board(int bSize) : boardSize((unsigned int)bSize), life(bSize) {}

ftxui::Element Board::render() {
	auto c = ftxui::Canvas(4*boardSize - 2, 4*boardSize);
	const auto &board = life.getBoard();
	for(int x = 0; x < boardSize; x++) {
		for(int y = 0; y < boardSize; y++) {
			if(x < boardSize - 1) { c.DrawText(4*x + 2, 4*y, " "); }
			if(board[x][y]) { c.DrawText(4*x, 4*y, "o"); }
			else c.DrawText(4*x, 4*y, ".");
			if(editMode && x == mouse_x && y == mouse_y) {
				c.DrawText(4*x, 4*y, "O");
			}
		}
	}
	return canvas(std::move(c));
}

void Board::toggleEditMode() {
	editMode = !editMode;
}

void Board::onMouse(const ftxui::Mouse &mouse) {
	// Only update the mouse position/register clicks at valid board entries
	if(mouse.x < 0 || mouse.x >= 2*boardSize - 1 || mouse.y < 0 || mouse.y >= boardSize) { return; }
	if(mouse.x % 2 == 1) { return; }
	
	// These are in "board coordinates".
	mouse_x = mouse.x/2;
	mouse_y = mouse.y;
	
	bool mouseWasHeld = mouseHeld;
	mouseHeld = (mouse.motion == ftxui::Mouse::Motion::Pressed && mouse.button == ftxui::Mouse::Button::Left);
	
	bool leftClicked = !mouseWasHeld && mouseHeld;
	
	if(leftClicked && editMode) {
		life.toggle(mouse_x, mouse_y);
	}
}

bool Board::updateLifeIfSimulating() {
	if(!editMode) { life.update(); }
	return !editMode;
}
