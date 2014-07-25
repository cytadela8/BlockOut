
#include <head.h>
using namespace std;

enum SpisMenu {Glowne,Generowane,Generowane_wybor,Generowanie_mapy,Blad,Gra_Normalna,Gra_Normalna_Easy,Gra_Normalna_Medium,Gra_Normalna_Hard,Gra_Normalna_Expert,Edytor};
enum Kierunek {nic=0,gora=1,dol=2,lewo=3,prawo=4,restart=5};
enum DanPlik {test,test2};
int const wieltab[2]= {14,10};
Kierunek kier=nic;
short int speed=0,ruch=0,celpozx,celpozy,startx,starty;
bool pozkal[14][10];
int x=0,y=0;
short int V=8;
SpisMenu MenuNum=Glowne;

BITMAP *zaznaczek;
BITMAP *bufor;
BITMAP *mapa;
BITMAP *pionek;
BITMAP *sciana;
BITMAP *tlo;
FONT *font2;
FONT *font2grob;
int nr,ostmouse_x,ostmouse_y;
bool win;
int sprop (int xc,int yc);
int sprek (int xa,int ya,int xc,int yc,short int kierek, bool baz[][10]);
inline short int generator(short int ilruch,short int ildod);
void czyscimenuakt();
long int game(short int a,short int b,long int c);
void rysuj(long int seed);

#include <plik.h>
#include <menu.h>
#include <generator.h>

void LoadMap(UsePlik &ddd,short int num);
void SaveMap(UsePlik &ddd,short int num);

#include <edytor.h>

void edytor(UsePlik &ddd,short int num);

inline void czyscimenu(menu *mena);
const string menu_glowne_dane[]= {"tryb normalny","tryb generowany","edytor","koniec"};
const string menu_gry_normalnej[]= {"EASY","MEDIUM","HARD","EXPERT","wroc"};
const string menu_gry_normalnej_lvl[]= {"poziom 1","poziom 2","poziom 3","poziom 4","poziom 5","poziom 6","poziom 7","poziom 8","poziom 9","poziom 10","poziom 11","poziom 12","poziom 13","poziom 14","poziom 15","poziom 16","poziom 17","poziom 18","poziom 19","poziom 20","wroc"};
const string menu_gry_generowanej[]= {"EASY","MEDIUM","HARD","tryb wyboru","wroc"};
const string menu_gry_generowanej_wybor[]= {"ilosc ruchow","ilosc zbednych klockow","seed","GENERUJ","wroc"};
const string menu_edycja[]={"plansza 1","plansza 2","plansza 3","plansza 4","plansza 5","plansza 6","plansza 7","plansza 8","wroc"};
const string nicek[]= {""};
const string ok[]= {"OK"};
menu *mena[11];
void menownik()
{
    mena[0]=new menu(menu_glowne_dane,4,90,"MENU");
    mena[1]=new menu(menu_gry_generowanej,5,90,"GENEROWANA MAPA");
    mena[2]=new menu(menu_gry_generowanej_wybor,5,90,"TRYB WYBORU GENEROWANIA");
    mena[3]=new menu(nicek,0,SCREEN_H/2-20,"generowanie...");
    mena[4]=new menu(ok,1,SCREEN_H/2-50,"wystapil blad! :<");
    mena[5]=new menu(menu_gry_normalnej,5,90,"GRA NORMALNA");
    mena[6]=new menu_przewijane(menu_gry_normalnej_lvl,21,90,"EASY");
    mena[7]=new menu_przewijane(menu_gry_normalnej_lvl,21,90,"MEDIUM");
    mena[8]=new menu_przewijane(menu_gry_normalnej_lvl,21,90,"HARD");
    mena[9]=new menu_przewijane(menu_gry_normalnej_lvl,21,90,"EXPERT");
    mena[10]=new menu(menu_edycja,9,90,"EDYCJA");
}
void czyscimenuakt()
{
    czyscimenu(mena[MenuNum]);
}
inline void czyscimenu(menu *mene)
{
    draw_sprite(bufor,tlo,0,0);
    (*mene).rysuj();
    draw_sprite(screen,bufor,0,0);
}

void rysuj(long int seed)
{
    for (int i=0; i<wieltab[0]; i++)
    {
        for (int j=0; j<wieltab[1]; j++)
        {
            if (pozkal[i][j])
                draw_sprite (mapa,sciana,i*50+10+40,j*50+10+40);
        }
        rect (mapa,celpozx*50+10+40,celpozy*50+10+40,celpozx*50+50+10+40-1,celpozy*50+50+10+40-1,makecol(0,200,0));
        floodfill(mapa,celpozx*50+25+40,celpozy*50+25+40,makecol(0,200,0));
    }
    opcja tym("seed",550);
    tym.UstLiczbe(seed);
    clear_to_color(bufor,makecol(255,0,255));
    if(seed!=0)
    tym.rysuj();
    draw_sprite(mapa,bufor,0,0);
}

