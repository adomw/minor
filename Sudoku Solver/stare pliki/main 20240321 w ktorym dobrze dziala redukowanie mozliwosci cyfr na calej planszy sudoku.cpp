#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string>

const bool Zasada[] = {  //tablica decydujaca o tym, ktore zasady beda brane pod uwage (trzy pierwsze zasady to klasyczne zasady sudoku, ale sa tez zagadki bedace rozwinieciem klasycznych)
                      1, // wiersze
                      1, // kolumny
                      1, // kwadraty 3x3
                      0  // dummy, ¿eby nie trzeba by³o przecinków naprawiaæ powy¿ej przy ka¿dej zmianie
                      };

char line(int x, int y){
    if((x == 0) || (y == 0) || (x == 72) || (y == 36)){
        if((x == 0) && (y == 0)) return (char)201;
        if((x == 0) && (y == 36)) return (char)200;
        if((x == 72) && (y == 0)) return (char)187;
        if((x == 72) && (y == 36)) return (char)188;
        if((x == 0) && (y % 4 == 0)) return (char)204;
        //if((x == 0) && (y % 12 == 0)) return (char)199;
        if((x == 72) && (y % 4 == 0)) return (char)185;
        if((y == 0) && (x % 8 == 0)) return (char)203;
        if((y == 36) && (x % 8 == 0)) return (char)202;
        if(y % 36 == 0) return (char)205;
        return (char)186;
    }

    if(x % 8 == 0){
        //if(y % 12 == 0) return (char)206;
        //if(y % 4 == 0) return (char)197;
        //if(y % 4 == 0) return (char)206;
        if(x % 24 == 0){
                if (y % 4 == 0) return (char)206;
                else return (char)186;
        }
        if(y % 12 == 0) return (char)206;
        if(y % 4 == 0) return (char)197;
        return (char)179;
    }

    if(y % 4 == 0)
        if(y % 12 == 0) return (char)205;
        else return (char)196;

    char c = 'x';
    if(y % 4 == 0){
        if(y % 12 == 0)
            if(x == 0) c = 'a';
            else c = '=';
        else c = '-';
    }
    else{
        if(x % 8 == 0) c = '|';
    }
    return c;
}

class Kratka{
private:
    bool Possible[10];
    int NumberOfPossible;
    int C; // 0 - puste, 1-9: cyfra, ktora tam sie znajduje
public:
    void reset(){
        for(int i = 1; i < 10; i++)
            Possible[i] = true;
        C = 0;
    }
    bool possible(int n){
        return Possible[n];
    }
    void setPossible(int n, bool b){
        Possible[n] = b;
    }
    int value(){
        return C;
    }
    void setValue(int n){
        C = n;
    }
    void calculatePossible(){
        int n = 0;
        if(C) n = 1;
        else for(int i = 1; i < 10; i++)
            if(Possible[i]) n++;
        NumberOfPossible = n;
    }
    int numberOfPossible(){
        calculatePossible();
        return NumberOfPossible;
    }
};

