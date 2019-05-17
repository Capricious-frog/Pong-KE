/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"

int EGOERA;
int puntuazioaPlayer = 0;
int puntuazioaCpu = 0;
int y = 96;

void tekEten() {

    if (SakatutakoTekla() == START) {
        EGOERA = 2;
        ErlojuaMartxanJarri();
    }

    if (SakatutakoTekla() == SELECT) {
//        EGOERA = 0;
//        EzabatuErronboHandia(1, 0, 150);
    }
}

void tenpEten() {
    static int tik = 0;
    static int tik1 = 0;
    static int seg = 0; // 512 tik segundu bat da.


    iprintf("\x1b[8;5HPuntuazioa:%d", puntuazioaPlayer);

    //Jokoa
    if (EGOERA == 1) {
        iprintf("\x1b[5;5HPasa diren tik-ak=%d", tik);

        if (tik == 512) {
            tik = 0;
            iprintf("\x1b[6;5HPasa diren segunduak=%d", seg);
            seg++;
        }

        if (tik1 == 256) {
            if (TeklaDetektatu()) {
                if (SakatutakoTekla() == GORA) {
                    iprintf("\x1b[7;5HTekla GORA sakatua  ");
                    y = y - 10;
                    SortuPaloteUrdina(0, 5, y);
                } else if (SakatutakoTekla() == BEHERA) {
                    iprintf("\x1b[7;5HTekla BEHERA sakatua");
                    y = y + 10;
                    SortuPaloteUrdina(0, 5, y);
                }
            }
            tik1 = 0;
        }

        tik++;
        tik1++;
    } else if (EGOERA == 3) {
        if (tik >= 2048) { // 4 Segundu pasa direnean
            puntuazioaPlayer = 0;
            puntuazioaCpu = 0;
            EGOERA = 0;
        }
        tik++;


    } else {
        iprintf("\x1b[9;5HPasa diren tik-ak=%d", tik);
        tik = 0;
        seg = 0;
    }
}

void etenZerbErrutEzarri() {
    irqSet(IRQ_KEYS, tekEten);
    irqSet(IRQ_TIMER0, tenpEten);
}

