#ifndef PLIK_H_INCLUDED
#define PLIK_H_INCLUDED

class dana
{
	public:
	dana(short int numek);
	~dana();
	virtual void WczytajInt (long int a) {;}
	virtual int zaladuj(fstream &plik)=0;
	virtual void zapisz(fstream &plik)=0;
	virtual long int const AktWartoscInt() {;}
	virtual bool const AktWartoscPoz(short int wyborekX,short int wyborekY) {;}
	virtual short int const AktWartoscStartX() {;}
	virtual short int const AktWartoscStartY() {;}
	virtual short int const AktWartoscCelX() {;}
	virtual short int const AktWartoscCelY() {;}
	virtual void UstWartoscPoz(short int wyborekX,short int wyborekY,bool wart) {;}
	virtual void UstStartX(short int wart) {;}
	virtual void UstStartY(short int wart) {;}
	virtual void UstCelX(short int wart) {;}
	virtual void UstCelY(short int wart) {;}
	private:
	short int num;
	bool zmian;
};
dana::dana(short int numek)
{
	num=numek;
	zmian=false;
}
dana::~dana()
{
	;
}
class danalongint:public dana
{
	public:
	danalongint(short int numek):dana(numek){info=0;}
	~danalongint(){;}
	int zaladuj(fstream &plik);
	void zapisz(fstream &plik);
	long int const AktWartoscInt(){return info;}
	void WczytajInt (long int danek) {info=danek;}
	private:
	long int info;
};
int danalongint::zaladuj(fstream &plik)
{
	if(plik>>info)
	return 0;
	else
	return 1;
}
void danalongint::zapisz(fstream &plik)
{
	plik<<info<<" ";
}
class danamapa:public dana
{
	public:
	danamapa(short int numek):dana(numek){for(int i=0;i<14;i++)for(int j=0;j<10;j++)tab[i][j]=false;celx=0;cely=0;startx=0;starty=0;}
	~danamapa(){;}
	bool const AktWartoscPoz(short int wyborekX,short int wyborekY) {return tab[wyborekX][wyborekY];}
	short int const AktWartoscStartX() {return startx;}
	short int const AktWartoscStartY() {return starty;}
	short int const AktWartoscCelX() {return celx;}
	short int const AktWartoscCelY() {return cely;}
	void UstWartoscPoz(short int wyborekX,short int wyborekY,bool wart) {tab[wyborekX][wyborekY]=wart;}
	void UstStartX(short int wart) {startx=wart;}
	void UstStartY(short int wart) {starty=wart;}
	void UstCelX(short int wart) {celx=wart;}
	void UstCelY(short int wart) {cely=wart;}
	void zapisz(fstream &plik);
	int zaladuj(fstream &plik);
	private:
	bool tab[14][10];
	short int celx,cely,startx,starty;
};
int danamapa::zaladuj(fstream &plik)
{
	plik>>celx;
	plik>>cely;
	plik>>startx;
	plik>>starty;
	short int tym,tym2;
	plik>>tym;
	while(tym!=9999)
	{
		plik>>tym2;
		tab[tym][tym2]=true;
		plik>>tym;
	}
	return 0;
}
void danamapa::zapisz(fstream &plik)
{
	plik << celx << " " << cely << " " << startx << " " << starty << " ";
	for (int i=0;i<14;i++)
	for (int j=0;j<10;j++)
	{
		if(tab[i][j])
		plik << i << " " << j << " ";
	}
	plik << 9999 << " ";
}
class UsePlik
{
	public:
	UsePlik(short int danrodzek[],short int ildan,string sciezek);
	~UsePlik(){;}
	long int AktWartoscInt(int wyborek) {return (*dane[wyborek]).AktWartoscInt();}
	void UstWartoscInt(int wyborek,long int wartosc) {(*dane[wyborek]).WczytajInt(wartosc);}
	void DodajInt(){dane[ildan]=new danalongint(ildan);ildan++;}
	void Zapis();

	bool const AktWartoscPoz(short int wyborek,short int wyborekX,short int wyborekY) {(*dane[wyborek]).AktWartoscPoz(wyborekX,wyborekY);}
	short int const AktWartoscStartX(short int wyborek) {(*dane[wyborek]).AktWartoscStartX();}
	short int const AktWartoscStartY(short int wyborek) {(*dane[wyborek]).AktWartoscStartY();}
	short int const AktWartoscCelX(short int wyborek) {(*dane[wyborek]).AktWartoscCelX();}
	short int const AktWartoscCelY(short int wyborek) {(*dane[wyborek]).AktWartoscCelY();}
	void UstWartoscPoz(short int wyborek,short int wyborekX,short int wyborekY,bool wart) {(*dane[wyborek]).UstWartoscPoz(wyborekX,wyborekY,wart);}
	void UstStartX(short int wyborek,short int wart) {(*dane[wyborek]).UstStartX(wart);}
	void UstStartY(short int wyborek,short int wart) {(*dane[wyborek]).UstStartY(wart);}
	void UstCelX(short int wyborek,short int wart) {(*dane[wyborek]).UstCelX(wart);}
	void UstCelY(short int wyborek,short int wart) {(*dane[wyborek]).UstCelY(wart);}

	private:
	short int danrodz[100];
	dana * dane[100];
	string sciezka;
	int ildan;
};
UsePlik::UsePlik(short int danrodzek[],short int ildanek,string sciezek)
{
	int i;
	sciezka=sciezek;
	fstream *plik;
	ildan=ildanek;
	plik=new fstream(sciezka.c_str(),ios::in);
	bool co=true;
	if(!((*plik).is_open()))
	{
		co=false;
		(*plik).close();
		delete plik;
		plik=new fstream(sciezka.c_str(),ios::out);
	}
	for(i=0;i<ildan;i++)
	{
		danrodz[i]=danrodzek[i];
		switch(danrodz[i])
		{
			case 0:
			dane[i]=new danalongint(i);
			break;
			case 1:
			dane[i]=new danamapa(i);
			break;
		}
		if(co)
		(*dane[i]).zaladuj(*plik);
		else
		(*dane[i]).zapisz(*plik);
	}
	(*plik).close();
	for(;i<100;i++)
	dane[i]=0;

}
void UsePlik::Zapis()
{
	fstream plik(sciezka.c_str(),ios::out);
	for(int i=0;i<ildan;i++)
	(*dane[i]).zapisz(plik);
}
#endif // PLIK_H_INCLUDED