void LoadMap(UsePlik &zrodlo,short int num)
{
	celpozx=zrodlo.AktWartoscCelX(num);
	celpozy=zrodlo.AktWartoscCelY(num);
	startx=zrodlo.AktWartoscStartX(num);
	starty=zrodlo.AktWartoscStartY(num);
	for(int i=0;i<wieltab[0];i++)
	for(int j=0;j<wieltab[1];j++)
	pozkal[i][j]=zrodlo.AktWartoscPoz(num,i,j);
}

void SaveMap(UsePlik &cel,short int num)
{
	cel.UstCelX(num,celpozx);
	cel.UstCelY(num,celpozy);
	cel.UstStartX(num,startx);
	cel.UstStartY(num,starty);
	for(int i=0;i<wieltab[0];i++)
	for(int j=0;j<wieltab[1];j++)
	cel.UstWartoscPoz(num,i,j,pozkal[i][j]);
}

void increment_speed()
{
    speed++;
}
END_OF_FUNCTION(increment_speed);
inline void init()
{
    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    install_int_ex(increment_speed,BPS_TO_TIMER(60));
    install_timer();
    install_keyboard();
    install_mouse();
    show_mouse(screen);
    unscare_mouse();
}

inline void deinit()
{
    clear_keybuf();
    allegro_exit();
}
long int game(short int ilruch,short int ildod,long int seed)
{
    short int tym;
    mapa=load_bmp("mp_szab.bmp",0);
    if (seed!=0)
    {
    if (ilruch==0)
    {
        switch (seed%10)
        {
        case 0:
            ilruch=5;
            ildod=1;
            break;
        case 1:
            ilruch=7;
            ildod=4;
            break;
        case 2:
            ilruch=12;
            ildod=8;
            break;
		case 3:
			ilruch=17;
			ildod=10;
			break;
        }
        srand(seed/10);
    }
    else
        srand(seed);
	startx=0;
	starty=0;
    unsigned short int dop=0;
    while (generator(ilruch,ildod))
    {
        dop++;
        tym=seed%10;
        seed=(int)(rand()*rand())/10*10+tym;
        srand(seed/10);
        if (key[KEY_ESC])
            return 0;
        if (dop>=10000)
        {
            czyscimenu(mena[Blad]);
            while(!key[KEY_ENTER]&&!key[KEY_LEFT]&&!key[KEY_RIGHT]&&!key[KEY_ESC]);
            return 0;
        }
    }
    }
    rysuj(seed);
    speed=0;
    kier=nic;
    ruch=0;
    x=startx*50;
    y=starty*50;
    while (!key[KEY_ESC])
    {
        while (speed>0&&!key[KEY_ESC])
        {
            if (kier==nic)
            {
                if (key[KEY_RIGHT])
                    kier=prawo;
                if (key[KEY_LEFT])
                    kier=lewo;
                if (key[KEY_DOWN])
                    kier=dol;
                if (key[KEY_UP])
                    kier=gora;
                if (key[KEY_R])
                    kier=restart;
                switch (kier)
                {
                case gora:
                {
                    if (pozkal[x/50][y/50-1]||y==0)
                        kier=nic;
                    break;
                }
                case dol:
                {
                    if (pozkal[x/50][y/50+1]||y==wieltab[1]-1)
                        kier=nic;
                    break;
                }
                case lewo:
                {
                    if (pozkal[x/50-1][y/50]||x==0)
                        kier=nic;
                    break;
                }
                case prawo:
                {
                    if (pozkal[x/50+1][y/50]||x==wieltab[0]-1)
                        kier=nic;
                    break;
                }
                }
                if (kier!=nic)
                    ruch++;
            }
            else
            {
                if(key[KEY_R])
                    kier=restart;
                switch (kier)
                {
                case gora:
                {
                    for (int i=0; i<V; i++)
                    {
                        if (y==0)
                            kier=nic;
                        else if ((x)%50==0&&(y)%50==0)
                        {
                            if (pozkal[(x)/50][((y)/50)-1])
                                kier=nic;
                            else
                                y--;
                        }
                        else
                            y--;
                    }

                    break;
                }
                case dol:
                {
                    for (int i=0; i<V; i++)
                        if (y==450)
                            kier=nic;
                        else if ((x)%50==0&&(y)%50==0)
                        {
                            if (pozkal[((x)/50)][((y)/50)+1])
                                kier=nic;
                            else
                                y++;
                        }
                        else
                            y++;
                    break;
                }
                case prawo:
                {
                    for (int i=0; i<V; i++)
                        if (x==650)
                            kier=nic;
                        else if ((x)%50==0&&(y)%50==0)
                        {
                            if (pozkal[((x)/50)+1][((y)/50)])
                                kier=nic;
                            else
                                x++;
                        }
                        else
                            x++;
                    break;
                }
                case lewo:
                {
                    for (int i=0; i<V; i++)
                        if (x==0)
                            kier=nic;
                        else if ((x)%50==0&&(y)%50==0)
                        {
                            if (pozkal[((x)/50)-1][((y)/50)])
                                kier=nic;
                            else
                                x--;
                        }
                        else
                            x--;
                    break;
                }
                case restart:
                {
                    if(y!=0)
                        x-=(double)x/(double)y*V;
                    else
                        x-=V;
                    if(x!=0)
                        y-=(double)y/(double)x*V;
                    else
                        y-=V;
                    if (x<0)
                        x=0;
                    if (y<0)
                        y=0;
                    if(x==0&&y==0)
                        kier=nic;
                }
                }
            }
            clear_to_color(bufor,makecol(255,255,255));
            draw_sprite(bufor,mapa,0,0);
            draw_sprite(bufor,pionek,x+50,y+50);
            draw_sprite(screen,bufor,0,0);
            if ((x)%50==0&&(y)%50==0)
                if (x/50==celpozx&&y/50==celpozy&&kier==nic)
                {
                    allegro_message("WYGRALES w %d ruchach",ruch);
                    win=true;
                    return seed;
                }
            speed--;
            if (speed>10)
                speed=0;
        }
    }
    return seed;
}
int main()
{
    srand(time(0));
    init();
    menownik();
    short int datek[2]= {0};
    UsePlik dane (datek,2,"dane.txt");
    for(int i=dane.AktWartoscInt(0)+1; i<4; i++)
    {
        (*mena[1]).OpcjaBlokuj(i);
        (*mena[5]).OpcjaBlokuj(i);
    }
    for(int i=dane.AktWartoscInt(1)+1; i<20; i++)
    {
    	switch(dane.AktWartoscInt(0))
    	{
    		case 0:
    		(*mena[6]).OpcjaBlokuj(i);
    		break;
    		case 1:
    		(*mena[7]).OpcjaBlokuj(i);
    		break;
    		case 2:
    		(*mena[8]).OpcjaBlokuj(i);
    		break;
    		case 3:
    		(*mena[9]).OpcjaBlokuj(i);
    		break;
    	}

    }
    short int spisek[88]={0};
    for (int i=20;i<80;i+=2)
    spisek[i]=1;
    for (int i=80;i<88;i++)
    spisek[i]=1;
    UsePlik mapy (spisek,88,"mapy.txt");
    tlo=load_bmp("tlo.bmp",0);
    bufor = create_bitmap(800,600);
    pionek=load_bmp("samolot.bmp",0);
    //pionek = create_bitmap(40,40);
    zaznaczek = create_bitmap(50,50);
    clear_to_color(zaznaczek,makecol(255,0,255));
    rect (zaznaczek,0,0,49,49,makecol(200,100,50));
    rect (zaznaczek,1,1,48,48,makecol(200,100,50));
    sciana=load_bmp("klocek.bmp",0);
    //clear_to_color(pionek,makecol(200,0,0));
    font2=load_font("czcionka OCR-A BT.pcx",0,0);
    font2grob=load_font("czcionka OCR-A BT wieksza groba.pcx",0,0);
    bool nacis=false;
    czyscimenu(mena[MenuNum]);
    while (true)
    {
        if (key[KEY_UP]||key[KEY_DOWN])
        {
            if (!nacis)
            {
                if (key[KEY_UP])
                    (*mena[MenuNum]).UstOpcje((*mena[MenuNum]).AktOpcja()-1);
                if (key[KEY_DOWN])
                    (*mena[MenuNum]).UstOpcje((*mena[MenuNum]).AktOpcja()+1);
                nacis=true;
                czyscimenu((mena[MenuNum]));
            }
        }
        else if ((key[KEY_ENTER]||mouse_b==1)||key[KEY_RIGHT])
        {
            if (!nacis)
            {
                if(mouse_b==1)
                    (*mena[MenuNum]).UstOpcjeMysz(mouse_y);
                switch (MenuNum)
                {
                case Glowne:
                {
                    switch ((*mena[MenuNum]).AktOpcja())
                    {
                    case 0:
                    {
                        MenuNum=Gra_Normalna;
                        break;
                    }
                    case 1:
                    {
                        MenuNum=Generowane;
                        break;
                    }
                    case 2:
                    {
                    	MenuNum=Edytor;
                    	break;
                    }
                    case 3:
                    {
                    	mapy.Zapis();
                        deinit();
                        return 0;
                        break;
                    }

                    }
                    break;
                }
                case Gra_Normalna:
                {
                    switch ((*mena[MenuNum]).AktOpcja())
                    {
                    case 0:
                    {

                        MenuNum=Gra_Normalna_Easy;
                        break;
                    }
                    case 1:
                    {
                    	if(dane.AktWartoscInt(0)>0)
                        MenuNum=Gra_Normalna_Medium;
                        break;
                    }
                    case 2:
                    {
                    	if(dane.AktWartoscInt(0)>1)
                        MenuNum=Gra_Normalna_Hard;
                        break;
                    }
                    case 3:
                    {
                    	if(dane.AktWartoscInt(0)>2)
                        MenuNum=Gra_Normalna_Expert;
                        break;
                    }
                    case 4:
                    {
                        MenuNum=Glowne;
                        break;
                    }
                    }
                    break;
                }
                case Gra_Normalna_Expert:
                case Gra_Normalna_Hard:
                case Gra_Normalna_Medium:
                case Gra_Normalna_Easy:
                {
                    switch ((*mena[MenuNum]).AktOpcja())
                    {
                    case 20:
                    {
                        MenuNum=Gra_Normalna;
                        break;
                    }
                    default:
                    {
                    	if ((*mena[MenuNum]).AktOpcja()<=dane.AktWartoscInt(1)||MenuNum-6<dane.AktWartoscInt(0))
                    	{
                    		short int aktek=(*mena[MenuNum]).AktOpcja();
                    		if(aktek%2||MenuNum==6)
                    		{
                    			kier=nic;
                    			ruch=0;
                    			if(mapy.AktWartoscInt(aktek+20*(MenuNum-6))==0)
                    			{
                    				SpisMenu ostmenek=MenuNum;
									MenuNum=Generowanie_mapy;
									czyscimenu((mena[MenuNum]));
									MenuNum=ostmenek;
                    				mapy.UstWartoscInt(aktek+20*(MenuNum-6),(int)(rand()*rand())/10*10+(MenuNum-6));
                    				mapy.Zapis();

                    			}
                    			win=false;
                    			mapy.UstWartoscInt(aktek+20*(MenuNum-6),game(0,0,mapy.AktWartoscInt(aktek+20*(MenuNum-6))));
                    			if(win&&dane.AktWartoscInt(1)==aktek&&dane.AktWartoscInt(0)==(MenuNum-6))
								{
									dane.UstWartoscInt(1,(dane.AktWartoscInt(1)+1));
									if(dane.AktWartoscInt(1)>19)
									{
										dane.UstWartoscInt(1,0);
										dane.UstWartoscInt(0,dane.AktWartoscInt(0)+1);
										(*mena[Gra_Normalna]).OpcjaOdblokuj(dane.AktWartoscInt(0));
										if(dane.AktWartoscInt(0)-1!=3)
										for(int i=0;i<20;i++)
										(*mena[MenuNum+1]).OpcjaBlokuj(i);

									}
									(*mena[MenuNum]).OpcjaOdblokuj(aktek+1);
									dane.Zapis();
								}
                    		}
                    		else
                    		{
                    			LoadMap(mapy,aktek+20*(MenuNum-6));
								kier=nic;
								ruch=0;
								win=false;
								game(0,0,0);
								if(win&&dane.AktWartoscInt(1)==aktek&&dane.AktWartoscInt(0)==(MenuNum-6))
								{
									dane.UstWartoscInt(1,(dane.AktWartoscInt(1)+1));
									if(dane.AktWartoscInt(1)>19)
									{
										dane.UstWartoscInt(1,0);
										dane.UstWartoscInt(0,dane.AktWartoscInt(0)+1);

									}
									(*mena[MenuNum]).OpcjaOdblokuj(aktek+1);
									dane.Zapis();
								}
                    		}
                    	}
                        break;
                    }
                    }
                    break;
                }
                case Generowane:
                {
                    switch((*mena[MenuNum]).AktOpcja())
                    {
                    case 0:
                    {

                        kier=nic;
                        ruch=0;
                        SpisMenu ostmenek=MenuNum;
                        MenuNum=Generowanie_mapy;
                        czyscimenu((mena[MenuNum]));
                        MenuNum=ostmenek;
                        game(0,0,(int)(rand()*rand())/10*10+0);
                        break;
                    }
                    case 1:
                    {
                        if(dane.AktWartoscInt(0)>0)
                        {
                            kier=nic;
                            ruch=0;
                            SpisMenu ostmenek=MenuNum;
                            MenuNum=Generowanie_mapy;
                            czyscimenu((mena[MenuNum]));
                            MenuNum=ostmenek;
                            game(0,0,(int)(rand()*rand())/10*10+1);
                        }
                        break;
                    }
                    case 2:
                    {
                        if(dane.AktWartoscInt(0)>1)
                        {
                            kier=nic;
                            ruch=0;
                            SpisMenu ostmenek=MenuNum;
                            MenuNum=Generowanie_mapy;
                            czyscimenu((mena[MenuNum]));
                            MenuNum=ostmenek;
                            game(0,0,(int)(rand()*rand())/10*10+2);
                        }
                        break;

                    }
                    case 3:
                    {
                    	if(dane.AktWartoscInt(0)>2)
                        MenuNum=Generowane_wybor;
                        break;
                    }
                    case 4:
                    {
                        MenuNum=Glowne;
                        break;
                    }
                    }
                    break;
                }
                case Generowane_wybor:
                {
                    switch ((*mena[MenuNum]).AktOpcja())
                    {
                    case 0:
                    case 1:
                    {
                        (*mena[MenuNum]).OpcjaEdycjaUserLiczby((*mena[MenuNum]).AktOpcja(),0,100);
                        break;
                    }
                    case 2:
                    {
                        (*mena[MenuNum]).OpcjaEdycjaUserLiczby((*mena[MenuNum]).AktOpcja());
                        break;
                    }
                    case 3:
                    {
                        kier=nic;
                        ruch=0;
                        SpisMenu ostmenek=MenuNum;
                        MenuNum=Generowanie_mapy;
                        czyscimenu((mena[MenuNum]));
                        MenuNum=ostmenek;
                        if((*mena[ostmenek]).OpcjaAktLiczba(2)==0)
                            game((*mena[ostmenek]).OpcjaAktLiczba(0),(*mena[ostmenek]).OpcjaAktLiczba(1),rand());
                        else
                            game((*mena[ostmenek]).OpcjaAktLiczba(0),(*mena[ostmenek]).OpcjaAktLiczba(1),(*mena[ostmenek]).OpcjaAktLiczba(2));
                        break;
                    }
                    case 4:
                    {
                        MenuNum=Generowane;
                        break;
                    }
                    }
                    break;
                }
                case Edytor:
                {
                	switch((*mena[MenuNum]).AktOpcja())
                	{
                		case 8:
                		{
                			MenuNum=Glowne;
                			break;
                		}
                		default:
                		{
                			edytor(mapy,(*mena[MenuNum]).AktOpcja()+80);
                			break;
                		}
                	}
                	break;
                }
                }

                czyscimenu((mena[MenuNum]));
                nacis=true;
            }
        }
        else if (key[KEY_ESC]||key[KEY_LEFT])
        {
            if(!nacis)
            {
                switch (MenuNum)
                {
				case Glowne:
				{
					mapy.Zapis();
					deinit();
					return 0;
					break;
				}
				case Edytor:
                case Gra_Normalna:
                case Generowane:
                {
                    MenuNum=Glowne;
                    czyscimenu((mena[MenuNum]));
                    break;
                }
                case Generowane_wybor:
                {
                    MenuNum=Generowane;
                    czyscimenu((mena[MenuNum]));
                    break;
                }
                case Gra_Normalna_Expert:
                case Gra_Normalna_Hard:
                case Gra_Normalna_Medium:
                case Gra_Normalna_Easy:
                {
                    MenuNum=Gra_Normalna;
                    czyscimenu((mena[MenuNum]));
                    break;
                }
                }
                nacis=true;
            }

        }
        else
            nacis=false;
        //textprintf(screen, font, 20, 20, makecol(255,255,0), "%d", mouse_y);
        if (mouse_y!=ostmouse_y||mouse_x!=ostmouse_x)
        {
            (*mena[MenuNum]).UstOpcjeMysz(mouse_y);
            czyscimenu((mena[MenuNum]));
        }
        ostmouse_x=mouse_x;
        ostmouse_y=mouse_y;

        if (speed>10) speed=0;
    }
    mapy.Zapis();
    deinit();
    return 0;
}
END_OF_MAIN()

