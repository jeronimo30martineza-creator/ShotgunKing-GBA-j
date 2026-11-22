
#include <stdint.h>

#define REG_DISPCNT (*(volatile uint16_t*)0x04000000)
#define VRAM ((volatile uint16_t*)0x06000000)
#define KEYINPUT (*(volatile uint16_t*)0x04000130)

#define MODE3 3
#define BG2 (1 << 10)

#define KEY_A  (1 << 0)
#define KEY_B  (1 << 1)
#define KEY_R  (1 << 8)
#define KEY_UP (1 << 6)
#define KEY_DOWN (1 << 7)
#define KEY_LEFT (1 << 5)
#define KEY_RIGHT (1 << 4)

#define RGB(r,g,b) ((r) | ((g) << 5) | ((b) << 10))

uint16_t black = RGB(2,2,3);
uint16_t white = RGB(29,29,29);
uint16_t red = RGB(31,3,3);
uint16_t gray = RGB(13,13,15);
uint16_t brown = RGB(15,9,4);

int kingX = 3;
int kingY = 7;
int cursorX = 3;
int cursorY = 7;
int shootMode = 0;

void pixel(int x, int y, uint16_t color) {
    if (x >= 0 && x < 240 && y >= 0 && y < 160)
        VRAM[y * 240 + x] = color;
}

void rect(int x, int y, int w, int h, uint16_t color) {
    for (int j = 0; j < h; j++)
        for (int i = 0; i < w; i++)
            pixel(x+i, y+j, color);
}

void board() {
    rect(0, 0, 240, 160, black);

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            uint16_t c = ((x+y)&1) ? gray : white;
            rect(56+x*16, 16+y*16, 16, 16, c);
        }
    }
}

void king() {
    int x = 56 + kingX*16;
    int y = 16 + kingY*16;

    rect(x+5,y+2,6,3,brown);
    rect(x+3,y+5,10,5,black);
    rect(x+2,y+10,12,4,red);
    rect(x+4,y+14,3,2,black);
    rect(x+9,y+14,3,2,black);

    rect(x+12,y+6,3,2,gray);
}

void cursor() {
    int x = 56 + cursorX*16;
    int y = 16 + cursorY*16;

    rect(x,y,16,1,red);
    rect(x,y+15,16,1,red);
    rect(x,y,1,16,red);
    rect(x+15,y,1,16,red);
}

int main(void) {
    REG_DISPCNT = MODE3 | BG2;

    uint16_t oldKeys = 0x03FF;

    while (1) {
        uint16_t keys = ~KEYINPUT & 0x03FF;
        uint16_t pressed = keys & ~oldKeys;
        oldKeys = keys;

        if (pressed & KEY_R)
            shootMode = !shootMode;

        if (!shootMode) {
            if (pressed & KEY_LEFT && kingX > 0) kingX--;
            if (pressed & KEY_RIGHT && kingX < 7) kingX++;
            if (pressed & KEY_UP && kingY > 0) kingY--;
            if (pressed & KEY_DOWN && kingY < 7) kingY++;
            cursorX = kingX;
            cursorY = kingY;
        } else {
            if (pressed & KEY_LEFT && cursorX > 0) cursorX--;
            if (pressed & KEY_RIGHT && cursorX < 7) cursorX++;
            if (pressed & KEY_UP && cursorY > 0) cursorY--;
            if (pressed & KEY_DOWN && cursorY < 7) cursorY++;
        }

        board();
        king();
        cursor();

        if (shootMode)
            rect(4,4,32,5,red);
    }

    return 0;
}
