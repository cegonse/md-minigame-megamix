#include "common.h"

static const u16 BlackPalette[64] = { [0 ... 63] = 0x0000 };

void setAllPalettesToBlack()
{
    // VDP_waitVSync();
    // SYS_disableInts();
    
    for(u16 i = PAL0; i <= PAL3; ++ i)
    {
        PAL_setPalette(i, BlackPalette, DMA);
    }
    
    // SYS_enableInts();
}