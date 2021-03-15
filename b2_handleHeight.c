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

void handleHeight() {
    char* tok = bk_strtok(0, ' ');
    int height = bk_atoi(tok);

    if (height == 30 && (vdp_type == VDP_F18A)) {
        bk_setupScreen(displayWidth, 30);
        return;
    }

    if (height == 24) {
        bk_setupScreen(displayWidth, 24);
        return;
    }

    if (height == 26 && (vdp_type == VDP_9938 || vdp_type == VDP_9958)) {
        bk_setupScreen(displayWidth, 26);
        return;
    }

    tputs_rom("no supported width specified\n");
}
