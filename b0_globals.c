#include "banks.h"
#define MYBANK BANK(0)

#include "b0_globals.h"

struct DeviceServiceRoutine* currentDsr;
char currentPath[256];
char filterglob[12];
int backspace;
unsigned int displayWidth = 40;
unsigned int displayHeight = 24;
int scripton = 0;
int* goto_line_ref;
struct DeviceServiceRoutine* scriptDsr = 0;
struct PAB* scriptPab;
int pal = 0;
int api_exec = 0;
int request_break;


