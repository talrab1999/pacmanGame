
#include "color.h"

void setTextColor(Color colorToSet) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}