#include <stdio.h>
#include <ncurses.h>
#include "Render.h"

#define MENU_HEIGHT 7
#define STATS_WIDTH 12
#define MESSAGE_LENGTH 200

char const *froggoDown = "/\x20-\x20\\\x20\n"
	"|\x20 \x20|\x20\n"
	"0\x70~\x10""0\x70";
char const *froggoRight = "/\x20-\x20""0\x70\n"
	"|\x20 \x20~\x10\n"
	"\\\x20-\x20""0\x70";
char const *froggoUp = "0\x70~\x10""0\x70\n"
	"|\x20 \x20|\x20\n"
	"\\\x20-\x20/\x20";
char const *froggoLeft = "0\x70-\x20\\\x20\n"
	"~\x10 \x20|\x20\n"
	"0\x70-\x20/\x20";


/**
 * Checks if the screen is big enough to allow play and loops until it is.
 * @return true if all is well, and false if the player asked to quit.
 */
bool checkScreen() {
	while (true) {
		if (COLS >= 80 && LINES >= 25) return true;
		clear();
		printw(
			"Terminal must be at least 80x25 to play, but is %dx%d\n",
			COLS,
			LINES
		);
		printw("Press q to quit");
		refresh();
		if (getch() == 'q') return false;
	}
}

/**
 * Right now this just draws arbitrary stuff everywhere, but at some point there
 * should actually be a scrolling map which is made up of characters that
 * have got colours and shiet. I will build a system for designing the levels
 * that lets you use tiles and stuff, but the tiles will be non mandatory, so
 * you can actually specify each character.
 */
void renderMap() {
	attrset(COLOR_PAIR(Render::floorColour));
	move(0, 0);
	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < LINES; y++) {
			addch('.');
		}
	}
}

int main(int argc, char **argv) {
	Render::Sprite sprite(froggoDown, froggoRight, froggoUp, froggoLeft);
	int px = 20, py = 20;
    initscr();
	start_color();
	cbreak();
	noecho();
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);
	Render::initColours();
    while (checkScreen()) {
		renderMap();
		sprite.render(px, py);
		refresh();
		switch (getch()) {
			case KEY_UP:
				sprite.orientation = Render::Orientation::UP;
				py -= 1;
				break;
			case KEY_DOWN:
				sprite.orientation = Render::Orientation::DOWN;
				py += 1;
				break;
			case KEY_LEFT:
				sprite.orientation = Render::Orientation::LEFT;
				px -= 1;
				break;
			case KEY_RIGHT:
				sprite.orientation = Render::Orientation::RIGHT;
				px += 1;
				break;
		}
    }
	clear();
	refresh();
    return 0;
}