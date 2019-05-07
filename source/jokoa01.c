/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

//Geuk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"

int denb;

void jokoa01()
{	
	//aldagai baten definizioa
	int i = 9;
	// int tekla = 0; //Venia por defecto
	//EGOERA;	
	int Pos = 2;
	int y = 250;
	int x = 125;
	int z = 25;
	int t;
	int a = 100;
	int b = 200;
	int kont = 0;
	int eraso = 0;
	int kon0 = 0;
	int kon1 = 0;
	int kon2 = 0;
	int tempmov = 0; // TODO: Que hace esta variable?
	// tik1;
	touchPosition PANT_DAT;

	// EGOERA = ZAI; // Lo que venia por defecto
	
	
	//iprintf("\x1b[22;5HHau idazte proba bat da");	//Honek, 22 lerroan eta 5 zutabean hasiko da idazten.
													//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
													 //komatxoen kanpoan aldagaiaren balioa.
	//iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);

	//******************************2.JARDUERAN************************************************//
	// Etenak baimendu behar dira. 
	IME = 1;
	// Teklatua konfiguratu behar da.
	konfiguratuTeklatua(0x40ff); // TODO: Zer egiten du 0x40ff
	// Tenporizadorea konfiguratu behar da.
	konfiguratuTenporizadorea(0x9999, 0x0042);
	// Teklatuaren etenak baimendu behar dira.
	TekEtenBaimendu();
	// Tenporizadorearen etenak baimendu behar dira.
	DenbEtenBaimendu();
	// Etenen zerbitzu errutinak ezarri behar dira.
	etenZerbErrutEzarri();
	//***************************************************************************************//

	

	//erakutsiAtea();

	while(1)
	{
		/*************************************1.JARDUERAN**************************************/
		//Hemen teklatuaren inkesta egin, sakatu den tekla pantailaratu, eta START
		//sakatzean egoera aldatu

    
	    // Menua
		if (EGOERA == 0)
        {
            int menuaKargatua = false;

            // TODO Llamarlo desde la funcion que carga el menu
            if (!menuaKargatua)
            {
                touchRead(&PANT_DAT);
                erakutsiMenua();
                menuaKargatua = true;
            }

			if (PANT_DAT.px != 0 || PANT_DAT.py != 0)
            {
                //iprintf("\x1b[22;5HHau idazte proba bat da");
				ErakutsiErronboa(1, 30, 30);
				
				EGOERA = 1; //Jokoa
            }
        }


        // Jokoa
        if (EGOERA == 1)
        {
            int jokoaKargatu = false;
            int puntuazioaPlayer = 0;
            int puntuazioaCpu = 0;

            if (!jokoaKargatu)
            {
                ErakutsiPaloteUrdina(0, 20, 96);
                ErakutsiPaloteGorria(0, 236, 96);
                ErakutsiPelotaMorea(0, 128, 96);
                erakutsiFondoa();
                jokoaKargatu = true;
            }

            if (TeklaDetektatu())
            {
                if (SakatutakoTekla() == SELECT)
                {
                    EGOERA = 2; //Pausa egoera
                }
            }

            // Jokalaria irabazlea da
            if (puntuazioaPlayer == 3)
            {
                ezabatuJokoaSpritak();
                EGOERA = 3; // Irabazlea egoera
            }

            // CPU-a irabazlea da
            if (puntuazioaCpu == 3)
            {
                ezabatuJokoaSpritak();
                EGOERA = 3; // Irabazlea egoera
            }
        }

        // Pausa
        if (EGOERA == 2)
        {
            int pausaKargatu = false;

            if (!pausaKargatu)
            {
                erakutsiPausa();
            }
        }
    }

}

void ezabatuJokoaSpritak()
{
    ezabatuPaloteUrdina(0, 20, 96);
    ezabatuPaloteGorria(0, 236, 96);
    ezabatuPelotaMorea(0, 128, 96);
}
