#include "banks.h"
#define MYBANK BANK(2)

#include "commands.h"

#include "b0_main.h"
#include "b1_strutil.h"
#include "b8_terminal.h"
#include "b8_setupScreen.h"
#include "b0_globals.h"
#include "b10_detect_vdp.h"
#include <string.h>

int can80Column() {
  return vdp_type != VDP_9918;
}

void handleWidth() {
  char* tok = bk_strtok(0, ' ');
  int width = bk_atoi(tok);

  if (width == 80 && can80Column()) {
    bk_setupScreen(80, displayHeight);
    return;
  }

  if (width == 40) {
    bk_setupScreen(40, displayHeight);
    return;
  }

  tputs_rom("no supported width specified\n");
}

