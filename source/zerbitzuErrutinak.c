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

int paloteUrdinaX = 5;
int paloteUrdinaY = 90;
int paloteGorriaX = 236;
int paloteGorriaY = 90;
int pelotaX = 120;
int pelotaY = 90;
// 0 = Jokalariari urbiltzen
// 1 = Jokalariari urruntzen
int norabideaX = 0;
// 0 = Gora
// 1 = Behera
int norabideaY = 0;

void tekEten() {

    if (SakatutakoTekla() == SELECT && EGOERA == 1) {
        ezkutatuJokoaSpritak();
        EGOERA = 2; //Pausa egoera
    }
}

void tenpEten() {
    static int tik = 0;
    static int tikPalote = 0;
    static int tikPelota = 0;
    static int tikCpu = 0;
    static int seg = 0; // 512 tik segundu bat da.


    /* ----------------- Jokoa ----------------- */
    if (EGOERA == 1) {

        if (tik == 512) {
            iprintf("\x1b[1;5HPuntuazioa:             ");
            iprintf("\x1b[2;5HJokalaria:%d", puntuazioaPlayer);
            iprintf("\x1b[3;5HOrdenagailua:%d", puntuazioaCpu);
            iprintf("\x1b[5;5HPasa diren segunduak=%d", seg);
            tik = 0;
            seg++;
        }

        // Jokalariaren mugimendua
        if (tikPalote == 6) {
            if (TeklaDetektatu()) {
                if (SakatutakoTekla() == GORA && paloteUrdinaY > 5) {
                    paloteUrdinaY--;
                    SortuPaloteUrdina(0, 5, paloteUrdinaY);
                } else if (SakatutakoTekla() == BEHERA && paloteUrdinaY < 171) {
                    paloteUrdinaY++;
                    SortuPaloteUrdina(0, 5, paloteUrdinaY);
                }
            }
            tikPalote = 0;
        }

        //CPU-aren mugimendua
        if (tikCpu == 9) {
            if (paloteGorriaY > pelotaY) {
                paloteGorriaY--;
                SortuPaloteGorria(1, paloteGorriaX, paloteGorriaY);
            } else {
                paloteGorriaY++;
                SortuPaloteGorria(1, paloteGorriaX, paloteGorriaY);
            }
            tikCpu = 0;
        }

        // Paretak detektatu
        if (pelotaX == 0) {
            puntuazioaCpu++;
            pelotaX = 120;
            pelotaY = 90;
            norabideaX = 1;
        } else if (pelotaX == 245) {
            puntuazioaPlayer++;
            pelotaX = 120;
            pelotaY = 90;
            norabideaX = 0;
        }

        if (pelotaY == 0) {
            norabideaY = 1;
        } else if (pelotaY == 176) {
            norabideaY = 0;
        }


        // Pelotaren mugimendua
        if (tikPelota == 8) {

            // Pelotak zerbait ukitu duen begiratu
            if (kolisioaJokalaria()) {
                if (!norabideaX) {
                    norabideaX = 1;
                }
            } else if (kolisioaCpu()) {
                if (norabideaX && norabideaY) {
                    norabideaX = 0;
                } else if (norabideaX && !norabideaY) {
                    norabideaY = 1;
                }
            }

            // Pelota mugitu
            if (norabideaX && norabideaY) {
                pelotaX++;
                pelotaY++;
            } else if (!norabideaX && norabideaY) {
                pelotaX--;
                pelotaY++;
            } else if (norabideaX && !norabideaY) {
                pelotaX++;
                pelotaY--;
            } else if (!norabideaX && !norabideaY) {
                pelotaX--;
                pelotaY--;
            }
            SortuPelotaMorea(2, pelotaX, pelotaY);

            tikPelota = 0;
        }

        tik++;
        tikPalote++;
        tikPelota++;
        tikCpu++;
    } else if (EGOERA == 3) {
        if (tik >= 2048) {
            // 4 Segundu pasa direnean
            puntuazioaPlayer = 0;
            puntuazioaCpu = 0;
            EGOERA = 0;
        }
        tik++;

    } else {
        tik = 0;
        seg = 0;
    }
}

void etenZerbErrutEzarri() {
    irqSet(IRQ_KEYS, tekEten);
    irqSet(IRQ_TIMER0, tenpEten);
}

// Kolisioak palen inguruan
int kolisioaJokalaria() {
    return (pelotaX + 6 >= paloteUrdinaX + 7 && pelotaX + 6 <= paloteUrdinaX + 9) &&
           (pelotaY >= paloteUrdinaY && pelotaY <= paloteUrdinaY + 18);
}

int kolisioaCpu() {
    return (pelotaX + 10 >= paloteGorriaX + 7 && pelotaX + 10 <= paloteGorriaX + 9) &&
           (pelotaY >= paloteGorriaY && pelotaY <= paloteGorriaY + 18);
}
