
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MNOZNIK 3
#define DZIELNIK 2

char *czytaj(int *ile) 
//funkcja, która będzie nam wczytywała znaki i zapisywała jedynie te, które nie są komentarzami, spacją, tabulacją lub enterem
{
	bool ignoruj = false;
    char *wynik = NULL;
    int rozmiar = 0;
    int i;
    char znak;
    for (i = 0; ((znak = getchar())) && (znak != EOF); ++i) 
    {
        assert(i < INT_MAX);
        if(znak==';') ignoruj = true;
        if(znak=='\n') ignoruj = false;
        if(ignoruj == false) 
        {
        if (i == rozmiar) 
        {
            rozmiar = 1 + rozmiar * MNOZNIK / DZIELNIK;
            wynik = realloc(wynik, rozmiar * sizeof *wynik);
            assert(wynik != NULL);
        }
        
        if(znak==' ' || znak=='\t' || znak=='\n' ) i--;
		else wynik[i] = znak; //ignorowanie spacji, tabulacji i enterów

		}
		else i--; //cofanie indeksu, gdy nie zapisujemy znaku w tablicy
    }
    *ile = i;
    return wynik;
}



int getint( int pozycja, int tab[], int size)//funkcja do wczytywania z dynamiczej tablicy intów
{
	if(pozycja<size)
	{
		return tab[pozycja];
	}
	else exit(1);
}

void setint(int pozycja, int wartosc, int** tab, int* size)//funkcja do tworzenai dynamicznej tablicy intów
{
	if(pozycja>=*size)
	{
		(*size)= 1 + (pozycja-(*size)) + (*size) * MNOZNIK / DZIELNIK;
		 *tab = realloc(*tab, *size * sizeof(int));
    }
	(*tab)[pozycja]=wartosc;
}

char getcharr( int pozycja, char tab[], int size)//funkcja do wczytywania z dynamiczej tablicy charów
{
	if(pozycja<size)
	{
		return tab[pozycja];
	}
	else exit(1);
}

void setchar(int pozycja, char wartosc, char** tab, int* size)//funkcja do tworzenai dynamicznej tablicy charów
{
	if(pozycja>=*size)
	{
		(*size)= 1 + (pozycja-(*size)) + (*size) * MNOZNIK / DZIELNIK;
		 *tab = realloc(*tab, *size * sizeof(char));
    }
	(*tab)[pozycja]=wartosc;
}

