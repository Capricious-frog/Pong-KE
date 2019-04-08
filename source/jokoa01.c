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
	
		if (EGOERA == 0)
		{
			EzabatuErronboHandia(1, 160, 0);
			EzabatuErronboHandia(2, 180, 0);
			EzabatuErronboHandia(3, 110, 0);
			EzabatuErronboa(5, t, z);
			EzabatuErronboa(4, y, x);
			erakutsiMenu();

			touchRead(&PANT_DAT);
			if ((PANT_DAT.px) != 0 || (PANT_DAT.py != 0))
			{
				EGOERA = 2;
				ErlojuaMartxanJarri();
				erakutsiPato();
			}
		}


		if (EGOERA == 2)
		{
			//Sprite nagusiaren mugimendua posizioka kudeatu dugu errezago izan dadin.
			if (SakatutakoTekla() == GORA && Pos != 0 && tempmov == 0)
			{
				Pos = Pos - 1;
				tempmov = 500;
			}
			if (SakatutakoTekla() == BEHERA && Pos != 4 && tempmov == 0)
			{
				Pos = Pos + 1;
				tempmov = 500;
			}
			if (tempmov > 0) {
				tempmov = tempmov - 1;
			}

			iprintf("\x1b[16;5H");

			if (Pos == 0) {
				ErakutsiErronboHandia(1, 34, 0);
			}
			if (Pos == 1) {
				ErakutsiErronboHandia(1, 68, 0);
			}
			if (Pos == 2) {
				ErakutsiErronboHandia(1, 100, 0);
			}
			if (Pos == 3) {
				ErakutsiErronboHandia(1, 134, 0);
			}
			if (Pos == 4) {
				ErakutsiErronboHandia(1, 168, 0);
			}

			if (eraso == 0) {
				ErakutsiErronboa(3, 34, x);
				x = 50 - (tik1 * 25);//*

				//Sprit-a hasierara itzultzeko
				if (x == 0) {
					x = 250;
				}

				ErakutsiErronboa(4, 68, b);
				b = 225 - (tik1 * 25);

				//Sprit-a hasierara itzultzeko
				if (b == 0) {
					b = 250;
				}

				ErakutsiErronboa(5, 100, y);
				y = 200 - (tik1 * 25);

				//Spritea hasierara itzultzeko
				if (y == 0) {
					y = 250;
				}

				ErakutsiErronboa(6, 134, z);
				z = 100 - (tik1 * 25);

				//Spritea hasierara itzultzeko
				if (z == 0) {
					z = 250;
				}

				ErakutsiErronboa(7, 168, a);
				a = 125 - (tik1 * 25);

				//Spritea hasierara itzultzeko
				if (a == 0) {
					a = 250;
				}


				 // hauek dira jokoa amaituko diren kasuak. If hauek bi spriten talka simulatzen dute.


				if ((x == 25) && (Pos == 0))
				{
					EGOERA = 1;
					EzabatuErronboHandia(1, 34, 0);
					EzabatuErronboa(3, 34, x);
					EzabatuErronboa(4, 68, b);
					EzabatuErronboa(5, 100, y);
					EzabatuErronboa(6, 134, z);
					EzabatuErronboa(7, 168, a);
				}
				if ((b == 25) && (Pos == 1))
				{
					EGOERA = 1;
					EzabatuErronboHandia(1, 34, 0);
					EzabatuErronboa(3, 34, x);
					EzabatuErronboa(4, 68, b);
					EzabatuErronboa(5, 100, y);
					EzabatuErronboa(6, 134, z);
					EzabatuErronboa(7, 168, a);
				}
				if ((y == 25) && (Pos == 2))
				{
					EGOERA = 1;
					EzabatuErronboHandia(1, 34, 0);
					EzabatuErronboa(3, 34, x);
					EzabatuErronboa(4, 68, b);
					EzabatuErronboa(5, 100, y);
					EzabatuErronboa(6, 134, z);
					EzabatuErronboa(7, 168, a);
				}
				if ((z == 25) && (Pos == 3))
				{
					EGOERA = 1;
					EzabatuErronboHandia(1, 34, 0);
					EzabatuErronboa(3, 34, x);
					EzabatuErronboa(4, 68, b);
					EzabatuErronboa(5, 100, y);
					EzabatuErronboa(6, 134, z);
					EzabatuErronboa(7, 168, a);
				}
				if ((a == 25) && (Pos == 4))
				{
					EGOERA = 1;
					EzabatuErronboHandia(1, 34, 0);
					EzabatuErronboa(3, 34, x);
					EzabatuErronboa(4, 68, b);
					EzabatuErronboa(5, 100, y);
					EzabatuErronboa(6, 134, z);
					EzabatuErronboa(7, 168, a);
				}

			}


			if (EGOERA == 1) {
				erakutsiover();
				x = 250;
				z = 320;
				a = 290;
				touchRead(&PANT_DAT);
				if ((PANT_DAT.px) != 0 || (PANT_DAT.py != 0)) {
					EGOERA = 0;
				}
			}
		}
	}

}
