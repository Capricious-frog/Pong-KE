/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h>        //nds-rako garatuta dagoen liburutegia
#include <stdio.h>        //c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>        //c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>        //Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia
#include "spriteak.h"
#include "definizioak.h"

u16 *gfxerronbo;
u16 *gfxerronboHandia;
u16 *gfxpaloteUrdina;
u16 *gfxpaloteGorria;
u16 *gfxpelotaMorea;


/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu() {
    /* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
    gfxpaloteUrdina = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
    gfxpaloteGorria = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
    gfxpelotaMorea = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void PaletaNagusiaEzarri() {
    SPRITE_PALETTE[1] = RGB15(31, 0, 0); // 1 baliodun pixelak gorriak izango dira.
    SPRITE_PALETTE[2] = RGB15(0, 31, 0); // 2 baliodun pixelak berdeak izango dira.
    SPRITE_PALETTE[3] = RGB15(0, 0, 31); // 3 baliodun pixelak urdinak izango dira.
    SPRITE_PALETTE[4] = RGB15(33, 150, 243); // 4 baliodun pixelak urdin argiak izango dira.
    SPRITE_PALETTE[5] = RGB15(120, 40, 31); // 5 baliodun pixelak gorri intentsoak izango dira.
    SPRITE_PALETTE[6] = RGB15(99, 57, 116); // 6 baliodun pixelak moreak izango dira.
}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko ezkerreko koadrantean. 
   Alboko irudian ikusten den bezala. */


u8 paloteUrdina[256] =
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4,
                0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };

u8 paloteGorria[256] =
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5,
                0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };

u8 pelotaMorea[256] =
        {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6,
                0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 6, 6, 6,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,
                6, 6, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 6, 6,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                6, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };

/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde() {

    int i;
    //16*16ko spriteentzako
    for (i = 0; i < 16 * 16 / 2; i++) {
        gfxpaloteUrdina[i] = paloteUrdina[i * 2] | (paloteUrdina[(i * 2) + 1] << 8);
        gfxpaloteGorria[i] = paloteGorria[i * 2] | (paloteGorria[(i * 2) + 1] << 8);
        gfxpelotaMorea[i] = pelotaMorea[i * 2] | (pelotaMorea[(i * 2) + 1] << 8);
    }
}

/* Funtzio honek erronbo bat irudikatuko dut pantailako x-y posizioan. Pantailan ateratzea nahi den erronbo
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke. */


/*---------------Gure jokoa-ren spritak---------------*/

//Erakutsi Spritak
void SortuPaloteUrdina(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpaloteUrdina,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           false,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

void SortuPaloteGorria(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpaloteGorria,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           false,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

void SortuPelotaMorea(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpelotaMorea,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           false,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

//Ezabatu Spriteak
void EzabatuPaloteUrdina(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpaloteUrdina,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           true,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

void EzabatuPaloteGorria(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpaloteGorria,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           true,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

void EzabatuPelotaMorea(int indizea, int x, int y) {

    oamSet(&oamMain, //main graphics engine context
           indizea,           //oam index (0 to 127)
           x, y,   //x and y pixle location of the sprite
           0,                    //priority, lower renders last (on top)
           0,                      //this is the palette index if multiple palettes or the alpha value if bmp sprite
           SpriteSize_16x16,
           SpriteColorFormat_256Color,
           gfxpelotaMorea,//+16*16/2,                  //pointer to the loaded graphics
           -1,                  //sprite rotation data
           false,               //double the size when rotating?
           true,            //hide the sprite?
           false, false, //vflip, hflip
           false    //apply mosaic
    );
    oamUpdate(&oamMain);

}