int main()
{
	int *tab=NULL;
	char *pom=NULL;
	int *g=NULL;
	int *o=NULL;
	int *w=NULL;
	int roz=2;//rozmiar dla tablicy tab do użycia w mallocu
	int rozp=2;//rozmiar dla tablicy pom
	int rozg=2;
	int rozo=2;
	int rozw=2;
	tab = (int*) malloc(roz * sizeof(*tab));//tablica dynamicznaj do której zapisujemy to, co potem będzie outputem kompilatora
	pom = (char*) malloc(rozp * sizeof(*pom));//dynamiczna tablica pomocnicza, w której będziemy zapisywać litery (nazy procedur), 
	//do których odwołujemy się w innej procedurze, a ich adresu jeszcze nie znamy
	//tzn. jeżeli procedura Y wystepuje w kodzie po X, ale w X jest odwołanie do Y to do pom[] zapisujemy Y
	g = (int*) malloc(rozg * sizeof(*g));//tu będą zapisywane adresy, do których odwołujemy się przy instrukcji 4 (POP_BRANCH) 
	o = (int*) malloc(rozo * sizeof(*o));//tu będą zapisywane adresy, przy których będziemy wywoływać instrukcję 4 (POP_BRANCH) 
	w = (int*) malloc(rozw * sizeof(*w));//tu będą zapisywane adresy, do których odwołujemy się przy instrukcji 4 (POP_BRANCH), ale już we właściwej kolejności
	char tab_litera[26]; //w tej tablicy będizemy przechowywać literę procedury, może być maksymalnie 26 procedur
	int tab_linijka[26];// natomiast w tej - linijkę, w której procedura się zaczyna
	//(linijki będą miały te same adresy co literki)
	int licz=1;//zliczamy kolejne wiersze w outpucie kompilatora (stąd potem znamy adresy, do których mamy się odwoływać)
	int t=0;// indeks w tab[]
	int l=0;//indeks w tab_litera[] i tab_linijka[]
	int adresPG=-2;//adres procedury głównej, ustawiamy najpierw na -2, a jak już będziemy go znali, to zamienimy
	int tresc2=-1;//tresc2 to adresy procedur, do których odwołujemy się przy 7 (CALL). 
	//Ustawiamy na -1, bo można się odwoływać do procedur, których adresów jeszcze nie znamy.
	//int f= -3;
	int n=0; //indeks w g[]
	int d=0;//indeks w pom[]
	int q=0; //indeks w o[]
	int r=0;//indeks w w[]
	int poziom=0;//poziom zwiększamy gdy napotkamy '{' i zmniejszamy gdy napotkamy '}'
	int nr_stosu=0;
	bool jestem_w_procedurze = false;
	char nazwa_procedury = ' ';
	int ile;
    char *znak = czytaj(&ile);
    for (int i = 0; i <ile; i++) 
    {
		if(znak[i]=='$')
		{
			int j=i+1;
			while(znak[j]=='+' || znak[j]=='-')
			{
				if(znak[j]=='+'){setint(t, 3, &tab, &roz); t++; j++; licz++;} 
				else if(znak[j]=='-'){setint(t, 2, &tab, &roz); t++; j++; licz++;} 
			}
			if(znak[j]=='{') 
			{
				setint(t, 5, &tab, &roz); 
				setint(t+1, -4, &tab, &roz); 
                q++;
                setint(q, t+1, &o, &rozo);
				t=t+2; licz++;
			}
		}
		
		if(znak[i]>=65 && znak[i]<=90) //w ASCII to są duże litery
		{
			if(jestem_w_procedurze==false)
			{
				nazwa_procedury=znak[i];
				jestem_w_procedurze=true;
				tab_litera[l]=nazwa_procedury;
				tab_linijka[l]=licz;
				l++;
				for(int j=0; j<l; j++)
				{
					if (tab_litera[j]==znak[i]) {tab_linijka[j]=licz;}
                    //w momencie, w którym odwołujemy się do procedury, której adresu jeszcze nie znamy, wpisujemy do tab_linijka -1
                    //więc jak natrafimy na tę procedurę, to przeszukujemy tab_litera, żeby sprawdzić czy wcześiej się odwołaliśmy do tej procedury
                    //i jeśli tak, to zamieniamy -1 w tab_linijka na właściwy już adres
				}
			}
			else if (jestem_w_procedurze==true && poziom>=1)
			{
				char a=znak[i];
				for(int i=0; i<l; i++)
				{
					if(a==tab_litera[i]) {tresc2=tab_linijka[i];}
					else tresc2=-1;//wstawiamy -1 jak jeszcze nie znamy adresu procedury
				}
				if(tresc2==-1){setchar(d, a, &pom, &rozp); d++;}
				setint(t, 7, &tab, &roz); setint(t+1, tresc2, &tab, &roz); t=t+2;
				licz++;
			}
		}
			
		if(znak[i]>=97 && znak[i]<=122) // małe literki
		{
			nr_stosu = znak[i]-97;
			int j=i+1;
			while(znak[j] != '}' && (znak[j] < 97 || znak[j] > 122) && znak[j]!= '$')
			{
				if(znak[j]=='+')
                {
                    setint(t, 1, &tab, &roz); //dodajemy 1 na stos
                    setint(t+1, nr_stosu, &tab, &roz);
                    t=t+2; j++;
                    licz++;
                }
				else if(znak[j]=='-')
                {
                    setint(t, 0, &tab, &roz);//dodajemy 0 na stos
                    setint(t+1, nr_stosu, &tab, &roz);
                    t=t+2;
                    j++;
                    licz++;
                } 
				else if(znak[j]=='{')
				{
					setint(t, 4, &tab, &roz);
                    setint(t+1, -4, &tab, &roz);
                    setint(t+2, nr_stosu, &tab, &roz);
                    q++;
                    setint(q, t+1, &o, &rozo);
                    t=t+3;
					licz++;
					poziom++;
					j++;
				}
				else j++;
			}
		}
		if(ile!=0)
		{
			if((znak[i]=='{' && i==0) || (znak[i]=='{' && i != 0 && (znak[i-1] < 97 || znak[i-1] > 122)))
			{
				jestem_w_procedurze=true;
				poziom++;
				if(nazwa_procedury == ' ' && adresPG==-2) 
				{
					tab_litera[l] = '.'; //żeby odróżnić procedurę główną od reszty procedur, nazywamy ją sobie '.'
					adresPG=licz;
				}
			}
		}
		
		if(znak[i]=='}')
		{ 
			if(i!=ile-1)//żeby nie odwoływać się do znak[i+1] przy klamerce kończącej program
			{
				poziom--;
				if(((znak[i+1] == '{' && poziom==0) || ((znak[i+1]>=65 && znak[i+1]<=90)&& poziom==0)))
				{
					
					if(nazwa_procedury != ' ') 
					{
						setint(t, 8, &tab, &roz);
						t++;
						licz++;
						nazwa_procedury = ' ';
						jestem_w_procedurze=false;
					}
			
				}
				else
				{
					if(znak[i+1]=='{') 
					{
						setint(t, 6, &tab, &roz);
                        setint(t+1, -3, &tab, &roz);
                        r++;
                        setint(r, t+1, &w, &rozw);
                        t=t+2; licz++; 
                        setint(getint(q, o, rozo), licz, &tab, &roz);
                        q--;
					}
					else if(znak[i+1] != '{' && poziom != 0)
					{
						setint(getint(r, w, rozw), licz, &tab, &roz);
						r--;
					}
				}
			}
		}
	}
	 printf("6 %d\n", adresPG);		
	
	for(int i=0; i<n; i++)
	{
		printf("%d, ", getint(i, g, rozg));
	}
	
	d=0;
	for(int i=0; i<t; i++)
	{
		if(getint(i, tab, roz)==-1)
		{		
			for(int j=0; j<l; j++)
			{
				if(getcharr(d, pom, rozp)==tab_litera[j]) {setint(i, tab_linijka[j], &tab, &roz);}
			}
			d++;
		}
	}
	
	for(int i=0; i<t; i++)
	 {
		 if (getint(i, tab, roz)==7 || getint(i, tab, roz)==6 || getint(i, tab, roz)==0 || getint(i, tab, roz)==1 || getint(i, tab, roz)==5)
		 { 
			 printf("%d %d\n", getint(i, tab, roz), getint(i+1, tab, roz)); 
             i=i+1;
		 }
		 else if(getint(i, tab, roz)==4)
		 {
			 printf("%d %d %d\n", getint(i, tab, roz), getint(i+1, tab, roz), getint(i+2, tab, roz)); 
             i=i+2;
		 }
		 else printf("%d\n", getint(i, tab, roz));
	 }
	printf("9\n");
    free(tab);
    free(pom);
    free(o);
    free(g);
    free(w);
    free(znak);
return 0;
}

