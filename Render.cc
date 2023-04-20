#include "Render.h"
#include <ncurses.h>

int Render::colours[Render::COLOURS][Render::COLOURS];
int Render::floorColour;
int Render::menuColour;

void Render::initColours() {
	for (int a = 0; a < COLOURS; a++) {
		for (int b = 0; b < COLOURS; b++) {
			int index = a * COLOURS + b;
			init_pair(index, a, b);
			colours[a][b] = index;
		}
	}
	floorColour = colours[COLOR_GREEN][COLOR_BLACK];
	menuColour = colours[COLOR_WHITE][COLOR_CYAN];
}

void Render::mvPrintN(int row, int col, int n, char const *text) {
	move(row, col);
	bool reading = true;
	for (int i = 0; i < n; i++) {
		if (reading) {
			char c = text[i];
			if (c) {
				addch(c);
			} else {
				addch(' ');
				reading = false;
			}
		} else {
			addch(' ');
		}
	}
}

void Render::drawImage(int x, int y, char const *image) {
    int offset = 0;
	move(y, x);
    for (int i = 0; image[i]; i++) {
        char c = image[i];
        if (c == '\n') {
            offset++;
            move(y + offset, x);
        } else {
            i++;
            char colourCode = image[i];
            attrset(COLOR_PAIR(colours[colourCode >> 4][colourCode & 0xf]));
            addch(c);
        }
    }
}

Render::Sprite::Sprite(
    char const *down,
    char const *right,
    char const *up,
    char const *left
): down(down), right(right), up(up), left(left) {}

void Render::Sprite::render(int x, int y) {
    if (orientation == Orientation::DOWN || !right || !up || !left) {
        drawImage(x, y, down);
		return;
    }
    switch (orientation) {
		case Orientation::RIGHT:
			drawImage(x, y, right);
			break;
		case Orientation::UP:
			drawImage(x, y, up);
			break;
		default:
			drawImage(x, y, left);
			break;
	}
}