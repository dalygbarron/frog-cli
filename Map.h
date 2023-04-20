#pragma once

#include "Dude.h"
#include <vector>

/**
 * This represents an area in the game.
 */
class Map {
    public:
        static int const WIDTH = 100;
        static int const HEIGHT = 50;

        /**
         * Creates the map based on the tile data given. If the tile data is
         * of the wrong size it will throw an exception and crash everything
         * because you should never do that.
         * @param tiles is the tile data which consists of either one or two
         *        characters per tile. If the first byte starts with a 1, then
         *        it is a single byte special tile which can be animated and
         *        stuff, if it starts with a 0 then it is a normal ascii char
         *        and then the next byte defines the foreground and background
         *        colours.
         */
        Map(char const *tiles);

        /**
         * Regenerates the pathing map after stuff has moved.
         */
        void regenPath();

    private:
        char const *tiles;
        bool path[WIDTH * HEIGHT];
        std::vector<Dude *> dudes;
};