#include <math.h>

#include "pico_explorer.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

ST7789 st7789(PicoExplorer::WIDTH, PicoExplorer::HEIGHT, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));

// 8-bit colour
// PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

// 16-bit colour
PicoGraphics_PenRGB565 graphics(st7789.width, st7789.height, nullptr);

int getNewDelta (int currentDelta, int newValue, int maxValue) {
    if (newValue < 0 || newValue > maxValue) {
        return currentDelta * -1;
    }
    else {
        return currentDelta;
    }
};

int getNewValue (int newValue, int maxValue) {
    if (newValue < 0) {
        // "Bounce" back in to positive territory.
        return newValue * -1;
    }
    else if (newValue > maxValue) {
        // "Bounce back into range"
        return maxValue - (newValue % maxValue);
    }
    else {
        // Do nothing, the value is within the range.
        return newValue;
    }
};

int main() {
    st7789.set_backlight(75);
    graphics.set_pen(120, 40, 60);
    graphics.clear();

    int r = 127;
    int g = 127; 
    int b = 127;

    int maxradius = round(std::min(st7789.width, st7789.height) / 2);
    int radius = rand () % maxradius;
    int dradius = (rand() % 10) - 5;

    int dr = (rand() % 10) - 5;
    int dg = (rand() % 10) - 5;
    int db = (rand() % 10) - 5;


    int x = round(st7789.width / 2);
    int y = round(st7789.height / 2);

    Point center = Point(x, y);
    Pen bg = graphics.create_pen(0, 0, 0);

    while(true) {
        int newr = r + dr;
        int newg = g + dg;
        int newb = b + db;
        int newradius = radius + dradius;

        r = getNewValue(newr, 255);
        g = getNewValue(newg, 255);
        b = getNewValue(newb, 255);
        radius = getNewValue(newradius, maxradius);

        dr = getNewDelta(dr, newr, 255);
        dg = getNewDelta(dg, newg, 255);
        db = getNewDelta(db, newb, 255);
        dradius = getNewDelta(dradius, newradius, maxradius);

        graphics.set_pen(bg);
        graphics.clear();

        Pen pen = graphics.create_pen(r, g, b);
        graphics.set_pen(pen);
        graphics.circle(center, radius);

        st7789.update(&graphics);

        sleep_ms(1000 / 30);
    }
}