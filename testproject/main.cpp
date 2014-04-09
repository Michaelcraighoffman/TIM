#include "stub.h"
#include "tests.h"
#include "once.h"

void _main() {
     TRACK("Started _main");
     //TestGraphH();
     TestGrayH();
     //TestSystemH();
     TimedWait(50000);
}
