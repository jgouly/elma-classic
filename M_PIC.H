#ifndef M_PIC_H
#define M_PIC_H

#include "eol_settings.h"

class pic8;

// extern int SCREEN_WIDTH;
#define SCREEN_WIDTH EolSettings->screen_width()
#define SCREEN_HEIGHT EolSettings->screen_height()
// extern int SCREEN_HEIGHT;

pic8* lockbackbuffer_pic(bool flipped = true);
void unlockbackbuffer_pic(void);

void lockfrontbuffer_pic(bool flipped = false);
void unlockfrontbuffer_pic(void);
void ppixelfront(int x, int y, unsigned char szin);

void bltfront(pic8* ppic);
void bltfront(pic8* ppic, int x1, int y1, int x2, int y2);

#endif
