#include "tests.h"
#include "graph.h"
#include "sprites.h"
#include "__timsystem.h"

void TestGraphH() {
    FontSetSys(F_4x6);
    DrawStr(0,10, "THE QUICK BROWN FOX JUMPS", 0);
    DrawStr(0,20, "OVER THE LAZY DOG.", 0);
    DrawStr(0,30, "the quick brown fox jumps", 0);
    DrawStr(0,40, "over the lazy dog.", 0);
    FontSetSys(F_6x8);
    DrawStr(0,50, "THE QUICK BROWN FOX JUMPS", 0);
    DrawStr(0,60, "OVER THE LAZY DOG.", 0);
    DrawStr(0,70, "the quick brown fox jumps", 0);
    DrawStr(0,80, "over the lazy dog.", 0);
}
