/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h>        //nds-rako garatuta dagoen liburutegia
#include <stdio.h>        //c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>        //c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>        //Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

//Geuk garatutako fitxategiak

#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"

int kont = 0;

void jokoa01() {
    touchPosition PANT_DAT;

    EGOERA = 0;


    //iprintf("\x1b[22;5HHau idazte proba bat da");	//Honek, 22 lerroan eta 5 zutabean hasiko da idazten.
    //Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta
    //komatxoen kanpoan aldagaiaren balioa.
    //iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);

    //******************************2.JARDUERAN************************************************//
    // Etenak baimendu behar dira.
    IME = 1;
    // Teklatua konfiguratu behar da.
    konfiguratuTeklatua(0x40ff);
    // Tenporizadorea konfiguratu behar da.
    konfiguratuTenporizadorea(0, 0x00C0);
    //konfiguratuTenporizadorea(0x9999, 0x0042);
    // Teklatuaren etenak baimendu behar dira.
    TekEtenBaimendu();
    // Tenporizadorearen etenak baimendu behar dira.
    DenbEtenBaimendu();
    // Etenen zerbitzu errutinak ezarri behar dira.
    etenZerbErrutEzarri();
    //***************************************************************************************//



    while (1) {
        /*************************************1.JARDUERAN**************************************/
        //Hemen teklatuaren inkesta egin, sakatu den tekla pantailaratu, eta START
        //sakatzean egoera aldatu

        // Menua
        if (EGOERA == 0) {
            int menuaKargatua = false;

            if (!menuaKargatua) {
                touchRead(&PANT_DAT);
                erakutsiMenua();
                menuaKargatua = true;
            }

            if (PANT_DAT.px != 0 || PANT_DAT.py != 0) {
                //iprintf("\x1b[22;5HHau idazte proba bat da");
                //ErakutsiErronboa(1, 30, 30);
                iprintf("\x1b[1;5HPantaila X:%d", PANT_DAT.px);
                iprintf("\x1b[2;5HPantaila Y:%d", PANT_DAT.py);

                if ((PANT_DAT.px >= 108 && PANT_DAT.px <= 144) && (PANT_DAT.py >= 107 && PANT_DAT.py <= 123)) {
                    EGOERA = 1; //Jokoa
                }
            }
        }


        // Jokoa
        if (EGOERA == 1) {
            int jokoaKargatu = false;

            if (!jokoaKargatu) {
                ErlojuaMartxanJarri();
                erakutsiFondoa();
                sortuJokoaSpritak();
                jokoaKargatu = true;
            }

            if (TeklaDetektatu()) {
                if (SakatutakoTekla() == SELECT) {
                    ezkutatuJokoaSpritak();
                    EGOERA = 2; //Pausa egoera
                } else if (SakatutakoTekla() == A) //TODO hau kendu
                {
                    puntuazioaPlayer++;
                    iprintf("\x1b[3;5HJokalariaren puntuazioa:%d", puntuazioaPlayer);
                } else if (SakatutakoTekla() == B) //TODO hau kendu
                {
                    puntuazioaCpu++;
                    iprintf("\x1b[4;5HCPU-aren puntuazioa:%d", puntuazioaCpu);
                }
            }

            // Jokalaria irabazlea da
            if (puntuazioaPlayer == 3) {
                ErlojuaGelditu();
                ezabatuJokoaSpritak();
                EGOERA = 3; // Irabazlea egoera
            } else if (puntuazioaCpu == 3) // CPU-a irabazlea da
            {
                ErlojuaGelditu();
                ezabatuJokoaSpritak();
                EGOERA = 3; // Irabazlea egoera
            }

        }

        // Pausa
        if (EGOERA == 2) {
            int pausaKargatu = false;

            if (!pausaKargatu) {
                erakutsiPausa();
                touchRead(&PANT_DAT);
                pausaKargatu = true;
            }

            if (PANT_DAT.px >= 87 && PANT_DAT.px <= 167) {
                if (PANT_DAT.py >= 80 && PANT_DAT.py <= 95)// Continue
                {
                    erakutsiJokoaSpritak();
                    EGOERA = 1;
                } else if (PANT_DAT.py >= 100 && PANT_DAT.py <= 112) // Restart
                {
                    sortuJokoaSpritak();
                    EGOERA = 1;
                } else if (PANT_DAT.py >= 116 && PANT_DAT.py <= 130) // Exit
                {
                    ezabatuJokoaSpritak();
                    EGOERA = 0;
                }
            }

        }

        // Irabazle/Galtzaile
        if (EGOERA == 3) {
            if (puntuazioaPlayer == 3) {
                erakutsiIrabazlea(); // Irabazi
                ErlojuaMartxanJarri();
                //ErlojuaGelditu();
            } else {
                erakutsiGaltzailea(); // Galdu
                ErlojuaMartxanJarri();
                //ErlojuaGelditu();
            }
        }
    }

}


void sortuJokoaSpritak() {
    SortuPaloteUrdina(0, 5, 96);
    SortuPaloteGorria(1, 236, 96);
    SortuPelotaMorea(2, 128, 96);
}

void ezabatuJokoaSpritak() {
    EzabatuPaloteUrdina(0, 5, 96);
    EzabatuPaloteGorria(1, 236, 96);
    EzabatuPelotaMorea(2, 128, 96);
}

void ezkutatuJokoaSpritak(int x, int y) {
    EzabatuPaloteUrdina(0, x, y);
    EzabatuPaloteGorria(1, x, y);
    EzabatuPelotaMorea(2, x, y);
}

void erakutsiJokoaSpritak(int x, int y) {
    SortuPaloteUrdina(0, x, y);
    SortuPaloteGorria(1, x, y);
    SortuPelotaMorea(2, x, y);
}
