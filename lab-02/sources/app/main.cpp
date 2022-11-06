#include "utils/screen.h"

int main(int arc, char** arv) {
    Screen* screen = Screen::show(arv, arc);
    Screen::terminate();
    return 0;
}