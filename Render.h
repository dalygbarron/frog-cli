#pragma once

namespace Render {
    int const COLOURS = 16;
    extern int colours[COLOURS][COLOURS];
    extern int floorColour;
    extern int menuColour;

    /**
     * Used where things can be rotated and stuff, pretty obvious what it is.
     */
    enum class Orientation {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    /**
     * Initialises the colours global so that it contains a colour pair for
     * every combination of allowed colours.
     */
    void initColours();

    /**
     * Moves somewhere then prints some text up to the given character count,
     * and if the string given doesn't hit the character count then it continues
     * printing spaces until it hits it.
     * @param row is the row to be on.
     * @param col is the column to be on.
     * @param n is the number of characters to write.
     * @param text is the text to write.
     */
    void mvPrintN(int row, int col, int n, char const *text);

    /**
     * Draws a pattern that is based on an image and where every second
     * character contains the colour codes that you are gonna be using.
     * @param x is the left column.
     * @param y is the top line.
     * @param image is the image to draw with the colour codes interleaved.
     */
    void drawImage(int x, int y, char const *image);

    /**
     * Used to store and render nice ascii graphics.
     */
    class Sprite {
        private:
            char const *down;
            char const *right;
            char const *up;
            char const *left;

        public:
            Orientation orientation = Orientation::DOWN;

            /**
             * Sets the sprite's image or images, if it has multiple then it is
             * considered rotatable, if it only has one it is only ever
             * displayed in that orientation.
             * @param down is the sprite when it is facing down, which is
             *        mandatory.
             * @param right is the sprite facing right.
             * @param up is the sprite facing up.
             * @param left is the sprite facing left.
             */
            Sprite(
                char const *down,
                char const *right,
                char const *up,
                char const *left
            );

            /**
             * Renders the sprite starting from it's top left corner.
             * @param x is the column to start on.
             * @param y is the line to start on.
             */
            void render(int x, int y);
    };
};