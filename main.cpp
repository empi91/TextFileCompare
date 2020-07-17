// GCC version 4.9.2
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool sprawdz_plik (fstream & plik, string nazwa);
void wypisz_pliki (char * p1, char * p2, long dlugosc1, long dlugosc2);
void wypisz_pliki_rozne (char * p1, char * p2, long dlugosc1, long dlugosc2);
bool porownaj_dlugosc (long dlugosc1, long dlugosc2);
void porownaj (char * p1, char * p2,int * t1, char * roznica, long dlugosc);
bool warunek(char * p1, int i);



int main()
{
    string nazwa1, nazwa2;

    cout << "Podaj nazwe pierwszego pliku (wraz z rozszerzeniem)" << endl;
    cin >> nazwa1;
    cout << "Podaj nazwe drugiego pliku (wraz z rozszerzeniem)" << endl;
    cin >> nazwa2;

    fstream plik1;
    plik1.open( nazwa1.c_str(), ios::in | ios::binary );
    fstream plik2;
    plik2.open( nazwa2.c_str(), ios::in | ios::binary );

    sprawdz_plik(plik1, nazwa1);
    sprawdz_plik(plik2, nazwa2);

    plik1.seekg( 0, ios::end );
    long dlugosc1 = plik1.tellg();
    plik1.seekg( 0, ios::beg );

    plik2.seekg( 0, ios::end );
    long dlugosc2 = plik2.tellg();
    plik2.seekg( 0, ios::beg );

    char * p1 = new char[ dlugosc1 ];
    char * p2 = new char[ dlugosc2 ];
    char * roznica = new char[ dlugosc1 ];
    int * t1 = new int [dlugosc1];
    plik1.read( p1, dlugosc1 );
    plik2.read( p2, dlugosc2 );

    if (!porownaj_dlugosc(dlugosc1, dlugosc2))
    {
        wypisz_pliki(p1, p2, dlugosc1,dlugosc2);
        porownaj(p1,p2,t1,roznica,dlugosc1);
    } else if (dlugosc1 > dlugosc2)
    {
        int n = dlugosc1 - dlugosc2;
        wypisz_pliki_rozne(p1, p2, dlugosc1,dlugosc2);
        cout << "Plik " << nazwa1 << " jest dluzszy o " << dec << n << endl;
    } else if (dlugosc1 < dlugosc2)
    {
        int n = dlugosc2 - dlugosc1;
        wypisz_pliki_rozne(p1, p2, dlugosc1,dlugosc2);
        cout << "Plik " << nazwa2 << " jest dluzszy o " << dec << n << endl;
    }

    plik1.close();
    plik2.close();
    delete [] p1;
    delete [] p2;
    delete [] roznica;
    delete [] t1;
    return 0;
}
bool sprawdz_plik (fstream & plik, string nazwa)
{
    if (!plik)
    {
        cout << "Plik " << nazwa << " nie zostal prawidlowo otwarty" << endl;
        return 1;
    }
    return 0;
}
void wypisz_pliki (char * p1, char * p2, long dlugosc1, long dlugosc2)
{

    for( int i = 0; i < dlugosc1; i++ )
    {
        if ((warunek(p1,i)) && (warunek(p2,i)))
        {
        cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
        cout << "Niedrukowalny znak" << "  |  ";
        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
        cout << "Niedrukowalny znak" << endl;
        } else if (warunek(p2,i))
        {
        cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
        cout << p1[ i ] << "  |  ";
        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
        cout << "Niedrukowalny znak" << endl;
        } else if (warunek(p1,i))
        {
        cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
        cout << "Niedrukowalny znak" << "  |  ";
        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
        cout << p2[i] << endl;
        } else
        {
        cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
        cout << p1[ i ] << "  |  ";
        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
        cout << p2[ i ] << endl;
        }

    }
    cout << "-------------------------" << endl;
}
void wypisz_pliki_rozne (char * p1, char * p2, long dlugosc1, long dlugosc2)
{
    if (dlugosc1 > dlugosc2)
        {
            int n = dlugosc1 - dlugosc2;

            for( int i = 0; i < dlugosc1; i++ )
            {
                if ( i > (dlugosc1 - n) )
                {
                    if (warunek(p1,i))
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << "  |  ";
                        cout << "Brak danych, plik krotszy" << endl;
                        } else
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << p1[ i ] << "  |  ";
                        cout << "Brak danych, plik krotszy" << endl;
                        }
                } else
                {
                    if ( i == (dlugosc1 - n))
                    {
                        if (warunek(p1,i))
                            {
                            cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << "Niedrukowalny znak" << "  |  ";
                            cout << "Brak danych, plik krotszy" << endl;
                            } else
                            {
                            cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << p1[ i ] << "  |  ";
                            cout << "Brak danych, plik krotszy" << endl;
                            }
                    } else
                    {
                        if (warunek(p1,i) && warunek(p2,i))
                        {
                            cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << "Niedrukowalny znak" << "  |  ";
                            cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                            cout << "Niedrukowalny znak" << endl;
                        } else if (warunek(p2,i))
                        {
                            cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << p1[ i ] << "  |  ";
                            cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                            cout << "Niedrukowalny znak" << endl;
                        } else if (warunek(p1,i))
                        {
                            cout << setw(4) << dec << i+1 << ": " << setw(2) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << "Niedrukowalny znak" << "  |  ";
                            cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                            cout << p2[i] << endl;
                        } else
                        {
                            cout << setw(4) << dec << i+1 << ": " << setw(19) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                            cout << p1[i] << "  |  ";
                            cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                            cout << p2[i] << endl;
                        }
                    }
                }
            }
        } else
        {
            int n = dlugosc2 - dlugosc1;

            for( int i = 0; i < dlugosc2; i++ )
            {
                if ( i > (dlugosc2 - n) )
                {
                    if (warunek(p2,i))
                    {
                        cout << setw(4) << dec << i+1 << ": " << "Brak danych, plik krotszy " << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << endl;
                    } else
                    {
                        cout << setw(4) << dec << i+1 << ": " << "Brak danych, plik krotszy " << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << p2[ i ] << endl;
                    }
                } else
                {
                    if ( i == (dlugosc2 - n))
                    {
                        if (warunek(p2,i))
                        {
                        cout << setw(4) << dec << i+1 << ": " << "Brak danych, plik krotszy " << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << endl;
                        } else
                        {
                        cout << setw(4) << dec << i+1 << ": " << "Brak danych, plik krotszy " << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << p2[ i ] << endl;
                        }
                    } else
                    {
                        if (warunek(p1,i) && warunek(p2,i))
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(4) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << endl;
                        } else if (warunek(p2,i))
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(21) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << p1[ i ] << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << endl;
                        } else if (warunek(p1,i))
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(4) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << "Niedrukowalny znak" << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << p2[i] << endl;
                        } else
                        {
                        cout << setw(4) << dec << i+1 << ": " << setw(21) << hex <<( int )( unsigned char ) p1[ i ] << " -> ";
                        cout << p1[ i ] << "  |  ";
                        cout << hex <<( int )( unsigned char ) p2[ i ] << " -> ";
                        cout << p2[ i ] << endl;
                        }
                    }
                }
            }
        }

    cout << "-------------------------" << endl;
}
bool porownaj_dlugosc (long dlugosc1, long dlugosc2)
{
    if (dlugosc1 == dlugosc2) return 0;
    else return 1;
}
void porownaj (char * p1, char * p2,int * t1, char * roznica, long dlugosc)
{
    int licznik = 0;
    int ilosc = dlugosc / 50;
    int iloscII = dlugosc % 50;
    int p = 0;
    for (int i = 0; i < ilosc; i++)
    {
        for (int j = 0; j + p < p + 50; j++)
        {
            if (p1[j+p] == p2[j+p])
            {
                continue;
            } else
            {
                roznica[licznik] = p2[j+p];
                t1[licznik] = (j+p);
                licznik++;

            }
        }
        p = p + 50;
    }
    for (int i = 0; i < iloscII; i++)
    {
            if (p1[i+(ilosc*50)] == p2[i+(ilosc*50)])
            {
                continue;
            } else
            {
                roznica[licznik] = p2[i+(ilosc*50)];
                t1[licznik] = i+(ilosc*50);
                licznik++;
            }
    }
    if (licznik == 0) cout << "Pliki sa takie same" << endl;
    for (int j = 0; j < licznik; j++)
    {
        int d = t1[j];
        cout << "Bajt " << setw(4) << dec << d+1 << ": " << hex << p1[d] << " -> " << roznica[j] << endl;
    }
}
bool warunek(char * p1, int i)
{
    if (p1[i] == 0x00 | p1[i] == 0x01 | p1[i] == 0x02 | p1[i] == 0x03 | p1[i] == 0x04 | p1[i] == 0x05 | p1[i] == 0x06 | p1[i] == 0x07 | p1[i] == 0x08 | p1[i] == 0x09) return 1;
    if (p1[i] == 0x0A | p1[i] == 0x0B | p1[i] == 0x0C | p1[i] == 0x0D | p1[i] == 0x0E | p1[i] == 0x0F | p1[i] == 0x1A | p1[i] == 0x1B | p1[i] == 0x1C | p1[i] == 0x1D | p1[i] == 0x1E | p1[i] == 0x1F) return 1;
    if (p1[i] == 0x10 | p1[i] == 0x11 | p1[i] == 0x12 | p1[i] == 0x13 | p1[i] == 0x14 | p1[i] == 0x15 | p1[i] == 0x16 | p1[i] == 0x17 | p1[i] == 0x18 | p1[i] == 0x19) return 1;

    return 0;
}
