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
        // wygrane pola 
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
        // pola planszy gry
        vector<vector<char>> plansza = {{'*', '*', '*'},{'*','*','*'},{'*','*','*'}};
        // losowanie znaku dla graczy
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
        char znak1,znak2;
        Player *player1;
        Player *player2;
        Player *player; // aktywny gracz
        string napis;
        int proba;
        

        KolkoKrzyzyk(string imie1,string imie2){
            //stan = 0;
            losuj_znak();
            this -> proba = 0;
            player1 = new Player(imie1,this->znak1);
            player2 = new Player(imie2,this->znak2);
            // cout << this->player1->imie <<"adresy : x-"<< &this->player1->pozycjaX << " y-"<< &this->player1->pozycjaY <<
            //         " i-" << &this->player1->imie << endl;
            //         getchar();
            // cout << this->player2->imie <<"adresy : x-"<< &this->player2->pozycjaX << " y-"<< &this->player2->pozycjaY <<
            //         " i-" << &this->player2->imie << endl;
            //         getchar();

        }

        void init(){
            this -> czysc_ekran();
            this -> rysuj_plansze();

            //zaczyna znak 'O'
            if(this -> player1->znak == 'O'){
                player = player1;

            }else{
                player = player2;
            }
            //cout << this->player->imie <<"adresy : x-"<< &this->player->pozycjaX << " y-"<< &this->player->pozycjaY <<
            //       " i-" << &this->player->imie << endl;
            //        getchar();
        }

        void play(){
            wpisz_pozycje();
        }

        void wpisz_pozycje(){
            
            cout << "Kolej gracza: " << this->player->imie << endl;
            int x,y;
            do{
                cout << "Wpisz pozycje x: " ;
                cin >> x;
                cout << "Wpisz pozycje y: " ;
                cin >> y;
                // sprawdz czy napewno wpisane sa dobre współrzedne 
                if((x>=0 || x<=3) && (y>=0 || y<=3)){
                    this->player->pozycjaX = x;
                    this->player->pozycjaY = y;
                    
                }
                else{
                    cout << "Błąd -> x:" << x << " y:" << y << endl;
                    continue;
                }

            }while(!this->sprawdz_pozycje());
            this->czysc_ekran();
            this->rysuj_plansze();
            this->zmien_playera();
            this->play();
        }

        void zmien_playera(){
            if(player == player1){
                player = player2;
            }else{
                player = player1;
            }
        }

        // czysc ekran konsoli
        void czysc_ekran(){
            cout << "\x1B[2J\x1B[H";
        }

        // rysuj plansze gry
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

        // sprawdzanie pozycji w planszy czy zajeta
        bool sprawdz_pozycje(){
            
            if(this->plansza[this->player->pozycjaY-1][this->player->pozycjaX-1] == '*'){
                this->aktualizuj_plansze();
                return true;
            }else{
                return false;
            }

            
        }

        // aktualizacja planszy - wpisanie znaku 
        void aktualizuj_plansze(){
            this -> plansza[this->player->pozycjaY-1][this->player->pozycjaX-1] = this->player->znak;
            this -> czysc_ekran();
            this -> rysuj_plansze();
            //cout << "sprawdzam wygraną ..." << endl;
            if(this -> sprawdz_wygrana()){
                wyswietl_wygrana();
            }else{
                //cout << "kolejna próba" << endl;
                this -> proba ++;
                this -> zmien_playera();
                this -> play();
            }
            
        }

        // sprawdzenie czy ktos juz wygrał
        bool sprawdz_wygrana(){
            znak = this->player->znak;
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


        void wyswietl_wygrana(){
            this->czysc_ekran();
            this->rysuj_plansze();
            cout << "Wygrał gracz: " << this->player->imie << " o znaku :" << this->player->znak << endl;
            exit(0);
        }

        ~KolkoKrzyzyk(){
            cout << "zwalnianie pamieci";
        }

};


int main(){

    
    
    string p1, p2;
    cout << "Wpisz imie pierwszego gracza : ";
    cin >> p1;
    cout << "Wpisz imie drugiego gracza : ";
    cin >> p2;

    KolkoKrzyzyk Gra(p1,p2);

    Gra.init();

    while(1){
        Gra.play();
    }
    
    return 0;
}


