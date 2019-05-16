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
int y = 96;

void tekEten() {
    // El codigo que venia
    /*if (EGOERA == ITXITA)
    {
        if (SakatutakoTekla() == A)
        {
            EGOERA = IREKITA;
            iprintf("\x1b[13;5HPasa diren segunduak=0");
            erakutsiAteaIrekita();
            seg3=0;
            ErakutsiErronboa(1, 5, 5);
            ErakutsiErronboHandia(2, 100, 100);
        }
    }*/

    if (SakatutakoTekla() == START) {
        EGOERA = 2;
        ErlojuaMartxanJarri();
    }

    if (SakatutakoTekla() == SELECT) {
        EGOERA = 0;
        EzabatuErronboHandia(1, 0, 150);
    }
}

void tenpEten() {
    static int tik = 0;
    static int tik1 = 0;
    static int seg = 0; // 512 tik segundu bat da.

    if (EGOERA == 1) {
        iprintf("\x1b[13;5HPasa diren tik-ak=%d", tik);

        if (tik == 512) {
            tik = 0;
            iprintf("\x1b[14;5HPasa diren segunduak=%d", seg);
            seg++;
        }

        if (tik1 == 256) {
            if (TeklaDetektatu()) {
                if (SakatutakoTekla() == GORA) {
                    iprintf("\x1b[16;5HTekla GORA sakatua");
                    y = y - 10;
                    SortuPaloteUrdina(0, 5, y);
                } else if (SakatutakoTekla() == BEHERA) {
                    iprintf("\x1b[16;5HTekla BEHERA sakatua");
                    y = y + 10;
                    SortuPaloteUrdina(0, 5, y);
                }
            }
            tik1 = 0;
        }

        tik++;
        tik1++;
    } else if (EGOERA == 3) {
        if (tik >= 2048) // 4 Segundu pasa direnean
        {
            EGOERA = 0;
        }
        iprintf("\x1b[4;1Hhdjsahdskaj:%d", tik);
        tik++;


    } else {
        iprintf("\x1b[13;5HPasa diren tik-ak=%d", tik);
        tik = 0;
        seg = 0;
    }
}

void etenZerbErrutEzarri() {
    irqSet(IRQ_KEYS, tekEten);
    irqSet(IRQ_TIMER0, tenpEten);
}

