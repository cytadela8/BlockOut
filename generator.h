int sprek (int xa,int ya,int xc,int yc,short int kierek, bool baz[][10])
{
	bool czyk=true;
	short int tym2=0;
	switch (kierek)
	{
		case gora:
		{
			if (ya==0)
			return 0;
			for (int i=ya;i>0;i--)
			{
				if (pozkal[xa][i-1])
				{
					if (ya==i)
					return 0;
					ya=i;
					czyk=false;
					break;
				}
			}
			if (czyk)
			ya=0;
			break;
		}
		case dol:
		{
			if (ya==wieltab[1])
			return 0;
			for (int i=ya;i<wieltab[1]-1;i++)
			{
				if (pozkal[xa][i+1])
				{
					if (ya==i)
					return 0;
					ya=i;
					czyk=false;
					break;
				}
			}
			if (czyk)
			ya=wieltab[1]-1;
			break;
		}
		case lewo:
		{
			if (xa==0)
			return 0;
			for (int i=xa;i>0;i--)
			{
				if (pozkal[i-1][ya])
				{
					if (xa==i)
					return 0;
					xa=i;
					czyk=false;
					break;
				}
			}
			if (czyk)
			xa=0;
			break;
		}
		case prawo:
		{
			if (xa==wieltab[0])
			return 0;
			for (int i=xa;i<wieltab[0]-1;i++)
			{
				if (pozkal[i+1][ya])
				{
					if (xa==i)
					return 0;
					xa=i;
					czyk=false;
					break;
				}
			}
			if (czyk)
			xa=wieltab[0]-1;
			break;
		}
	}
	if (xa==xc&&ya==yc)
	return 1;
	if (baz[xa][ya])
	return 0;
	baz[xa][ya]=true;
	bool baz2[wieltab[0]][10];
	for (int i=0;i<wieltab[0];i++)
	for (int j=0;j<wieltab[1];j++)
	baz2[i][j]=baz[i][j];
	int xa2=xa;
	int ya2=ya;
	if (kierek==lewo||kierek==prawo)
	{
		tym2+=sprek (xa,ya,xc,yc,gora,baz);
		tym2+=sprek (xa2,ya2,xc,yc,dol,baz2);
	}
	else
	{
		tym2+=sprek (xa,ya,xc,yc,lewo,baz);
		tym2+=sprek (xa2,ya2,xc,yc,prawo,baz2);
	}
	if (tym2>=2)
	return 2;
	return tym2;
}
int sprop (int xc,int yc)
{
	bool baz[wieltab[0]][10];
	for (int i=0;i<wieltab[0];i++)
	{
		for (int j=0;j<wieltab[1];j++)
		{
			baz[i][j]=false;
		}
	}
	if (xc==0&&yc==0)
	return 2;
	baz[0][0]=true;
	short int tym=0;
	bool baz2[wieltab[0]][10];
	for (int i=0;i<wieltab[0];i++)
	for (int j=0;j<wieltab[1];j++)
	baz2[i][j]=baz[i][j];
	tym+=sprek(0,0,xc,yc,dol,baz);
	tym+=sprek(0,0,xc,yc,prawo,baz2);
	if (tym>=2)
	return 2;
	return tym;
}

