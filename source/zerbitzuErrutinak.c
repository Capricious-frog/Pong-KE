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
int norabidea = 0;

void tekEten() {

//    if (SakatutakoTekla() == START) {
//        EGOERA = 2;
//        ErlojuaMartxanJarri();
//    }

//    if (SakatutakoTekla() == SELECT) {
//        EGOERA = 0;
//        EzabatuErronboHandia(1, 0, 150);
//    }
}

void tenpEten() {
    static int tik = 0;
    static int tikPalote = 0;
    static int tikPelota = 0;
    static int seg = 0; // 512 tik segundu bat da.


    iprintf("\x1b[8;5HPuntuazioa:%d", puntuazioaPlayer);

    //Jokoa
    if (EGOERA == 1) {
        iprintf("\x1b[5;5HPalote urdina Y=%d", paloteUrdinaY);

        if (tik == 512) {
            tik = 0;
            iprintf("\x1b[6;5HPasa diren segunduak=%d", seg);
            seg++;
        }

        if (tikPalote == 6) {
            if (TeklaDetektatu()) {
                if (SakatutakoTekla() == GORA && paloteUrdinaY > 5) {
                    iprintf("\x1b[7;5HTekla GORA sakatua  ");
                    paloteUrdinaY--;
                    SortuPaloteUrdina(0, 5, paloteUrdinaY);
                } else if (SakatutakoTekla() == BEHERA && paloteUrdinaY < 171) {
                    iprintf("\x1b[7;5HTekla BEHERA sakatua");
                    paloteUrdinaY++;
                    SortuPaloteUrdina(0, 5, paloteUrdinaY);
                }
            }
            tikPalote = 0;
        }

        if (tikPelota == 10) {
            // Kolisioak egon diren begiratu
            if (collitionPlayer()) {
                norabidea = 1;
            } else if (collitionEnemy()) {
                norabidea = 0;
            }

            if (norabidea) {
                pelotaX++;
                SortuPelotaMorea(2, pelotaX, pelotaY);
            } else {
                pelotaX--;
                SortuPelotaMorea(2, pelotaX, pelotaY);
            }

            tikPelota = 0;
        }

        tik++;
        tikPalote++;
        tikPelota++;
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

int collitionPlayer() {

    iprintf("\x1b[1;5HPantaila X:%d", PANT_DAT.px);
    iprintf("\x1b[2;5HPantaila Y:%d", PANT_DAT.py);
    iprintf("\x1b[3;5HpaloteUrdinaX:%d", paloteUrdinaX);
    iprintf("\x1b[4;5HpaloteUrdinaY Y:%d", paloteUrdinaY);

    touchRead(&PANT_DAT);
    if ((PANT_DAT.px >= paloteUrdinaX + 7 && PANT_DAT.px <= paloteUrdinaX + 9) &&
        (PANT_DAT.py >= paloteUrdinaY && PANT_DAT.py <= paloteUrdinaY + 18)) {
        iprintf("\x1b[20;5HColision!      ");
    } else {
        iprintf("\x1b[20;5HNo hay Colision");
    }


//    if (pelotaX == paloteUrdinaX) {
//        return true;
//    } else if (pelotaY == paloteUrdinaY) {
//        return true;
//    }
//
//    return false;
}

int collitionEnemy() {










//    if (pelotaX == paloteGorriaX) {
//        return true;
//    } else if (pelotaY == paloteGorriaY) {
//        return true;
//    }
//
//    return false;
    return false;
}

