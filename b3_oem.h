#ifndef _OEM_H
#define _OEM_H 1

extern unsigned char PAT0;
extern unsigned char PAT95;
extern unsigned char PAT127;

void defineChars();

#include "banking.h"

DECLARE_BANKED_VOID(defineChars, BANK(3), bk_defineChars, (), ())

#endif