inline short int generator(short int ilruch,short int ildod)
{
	bool kon,tmp;
	short int licz=0,wnios;
    short int odl,ostkier;
    bool tab[wieltab[0]][wieltab[1]];
    for (int i=0;i<wieltab[0];i++)
    {
    	for (int j=0;j<wieltab[1];j++)
    	{
    		tab[i][j]=false;
    		pozkal[i][j]=false;
    	}
    }
    tab[0][0]=true;
    x=0;
    y=0;
    kier=nic;
    kon=true;
    for (int i=0;i<ilruch;i++)
    {
    	licz=0;
    	while (1==1)
        {
        	if (kon)
        	ostkier=kier;
        	licz++;
        	if (licz>50)
        	return 1;
        	kier=(Kierunek)(rand()%4+1);
        	kon=false;
        	if ((kier==gora&&y==0)||(kier==lewo&&x==0)||(kier==prawo&&x==(wieltab[0]-1))||(kier==dol&&y==(wieltab[1]-1)))
			continue;
			if (ostkier==kier)
			continue;

			switch (kier)
			{
				case dol:
				{
					if (ostkier==gora)
					continue;
       				odl=rand()%(wieltab[1]-y-1)+1;
       				kon=false;
       				for (int j=1;j<=odl;j++)
       				{
       					if (pozkal[x][y+j])
       					{
       						kon=true;
       						break;
       					}
       				}
					if (kon)
					{
						kon=false;
						continue;
					}
					kon=false;
					if (tab[x][y+odl])
					continue;
					if (y+odl+1<wieltab[1])
					{
						if (tab[x][y+odl+1])
						continue;
						tmp=pozkal[x][y+odl+1];
						pozkal[x][y+odl+1]=true;
					}
					wnios=sprop(x,y+odl);
					if (!wnios)
					return 1;
					if (wnios==2)
					{
						if (y+odl+1<wieltab[1])
						pozkal[x][y+odl+1]=tmp;
						continue;
					}
					for (int j=1;j<=odl;j++)
					{
						tab[x][y+j]=true;
					}
       				kon=true;
       				y+=odl;
       				break;
				}
				case gora:
				{
					if (ostkier==dol)
					continue;
					odl=rand()%y+1;
       				kon=false;
       				for (int j=1;j<=odl;j++)
       				{
       					if (pozkal[x][y-j])
       					{
       						kon=true;
       						break;
       					}
       				}
					if (kon)
					{
						kon=false;
						continue;
					}
					kon=false;
					if (tab[x][y-odl])
					continue;
					if (y-odl>0)
					{
						if (tab[x][y-odl-1])
						continue;
						tmp=pozkal[x][y-odl-1];
						pozkal[x][y-odl-1]=true;
					}
					wnios=sprop(x,y-odl);
					if (!wnios)
					return 1;
					if (wnios==2)
					{
						if (y-odl>0)
						pozkal[x][y-odl-1]=tmp;
						continue;
					}
					for (int j=1;j<=odl;j++)
					{
						tab[x][y-j]=true;
					}
       				kon=true;
       				y-=odl;
       				break;
       			}
				case prawo:
				{
					if (ostkier==lewo)
					continue;
					odl=rand()%(wieltab[0]-x-1)+1;
       				kon=false;
       				for (int j=1;j<=odl;j++)
       				{
       					if (pozkal[x+j][y])
       					{
       						kon=true;
       						break;
       					}
       				}
					if (kon)
					{
						kon=false;
						continue;
					}
					kon=false;
					if (tab[x+odl][y])
					continue;
					if (x+odl+1<wieltab[0])
					{
						if (tab[x+odl+1][y])
						continue;
						tmp=pozkal[x+odl+1][y];
						pozkal[x+odl+1][y]=true;
					}
					wnios=sprop(x+odl,y);
					if (!wnios)
					return 1;
					if (wnios==2)
					{
						if (x+odl+1<wieltab[0])
						pozkal[x+odl+1][y]=tmp;
						continue;
					}
					for (int j=1;j<=odl;j++)
					{
						tab[x+j][y]=true;
					}
       				kon=true;
       				x+=odl;
       				break;
				}
				case lewo:
				{
					if (ostkier==prawo)
					continue;
					odl=rand()%x+1;
       				kon=false;
       				for (int j=1;j<=odl;j++)
       				{
       					if (pozkal[x-j][y])
       					{
       						kon=true;
       						break;
       					}
       				}
					if (kon)
					{
						kon=false;
						continue;
					}
					kon=false;
					if (tab[x-odl][y])
					continue;
					if (x-odl>0)
					{
						if (tab[x-odl-1][y])
						continue;
						tmp=pozkal[x-odl-1][y];
						pozkal[x-odl-1][y]=true;
					}
					wnios=sprop(x-odl,y);
					if (!wnios)
					return 1;
					if (wnios==2)
					{
						if (x-odl>0)
						pozkal[x-odl-1][y]=tmp;
						continue;
					}
					for (int j=1;j<=odl;j++)
					{
						tab[x-j][y]=true;
					}
					x-=odl;
       				kon=true;
       				break;
       			}


       		}
       		if (kon)
			break;
       	}





    }
    celpozx=x;
    celpozy=y;
    licz=0;
    for (int i=0;i<ildod;i++)
    {
    	licz=0;
        while (true)
        {
            licz++;
            if (licz>50)
            return 1;
            x=rand()%wieltab[0];
            y=rand()%wieltab[1];
            if (tab[x][y]||pozkal[x][y])
            continue;
            pozkal[x][y]=true;
            wnios=sprop(celpozx,celpozy);
            if (!wnios)
            return 1;
            if (wnios>=2)
            {
                pozkal[x][y]=false;
                continue;
            }
            break;
        }
    }
    return 0;
}
