/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; //sakatutako tekla gordetzeko aldagaia



int TeklaDetektatu() 
{
	//TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	return (~TEKLAK_DAT & 0x03ff) != 0);
}

int SakatutakoTekla() 
{

	//Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	//Gora=6;Behera=7;R=8;L=9;


	

}

void konfiguratuTeklatua(int TEK_konf)
{
	//Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	//Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	DENB0_DAT = Latch;
	DENB0_KNT = TENP_konf;
	
	
}

void TekEtenBaimendu()
{
	//Teklatuaren etenak baimendu
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
	IME=1;
}

void TekEtenGalarazi()
{

	//Teklatuaren etenak galarazi
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
	IME=1;
}  

void DenbEtenBaimendu()
{

//Denboragailu baten etenak baimendu (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
	IME=1;
}

void DenbEtenGalarazi()
{

//Denboragailu baten etenak galarazi (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
	IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	
}
