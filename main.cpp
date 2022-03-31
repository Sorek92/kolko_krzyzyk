#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <cstdio>

using namespace std;

class Player{

    public:
        string imie;
        char znak;
        int pozycjaX, pozycjaY;

    Player(){

    }

    Player(string imie, char znak){
        this->imie = imie;
        this->znak = znak;
    }

    ~Player(){
        cout << "zwalnianie pamięci";
    }

};

class KolkoKrzyzyk : public Player{
    private :
        vector<vector<vector<int>>> wygranaX = {
            {
                {1,1},
                {2,2},
                {3,3}},
            {
                {3,1},
                {2,2},
                {1,3}},
            {
                {1,1},
                {1,2},
                {1,3}},
            {
                {2,1},
                {2,2},
                {2,3}},
            {
                {3,1},
                {3,2},
                {3,3}},
            {
                {1,1},
                {2,1},
                {3,1}},
            {
                {1,2},
                {2,2},
                {3,2}},
            {
                {1,3},
                {2,3},
                {3,3}},

        };

        void losuj_znak(){
            srand((unsigned)time(0));
            if(rand()%2+1 == 1){
                 this->znak1='X';
                 this->znak2='O';
             }else{
                this->znak1='O';
                this->znak2='X';
            }
        }

    public:
        int stan;
        int runda;
        vector<vector<char>> plansza;
        char znak1,znak2;
        Player *player1;
        Player *player2;
        string napis;
        int proba;

        KolkoKrzyzyk(string imie1,string imie2){
            stan = 0;
            plansza = {{'*', '*', '*'},{'*','*','*'},{'*','*','*'}};
            losuj_znak();
            proba = 0;
            player1 = new Player(imie1,this->znak1);
            player2 = new Player(imie2,this->znak2);

        }

        void czysc_plansze(){
            cout << "\x1B[2J\x1B[H";
        }

        void rysuj_plansze(){

            string tabulacja = "\t\t\t";

            string p1 = "Player1 ( ";
            p1.append(1, this->player1->znak); 
            p1 += " )"; 

            string p2 = " Player 2 ( ";
            p2.append(1,this->player2->znak);
            p2 +=" )";
            cout << p1 + tabulacja + p2 << endl;

            int odstep = p1.length()-this->player1->imie.length();

            string polaczenie(odstep,' ');
            
            cout << this->player1->imie;
            cout << polaczenie;
            
            cout << tabulacja + " " + this->player2->imie << endl;


            cout << "\t\t    x   x   x  " << endl;
            cout << "\t\t   (1) (2) (3) " << endl;

            for(int i = 0; i < this->plansza.size(); i++){
                cout << "\t\t  -------------" << endl;
                cout << "\t     y(" << i+1 << ") ";
                for(int j=0; j< this->plansza[i].size(); j++){
                    cout <<  "| " << this->plansza[i][j] << " ";
                }
                cout << "|" << endl;
            }
            cout << "\t\t  -------------" << endl;
        }

        bool sprawdz_pozycje(int x, int y){
            if(this->plansza[y-1][x-1] == '*'){
                return true;
            }else{
                return false;
            }
        }

        void aktualizuj_plansze(int x, int y, char znak){
            this -> plansza[y-1][x-1] = znak;
            this -> proba ++;
        }

        bool sprawdz_wygrana(char znak){

            vector<vector<char>> kopia;
            kopia = this->plansza;
            
            int tempx,tempy;
            int licznik = 0;
            bool zwroc = false;
            for(int i=0; i< this->wygranaX.size(); i++){
                licznik = 0;
                for(int j=0; j< this->wygranaX[i].size(); j++){
                    tempx = this->wygranaX[i][j][0];
                    tempy = this->wygranaX[i][j][1];
                    //cout << "sprawdzam x: " << tempx << " y: " << tempy << endl;
                    //cout << "pole " << kopia[tempy-1][tempx-1] << " zn : " << znak << endl;
                    if(kopia[tempx-1][tempy-1] == znak){
                        licznik++;                   
                        
                    }else{
                        //licznik--;
                        //cout << "x: " << tempx << " y: "<< tempy;
                        //cout << " znak : " << znak << endl;
                        //cout << "znak na miejscu "<< tempx-1 << ";" << tempy-1 << " : " << kopia[tempx-1][tempy-1] << endl;
                    }
                    
                }
                //cout << "----------" << endl;
                if(licznik == 3){
                    zwroc = true;
                }
            }

            return zwroc;

        }
   
};


int main(){

    
    
    string p1, p2;
    cout << "Wpisz imie pierwszego gracza : ";
    cin >> p1;
    cout << "Wpisz imie drugiego gracza : ";
    cin >> p2;

    KolkoKrzyzyk Gra(p1,p2);


    while(1){
        if(Gra.proba >= 9) Gra.stan = 6;
        switch(Gra.stan){
            case 0: {

                    Gra.czysc_plansze();
                    Gra.rysuj_plansze();

                    //zaczyna znak 'O'
                    if(Gra.player1->znak == 'O'){
                        Gra.stan = 1;
                    }else{
                        Gra.stan = 2;
                    }
                    break;
            }
            case 1: {
                    
                    cout << "Kolej playera 1 " << endl;
                    do{
                        cout << "Wpisz pozycje x: " ;
                        cin >> Gra.player1->pozycjaX;
                        cout << "Wpisz pozycje y: " ;
                        cin >> Gra.player1->pozycjaY;

                    }while(!Gra.sprawdz_pozycje(Gra.player1->pozycjaX,Gra.player1->pozycjaY));

                    Gra.aktualizuj_plansze(Gra.player1->pozycjaX,Gra.player1->pozycjaY,Gra.player1->znak);
                    Gra.czysc_plansze();
                    Gra.rysuj_plansze();
                    if(Gra.sprawdz_wygrana(Gra.player1->znak)){
                        Gra.czysc_plansze();
                        Gra.stan = 4;
                    }else{
                        Gra.stan = 2;
                    }
                   

                    break;
            }
            case 2: {
                    cout << "\t\t\t\tKolej playera 2 " << endl;
                    do{
                        cout << "\t\t\t\tWpisz pozycje x: " ;
                        cin >> Gra.player2->pozycjaX;
                        cout << "\t\t\t\tWpisz pozycje y: " ;
                        cin >> Gra.player2->pozycjaY;

                    }while(!Gra.sprawdz_pozycje(Gra.player2->pozycjaX,Gra.player2->pozycjaY));

                    Gra.aktualizuj_plansze(Gra.player2->pozycjaX,Gra.player2->pozycjaY,Gra.player2->znak);
                    Gra.czysc_plansze();
                    Gra.rysuj_plansze();

                    if(Gra.sprawdz_wygrana(Gra.player2->znak)){
                        Gra.czysc_plansze();
                        Gra.stan = 5;
                    }else{
                        Gra.stan = 1;
                    }

                    

                    break;
            }
            case 3: cout << "wpisanie pola" << endl;
                    break;
            case 4: 
                // wyswietl plansze
                Gra.rysuj_plansze();
                    cout << "wygrał gracz nr 1"<< endl;
                    exit(0);
                    break;
            case 5: Gra.rysuj_plansze();
                    cout << "wygrał gracz nr 2"<< endl;
                    exit(0);
                    break;
            case 6: Gra.rysuj_plansze();
                    cout << "remis" << endl;
                    exit(0);
                    break;

        }
    }



    return 0;
}