class Plansza{
private:
    Kratka kratka[9][9];
    bool Possible;
public:
    void reset(){
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                kratka[i][j].reset();
        Possible = true;
    }
    void reset1(){
        int r;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++){
                r = rand();
                if(r % 2)
                    kratka[i][j].reset();
                else
                    kratka[i][j].setValue(r % 9);
            }
        Possible = true;
    }
    void reset2(){
        int r;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++){
                r = rand();
                if(r % 2)
                    kratka[i][j].reset();
                else
                    kratka[i][j].setValue(r % 9 + 1);
            }
        Possible = true;
    }
    void calculatePossiblities(){
        if(Zasada[0]){//sprawdzenie wierszy
            for(int j = 0; j < 9; j++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[n][j].value();printf("%d", k);
                    if(k != 0)
                        for(int i = 0; i < 9; i++)
                            kratka[i][j].setPossible(k, false);
                    n++;
                }printf("\n");
            }
            //for(int i = 1; i <= 9; i++) printf("%d,", (int)kratka[4][3].possible(i));
        }
        if(Zasada[1]){//sprawdzenie kolumn
            for(int i = 0; i < 9; i++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[i][n].value();printf("%d", k);
                    if(k != 0)
                        for(int j = 0; j < 9; j++)
                            kratka[i][j].setPossible(k, false);
                    n++;
                }printf("\n");
            }
        }
        if(Zasada[2]){//sprawdzenie kolumn
            for(int i3 = 0; i3 < 3; i3++) for(int j3 = 0; j3 < 3; j3++)//ta sama procedura dla kazdego kwadratu po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[i3 * 3 + n % 3][j3 * 3 + n / 3].value();printf("%d", k);
                    if(k != 0)
                        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
                            kratka[i3 * 3 + i][j3 * 3 + j].setPossible(k, false);
                    n++;
                }printf("\n");
            }
            //for(int i = 1; i <= 9; i++) printf("%d,", (int)kratka[4][3].possible(i));
        }
    }
    bool possible(){
        return Possible;
    }
    void read(std::string input[]){ //wczytaj sudoku ze stringa
        for(int j = 1; j <= 9; j++)
        {
            std::string s = input[j - 1];
            for(int i = 1; i <= 9; i++)
            {
                char c = s[i - 1];
                kratka[i - 1][j - 1].reset();
                if(!(c == ' '))
                    kratka[i - 1][j - 1].setValue(c - 48);
            }
            printf("\n");
        }

    }
    void print(){/*
        printf("%c", 218); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 194); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 194); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 191);
        printf("%c", 195); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 180);
        printf("%c", 195); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 180);
        printf("%c", 192); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 193); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 193); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 217);

        printf("%c", 201); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 194); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 194); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 191);
        printf("%c", 195); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 180);
        printf("%c", 195); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 197); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 180);
        printf("%c", 200); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c", 193); printf("%c%c%c%c%c", 196, 196, 196); printf("%c", 193); printf("%c%c%c%c%c", 196, 196, 196, 196, 196); printf("%c\n", 217);




        printf("%c", 218); printf("%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196); printf("%c\n", 191);
        printf("%c", 179); printf(" 1 2 3 "); printf("%c\n", 179);
        printf("%c", 179); printf(" 4 5 6 "); printf("%c\n", 179);
        printf("%c", 179); printf(" 7 8 9 "); printf("%c\n", 179);
        printf("%c", 192); printf("%c%c%c%c%c%c%c", 196, 196, 196, 196, 196, 196, 196); printf("%c\n", 217);

*/

        /*for(int j = 0; j < 37; j++){
            for(int i = 0; i < 73; i++){
                if(line(i, j) == 'x') printf("0");
                else printf("%c", line(i, j));
            }
            printf("\n");
        }*/

        int x, y, k;

        for(int j = 0; j < 37; j++){
            y = (j - 1) / 4;
            for(int i = 0; i < 73; i++){
                if(line(i, j) == 'x'){
                    x = (i - 2) / 8;
                    if(kratka[x][y].value() == 0){
                        k = ((i - 2) % 8) / 2 + 3 * ((j - 1) % 4) + 1;
                        if(i % 2 == 0)
                            if(kratka[x][y].possible(k)) printf("%d", k);
                            else printf(" ");
                        else printf(" ");
                    }
                    else{
                        //179, 196
                        if(i % 8 == 4)
                            if(j % 4 == 2) printf("%d", kratka[x][y].value());
                            else printf("%c", 196);
                        //else if((j % 4 == 2) && ((i % 8 == 3)  || (i % 8 == 5))) printf("%c", 179);
                        else printf(" ");
                    }
                }
                else printf("%c", line(i, j));
            }
            printf("\n");
        }
        //printf("%d", kratka[8][8].numberOfPossible());
        printf("%d", kratka[6][6].value());
    }
};

int main(){
    srand(time(NULL));
    Plansza plansza;
    //plansza.reset2();
    std::string input[] = {
                 "1 6  3 9 ",
                 "23456789 ",
                 "3 8 9 54 ",
                 "17  4 31 ",
                 "     6 2 ",
                 "      6  ",
                 "5       4",
                 "294 3   5",
                 "1 6666444"
    };
    plansza.read(input);

    plansza.calculatePossiblities();

    plansza.print();
    return 0;
}
