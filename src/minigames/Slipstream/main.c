#include <genesis.h>
#include "Slipstream.h"
#include "inc/display.h"



Sprite *coche1;
Sprite *coche2;

static s16 valuesA [ 224 ];
static s16 valuesB [ 224 ];
static u16 vram_pos = 16;



static void *vint_callback ( )
{
	VDP_setHorizontalScrollLine ( BG_A, 0, valuesA, 224, 0 );
	VDP_setHorizontalScrollLine ( BG_B, 0, valuesB, 224, 0 );

	return 0;
}



void drawImageXY ( Image *image, int plan, u16 x, u16 y )
{
    u16 pal = ( plan == BG_A ) ? PAL1 : PAL0;

    SYS_disableInts();
    VDP_drawImageEx ( plan, image, TILE_ATTR_FULL ( pal, 0, 0, 0, vram_pos ), x, y, 0, 0 );
    SYS_enableInts();

    preparePal ( pal, image->palette->data );

    vram_pos += image->tileset->numTile;
}



void drawCocheXY ( s16 x, s16 y )
{
	SPR_setPosition ( coche1, x,    y );
	SPR_setPosition ( coche2, x+88, y );
}



void Slipstream_Main ( )
{
	vram_pos = 16;

	VDP_setScrollingMode ( HSCROLL_LINE, VSCROLL_PLANE );

waitMs(1000);
	SPR_init ( );

	s16 coche_x =  75;
	s16 coche_y = 140;

	coche1 = SPR_addSprite ( &coche, coche_x,    coche_y, TILE_ATTR(PAL2, 0, 0,0) );
	coche2 = SPR_addSprite ( &coche, coche_x+88, coche_y, TILE_ATTR(PAL2, 0, 0,0) );

	SPR_setAnim ( coche1, 0 );
	SPR_setAnim ( coche2, 1 );

	drawCocheXY ( coche_x, coche_y );


	preparePal( PAL2, coche.palette->data);


	s16 i;

	fix32 vel_x_a = FIX32(10);
	fix32 vel_x_b = FIX32(.5);

	fix32 fValuesA [ 224 ];
	fix32 fValuesB [ 224 ];

	for ( i=0; i<224; i++)
	{
		valuesA[i] = 0;
		valuesB[i] = 0;

		fValuesA[i] = FIX32(0);
		fValuesB[i] = FIX32(0);
	}

	displayOff(0);

	drawImageXY ( (Image*) &foreground1, BG_A, 0, -17 );
	drawImageXY ( (Image*) &background1, BG_B, 0, -17 );

	SYS_setVIntCallback ( (VoidCallback*) vint_callback );

	displayOn(0);


	s32 inc_x = 0;
	s32 inc_y = 0;
	const int values_x[20] = { 4, 5, 3, 2, 1, 0, -1, -2, -3, -5, -4, -5, -3, -2, -1, 0, 1, 2, 3, 5 };
	const int values_y[16] = { 3, 2, 1, 0, -1, -2, -3, -4, -3, -2, -1, 0, 1, 2, 3, 4 };

	s16 repeat = 3;
	s16 sumar = 0;

	while(1) {
		u16 topB = 60;
		s16 j = 0;

		for ( i=0; i<224; i++) {
			fValuesA[i] = fix32Add ( fValuesA[i], vel_x_a );
			fValuesB[i] = fix32Add ( fValuesB[i], vel_x_b );

			if ( i > topB ) {
				fix32 inc_x = fix32Div ( FIX32(j), FIX32(27)) ;
				fValuesB[i] = fix32Add ( fValuesB[i], inc_x );
				j++;
			}

			valuesA[i] = fix32ToRoundedInt ( fValuesA[i] );
			valuesB[i] = fix32ToRoundedInt ( fValuesB[i] );
		}


		if ( repeat )
			--repeat;
		else {
			inc_x = values_x [ sumar % 20 ];
			inc_y = values_y [ sumar % 16 ];
			sumar++;

			repeat = 2;
		}

		drawCocheXY ( coche_x+inc_x, coche_y+inc_y );

		// if ( JOY_readJoypad(JOY_1) & BUTTON_A & BUTTON_B & BUTTON_C & BUTTON_START )
		if ( JOY_readJoypad(JOY_1) & BUTTON_START )
			break;

		SPR_update();
		SYS_doVBlankProcess();
	}
}
