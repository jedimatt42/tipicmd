#include "banks.h"

#define MYBANK BANK_0

#include "commands.h"
#include "b1cp_strutil.h"
#include <conio.h>

void handleEcho() {
  char* peek = strtokpeek(0, " ");
  int newline = 0 != strcmpi("/N", peek);
 
  if (!newline) {
    strtok(0, " "); // consume the optional /n
  }

  char* tok = strtok(0, 0);
  cputs(tok);

  if (newline) {
    cputc('\n');
  }
}