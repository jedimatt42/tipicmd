#include "banks.h"
#define MYBANK BANK_2

#include "b0_globals.h"
#include "commands.h"
#include "b1cp_strutil.h"
#include "b2_dsrutil.h"
#include <string.h>
#include <conio.h>


void handleDelete() {
  char* filename = strtok(0, " ");
  if (filename == 0) {
    cputs("error, must specify a file name\n");
    return;
  }

  char buffer[256];
  strcpy(buffer, currentPath);
  strcat(buffer, filename);
  
  unsigned int exists = existsFile(currentDsr, buffer);
  if (!exists) {
    cputs("file not found ");
    cputs(buffer);
    cputc('\n');
    return;
  }

  struct PAB pab;
  initPab(&pab);
  pab.pName = buffer;

  unsigned char err = dsr_delete(currentDsr, &pab);
  if (err) {
    cputs("cannot delete file ");
    cputs(currentPath);
    cputs(filename);
    cputc('\n');
  }
}