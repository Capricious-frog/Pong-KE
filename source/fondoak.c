/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h>        //nds-rako garatuta dagoen liburutegia
#include <stdio.h>      //c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>     //c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>     //Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

/* Fondo desberdinak erakutsi nahi izango baditugu, hemen fondo bakoitzaren burukoa (.h fitxategia) gehitu behar da. Buruko horiek
automatikoki sortzen dira, konpilatzerako garaian, baina horretarako gogoratu behar da */

#include "fondoak.h"
#include "grafikoak.h"
#include "fondoa.h"
#include "Galtzailea.h"
#include "Irabazlea.h"
#include "Pausa.h"
#include "hasiera.h"

/* irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

//Gure jokoa
void erakutsiMenua() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     hasieraBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *) BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     hasieraBitmapLen); /* Luzera (bytetan) automatikoki sortzen den aldagaia */
}

void erakutsiIrabazlea() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     IrabazleaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *) BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     IrabazleaBitmapLen); /* Luzera (bytetan) automatikoki sortzen den aldagaia */
}

void erakutsiGaltzailea() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     GaltzaileaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *) BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     GaltzaileaBitmapLen); /* Luzera (bytetan) automatikoki sortzen den aldagaia */
}

void erakutsiPausa() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     PausaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *) BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     PausaBitmapLen); /* Luzera (bytetan) automatikoki sortzen den aldagaia */
}

void erakutsiFondoa() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     fondoaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *) BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     fondoaBitmapLen); /* Luzera (bytetan) automatikoki sortzen den aldagaia */
}
