#include "vdp.h"

// TODO: note that this assumes you are using conio, which
// means that any software that scrolls the screen
// needs to pull in at least conio_bgcolor.c, which
// I don't intend. We can fix that. This is only
// used for the background color memset.
extern unsigned int conio_scrnCol; // conio_bgcolor.c

// Mode				Has Attributes		Handled here
// 24x32 graphics	No					Yes
// 24x40 text		No					Yes
// 24x32 bitmap		Yes					No
// 48x64 multicolor	No					No (but might do something)
// 24x60 text		No					No
// 24x40 text color	Yes (F18A)			No
// 24x80 text		No  (F18A)			Yes
// 24x80 text color Yes (F18A)			No
// 30x80 text color Yes (F18A)			No

// this buffer is on the stack, so might as well be bigger
// and I'm only using text modes... but, should be no bigger
// than one line, or it gets weird.
#define SCRLBUF 40

void scrn_scroll_default() {
  // hacky, slow, but functional scroll that takes minimal memory
  unsigned char x[SCRLBUF];             // multiple byte buffer to speed it up
  int nLine = nTextEnd - nTextRow + 1;  // size of one line
  for (int adr = (nTitleLine * nLine) + nLine + gImage; adr < nTextEnd; adr += SCRLBUF) {
    vdpmemread(adr, x, SCRLBUF);
    vdpmemcpy(adr - nLine, x, SCRLBUF);
  }
  vdpmemset(nTextRow, ' ', nLine);  // clear the last line

  if (nTextFlags & TEXT_FLAG_HAS_ATTRIBUTES) {
    // copy color attributes the same way
    for (int adr = (nTitleLine * nLine) + nLine + gColor; adr < nTextEnd + gColor; adr += SCRLBUF) {
      vdpmemread(adr, x, SCRLBUF);
      vdpmemcpy(adr - nLine, x, SCRLBUF);
    }
    vdpmemset(nTextRow + gColor, conio_scrnCol, nLine);  // clear the last line
  }
}

void (*scrn_scroll)() = scrn_scroll_default;
