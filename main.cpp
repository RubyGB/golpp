#include <iostream>
#include <chrono>
#include <thread> // sleep_for
#include <ftxui/dom/elements.hpp>

#include "Board.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/canvas.hpp"
#include "ftxui/screen/color.hpp"

const int MAX_BOARD_SIZE = 50; // This is an understimate for terminals that could display more than 50 lines at once AND could display 100+ characters per row.

int main() {
	using namespace ftxui;
	
	// Tutorial text
	std::cout << "Welcome to a (periodic) Game of Life simulation." << std::endl;
	std::cout << "This program starts in 'edit mode'. Press [e] to toggle between this and 'simulation mode'." << std:: endl;
	std::cout << "While in edit mode, left-click to toggle individual cells." << std::endl;
	std::cout << "Once you are satisfied with the initial board layout, switch to simulation mode to observe the simulation." << std::endl;
	std::cout << "To toggle simulation speed: [1] is 1x (10fps), [2] is 2x (20fps) and [3] is 4x (40fps)." << std::endl;
	std::cout << "Finally, to quit the simulation, press [q]." << std::endl << std::endl;
	std::cout << "To begin, type an integer board size in the range [0, " << MAX_BOARD_SIZE << "] and hit [Enter]." << std::endl;
	
	int userBoardSize;
	std::cin >> userBoardSize;
	if(userBoardSize < 0 || userBoardSize > MAX_BOARD_SIZE) {
		std::cout << "Invalid board size. Terminating program." << std::endl;
		return -1;
	}
	
	Board board(userBoardSize);
	bool shouldQuit = false;
	int simulationSpeed = 1;
	auto fps = [](int ss) { // fps for given simulation speed
		if(ss < 1) { ss = 1;}
		if(ss >= 3) { ss = 4; }
		return 100 / ss;
	};
	
	// helper function
	auto matchCharacter = [](const ftxui::Event &e, std::string c) -> bool {
		return e.is_character() && e.character() == c;
	};
	
	std::function<Element()> render = std::bind(&Board::render, &board);
	auto renderer = Renderer(render);
	renderer |= CatchEvent([&](Event e) {
		if(e.is_mouse()) {
			board.onMouse(e.mouse());
			return true;
		}
		if(matchCharacter(e, "e")) { board.toggleEditMode(); }
		if(matchCharacter(e, "q")) { shouldQuit = true; }
		if(matchCharacter(e, "1")) { simulationSpeed = 1; }
		if(matchCharacter(e, "2")) { simulationSpeed = 2; }
		if(matchCharacter(e, "3")) { simulationSpeed = 3; }
		return false;
	});
	
	auto screen = ScreenInteractive::FitComponent();
	
	// Have a separate thread which regularly posts GOL updates to the screen.
	// Using this until ftxui::Loop is included in a major release
	std::thread updateGOL([&] {
		while(!shouldQuit) {
			std::this_thread::sleep_for(std::chrono::milliseconds( fps(simulationSpeed) ));
			screen.Post([&] { board.updateLifeIfSimulating(); });
			screen.Post(ftxui::Event::Custom);
		}
		screen.ExitLoopClosure()();
	});
	
	screen.Loop(renderer);
	updateGOL.join();
	
	return 0;
}
