/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; // sakatutako tekla gordetzeko aldagaia



int TeklaDetektatu() 
{
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	return (~TEKLAK_DAT & 0x03ff) != 0);
}

int SakatutakoTekla() 
{

	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	// Gora=6;Behera=7;R=8;L=9;


	if ((TEKLAK_DAT & 0x0001) == 0) return A;
	if ((TEKLAK_DAT & 0x0002) == 0) return B;
	if ((TEKLAK_DAT & 0x0004) == 0) return SELECT;
	if ((TEKLAK_DAT & 0x0008) == 0) return START;
	if ((TEKLAK_DAT & 0x0010) == 0) return ESKUBI;
	if ((TEKLAK_DAT & 0x0020) == 0) return EZKER;
	if ((TEKLAK_DAT & 0x0040) == 0) return GORA;
	if ((TEKLAK_DAT & 0x0080) == 0) return BEHERA;
	if ((TEKLAK_DAT & 0x0100) == 0) return R;
	if ((TEKLAK_DAT & 0x0200) == 0) return L;

}

void konfiguratuTeklatua(int TEK_konf)
{
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	TEKLAK_KNT = TEKLAK_KNT | TEK_konf;
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	DENB0_DAT = Latch;
	DENB0_KNT = DENB0_KNT | TENP_konf;
	
	
}

void TekEtenBaimendu()
{
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE | 0x00001000;
	IME=1;
}

void TekEtenGalarazi()
{

	//Teklatuaren etenak galarazi
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE | 0xFFFFEFFF;
	IME=1;
}  

void DenbEtenBaimendu()
{

	// Denboragailu baten etenak baimendu (Timer0)
	// Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE | 0x00000008;
	IME=1;
}

void DenbEtenGalarazi()
{

	// Denboragailu baten etenak galarazi (Timer0)
	// Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IE = IE & 0xFFFFFFF7;
	IME=1;

}

void ErlojuaMartxanJarri()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT = DENB0_KNT | 0x0080;
}

void ErlojuaGelditu()
{
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	DENB0_KNT = DENB0_KNT & 0xFF7F;
}
