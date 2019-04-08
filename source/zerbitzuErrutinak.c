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
int seg3;
int x = 250; // TODO: Que es x?

void tekEten ()
{
	// El codigo que venia
	/*if (EGOERA == ITXITA)
	{	
		if (SakatutakoTekla()==A)
		{
			EGOERA=IREKITA;
			iprintf("\x1b[13;5HPasa diren segunduak=0");
			erakutsiAteaIrekita();
			seg3=0;
			ErakutsiErronboa(1, 5, 5);
			ErakutsiErronboHandia(2, 100, 100);
		}
	}*/

	if (SakatutakoTekla() == START)
	{

		EGOERA = 2;
		ErlojuaMartxanJarri();
		erakutsiPato();


	}

	if (SakatutakoTekla() == SELECT)
	{
		EGOERA = 0;

		EzabatuErronboHandia(1, 0, 150);


	}
}

void tenpEten()
{
	static int tik=0;
	static int seg=0;
	static int seg1 = 0; // TODO: Mirar que hace seg1

	// El codigo que venia	
	/*if (EGOERA!=ZAI)
	{
		tik++; 
		if (tik==5)
		{
			seg++;
			iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
			tik=0;
			if (EGOERA == IREKITA)
			{
				seg3++;
				if (seg3==3)
				{
					erakutsiAtea();
					seg3=0;
					EGOERA=ITXITA;
					EzabatuErronboa(1, 5, 5);
					EzabatuErronboHandia(2, 100, 100);
				}
			}
				
		}*/

	if (EGOERA == 2)
	{
		tik++;
		if (tik == 5)
		{
			seg1++;
			seg++;
			if (seg1 * 25 > 320) { seg1 = 0; }
			tik1 = seg1;

			iprintf("\x1b[13;5HPuntuak=%d", seg);
			tik = 0;
		}

	}

	if (EGOERA == 1) { seg = 0; seg1 = 0; }// Hasieratu egin behar da
}
	
}

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}

