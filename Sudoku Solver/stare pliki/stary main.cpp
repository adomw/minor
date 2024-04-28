#include<stdio.h>
#include<time.h>
#include<stdlib.h>

const bool Zasada[] = {
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
    int C; // 0 - puste
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
    void calculatePossible(){
        if(Zasada[0]){

        }
    }
    bool possible(){
        return Possible;
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

    }
};

int main(){
    srand(time(NULL));
    Plansza plansza;
    plansza.reset1();
    plansza.print();
    return 0;
}
