#include "banks.h"
#define MYBANK BANK(0)

#include "b0_globals.h"

struct DeviceServiceRoutine* currentDsr;
char currentPath[256];
char filterglob[12];
int backspace;
unsigned int displayWidth = 40;
int scripton = 0;
int lineno = 0;
struct DeviceServiceRoutine* scriptDsr = 0;
struct PAB* scriptPab;
int pal = 0;
int vdp_type;


