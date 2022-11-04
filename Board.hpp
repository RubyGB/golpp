#pragma once
#include "Life.hpp"

#include "ftxui/component/component.hpp" // for Renderer

class Board {
private:
	bool editMode = true;
	
	bool mouseHeld = false;
	int mouse_x = 0, mouse_y = 0;
	
	unsigned int boardSize;
	Life life;
public:
	Board(int boardSize);
	
	ftxui::Element render();
	void toggleEditMode();
	void onMouse(const ftxui::Mouse &mouse);
	// Returns !editMode (e.g., true if a GOL update took place)
	bool updateLifeIfSimulating(); // update GOL state
};
