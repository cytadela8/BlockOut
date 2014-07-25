#include<sstream>
short int const WspolczynnikCienia=50;
class opcja
{
	public:
	opcja(string tekstek,unsigned short const pozek);
	~opcja();
	void zaznacz() {wybr=true;}
	void odznacz() {wybr=false;}
	void blokuj() {blok=true;}
	void odblokuj() {blok=false;}
	int AktLiczba() const{return dopisekliczba;}
	void UstLiczbe(long int liczbaek){dopisekliczba=liczbaek;}
	void EdycjaUserLiczby() {EdycjaUserLiczby(-2147483646,2147483646);}
	void EdycjaUserLiczby(long int min,long int max);
	void rysuj(int pozek) {poz=pozek; rysuj();}
	void rysuj() const
	{
		ostringstream ss;
		ss << dopisekliczba;
		string tekstek;
		if (dopisekliczba==0)
		tekstek=tekst;
		else
		tekstek=tekst+":"+ss.str();
		short int pozx,pozy,cieniowanie,cieniowanie2,cieniowanie3;
		pozy=poz;
		if (wybr&&!blok)
		pozx=SCREEN_W/2 - text_length(font2grob, tekstek.c_str())/2;
		else
		pozx=SCREEN_W/2 - text_length(font2, tekstek.c_str())/2;
		if(!blok)
		{
			pozx+=4;
			pozy+=4;
		}
		for (;pozy>=poz;pozx--,pozy--)
		if (wybr)
		{
			cieniowanie=(pozy-poz)*WspolczynnikCienia;
			if (cieniowanie>250)
			cieniowanie=250;
			cieniowanie2=(pozy-poz)*WspolczynnikCienia;
			if (cieniowanie2>100)
			cieniowanie2=100;
			cieniowanie3=(pozy-poz)*WspolczynnikCienia;
			if (cieniowanie3>50)
			cieniowanie3=50;
			if(blok)
		    textout_ex(bufor,font2,tekstek.c_str(), pozx, pozy, makecol(100-cieniowanie,100-cieniowanie2,100-cieniowanie3), -1);
			else
		    textout_ex(bufor,font2grob,tekstek.c_str(), pozx, pozy, makecol(250-cieniowanie,100-cieniowanie2,50-cieniowanie3), -1);
		}

		else
		{
			cieniowanie=(pozy-poz)*WspolczynnikCienia;
			if (cieniowanie>250)
			cieniowanie=250;
    		textout_ex(bufor,font2,tekstek.c_str(), pozx, pozy, makecol(250-cieniowanie,250-cieniowanie,250-cieniowanie), -1);
		}
	}
	private:
	bool wybr;
	bool blok;
	string tekst;
	long int dopisekliczba;
	unsigned short int poz;
};
opcja::opcja(string tekstek,unsigned short const pozek)
{
	wybr=false;
	blok=false;
	dopisekliczba=0;
	tekst=tekstek;
	poz=pozek;
}
opcja::~opcja()
{
}
void opcja::EdycjaUserLiczby(long int min,long int max)
{
	bool nacis=true;
	bool nacisczas=false;
	while(key[KEY_ENTER]||key[KEY_RIGHT])
	;
	while(!key[KEY_ENTER]&&!key[KEY_ESC]&&!key[KEY_LEFT])
	{
		if (key[KEY_0]||key[KEY_0_PAD])
		{
			if(!nacis)
			{
				if (dopisekliczba<max/10&&dopisekliczba>min/10)
				dopisekliczba*=10;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_1]||key[KEY_1_PAD])
		{
			if(!nacis)
			{
				dopisekliczba*=10;
				dopisekliczba+=1;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_2]||key[KEY_2_PAD])
		{
			if(!nacis)
			{
				dopisekliczba*=10;
				dopisekliczba+=2;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_3]||key[KEY_3_PAD])
		{
			if(!nacis)
			{
				dopisekliczba*=10;
				dopisekliczba+=3;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_4]||key[KEY_4_PAD])
		{
			if(!nacis)
			{
				dopisekliczba*=10;
				dopisekliczba+=4;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_5]||key[KEY_5_PAD])
		{
			if(!nacis)
			{
			    dopisekliczba*=10;
				dopisekliczba+=5;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_6]||key[KEY_6_PAD])
		{
			if(!nacis)
			{
			    dopisekliczba*=10;
				dopisekliczba+=6;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_7]||key[KEY_7_PAD])
		{
			if(!nacis)
			{
			    dopisekliczba*=10;
				dopisekliczba+=7;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_8]||key[KEY_8_PAD])
		{
			if(!nacis)
			{
			    dopisekliczba*=10;
				dopisekliczba+=8;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_9]||key[KEY_9_PAD])
		{
			if(!nacis)
			{
			    dopisekliczba*=10;
				dopisekliczba+=9;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
			}
			nacis=true;
		}
		else
		if (key[KEY_BACKSPACE])
		{
		    if(!nacis)
		    {
		        dopisekliczba/=10;
		        if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
		        czyscimenuakt();

		        nacis=true;
				speed=0;
				nacisczas=true;
		    }
		    else
			{
				if(nacisczas&&speed>30)
				{
					speed=25;
					dopisekliczba/=10;
					if (dopisekliczba>max)
					dopisekliczba=max;
					if (dopisekliczba<min)
					dopisekliczba=min;
					czyscimenuakt();
				}
			}
		}
		else
		if (key[KEY_DOWN])
		{
			if(!nacis)
			{
				dopisekliczba--;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();
				nacis=true;
				speed=0;
				nacisczas=true;
			}
			else
			{
				if(nacisczas&&speed>60)
				{
					speed=50;
					dopisekliczba--;
					if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
					czyscimenuakt();
				}
			}
		}
		else
		if (key[KEY_UP])
		{
			if(!nacis)
			{
				dopisekliczba++;
				if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
				czyscimenuakt();

				nacis=true;
				speed=0;
				nacisczas=true;
			}
			else
			{
				if(nacisczas&&speed>60)
				{
					speed=50;
					dopisekliczba++;
					if (dopisekliczba>max)
				dopisekliczba=max;
				if (dopisekliczba<min)
				dopisekliczba=min;
					czyscimenuakt();
				}
			}

		}
		else
		if (key[KEY_MINUS])
		{
			if(!nacis)
			{
				dopisekliczba*=-1;
				nacis=true;
			}
		}
		else
		{
			nacisczas=false;
			nacis=false;
		}

	}
}
class menu
{
	public:
	menu(string const tab[],unsigned short int ilopek,unsigned short int poczpoz,string const & tytol);
	~menu();
	virtual int rysuj() const;
	unsigned short int AktOpcja() const {return wybor;}
	virtual void UstOpcjeMysz(short int mysz);
	void OpcjaBlokuj(short int wyborek) {(*wskaz[wyborek]).blokuj();}
	void OpcjaOdblokuj(short int wyborek) {(*wskaz[wyborek]).odblokuj();}
	void OpcjaEdycjaUserLiczby(short int wyborek) const {(*wskaz[wyborek]).EdycjaUserLiczby();}
	void OpcjaEdycjaUserLiczby(short int wyborek,long int min,long int max) const {(*wskaz[wyborek]).EdycjaUserLiczby(min,max);}
	int OpcjaAktLiczba(short int wyborek)const {return (*wskaz[wyborek]).AktLiczba();}
	void UstOpcje(short int wyborek)
	{
		if (wyborek<0)
		wyborek=ilop-1;
		if (wyborek>ilop-1)
		wyborek=0;
		(*wskaz[wybor]).odznacz();
		wybor=wyborek;
		(*wskaz[wybor]).zaznacz();
	}
	protected:
	unsigned short int wybor,ilop,poczpoz;
	opcja * wskaz[21];
	opcja * tytol;
};
menu::menu(string const tab[],unsigned short int ilopek,unsigned short int poczpozek,string const & tytolek)
{
	wybor=0;
	poczpoz=poczpozek;
	poczpoz+=60;
	ilop=ilopek;
	for (int i=0;i<20;i++)
	wskaz[i]=0;
	for (unsigned short int i=0,j=poczpoz;i<ilop;i++,j+=50)
	{
		wskaz[i]=new opcja(tab[i],j);
	}
	if (ilop>0) (*wskaz[0]).zaznacz();
	tytol=new opcja(tytolek,poczpoz-60);
	(*tytol).zaznacz();
}
menu::~menu()
{
	delete tytol;
	for (int i=0;i<ilop;i++)
	delete wskaz[i];
}
int menu::rysuj() const
{
	(*tytol).rysuj();
	for (int i=0;i<ilop;i++)
	{
		(*wskaz[i]).rysuj();
	}

	return 0;
}
void menu::UstOpcjeMysz(short int mysz)
{
	short int wyborek=(mysz-poczpoz)/50;
	if (wyborek>=0&&wyborek<ilop)
	{
		(*wskaz[wybor]).odznacz();
		wybor=wyborek;
		(*wskaz[wybor]).zaznacz();
	}
}
class menu_przewijane:public menu
{
	public:
	menu_przewijane(string const tab[],unsigned short int ilopek,unsigned short int poczpoz,string const & tytol):menu(tab,ilopek,poczpoz,tytol){;}
	void UstOpcjeMysz(short int mysz) {;}
	int rysuj() const;
};
int menu_przewijane::rysuj() const
{
	(*tytol).rysuj();
	int i=wybor;
	if(i>ilop-5)
	i=ilop-5;
	i-=4;
	if(i<0)
	i=0;
	int zmniej_wys=i*50;
	for (;i<ilop;i++)
	{
		(*wskaz[i]).rysuj(poczpoz+50*i-zmniej_wys);
	}
	return 0;
}
