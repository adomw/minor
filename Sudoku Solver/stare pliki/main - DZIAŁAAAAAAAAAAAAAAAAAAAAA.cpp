#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string>
#include<stack>

//wspolrzedne planszy sa 0..8 x 0..8
//ale juz odnoszenie sie do cyfr w samych kratkach jest 1..9

const bool Zasada[] = {  //tablica decydujaca o tym, ktore zasady beda brane pod uwage (trzy pierwsze zasady to klasyczne zasady sudoku, ale sa tez zagadki bedace rozwinieciem klasycznych)
                      1, // wiersze
                      1, // kolumny
                      1, // kwadraty 3x3
                      0  // dummy, ¿eby nie trzeba by³o przecinków naprawiaæ powy¿ej przy ka¿dej zmianie
                      };

char line(int x, int y){ //funkcja zwracajaca znak ascii do "budowy" planszy przy wyswietlaniu
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

struct Coords{ //struktura zawierajaca dwa parametry
    int x, y;
};

class Kratka{
private:
    bool Possible[10];
    int NumberOfPossible;
    int C; // 0 - puste, 1-9: cyfra, ktora tam sie znajduje
public:
    bool empty(){ //return true jesi 0
        if(C == 0) return true;
        else return false;
    }
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
    void reset(){//wlasciwy reset planszy
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                kratka[i][j].reset();
        Possible = true;
    }
    void reset1(){//testowy reset z dodatkowymi paramentrami
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
    void reset2(){//testowy reset 2
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
    void calculatePossiblities(){//dla kazdej kratki policz i ustaw mozliwosci zgodnie z zasadami sudoku
        if(Zasada[0]){//sprawdzenie wierszy
            for(int j = 0; j < 9; j++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[n][j].value();
                    if(k != 0)
                        for(int i = 0; i < 9; i++)
                            kratka[i][j].setPossible(k, false);
                    n++;
                }
            }
            //for(int i = 1; i <= 9; i++) printf("%d,", (int)kratka[4][3].possible(i));
        }
        if(Zasada[1]){//sprawdzenie kolumn
            for(int i = 0; i < 9; i++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[i][n].value();
                    if(k != 0)
                        for(int j = 0; j < 9; j++)
                            kratka[i][j].setPossible(k, false);
                    n++;
                }
            }
        }
        if(Zasada[2]){//sprawdzenie kolumn
            for(int i3 = 0; i3 < 3; i3++) for(int j3 = 0; j3 < 3; j3++)//ta sama procedura dla kazdego kwadratu po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = kratka[i3 * 3 + n % 3][j3 * 3 + n / 3].value();
                    if(k != 0)
                        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
                            kratka[i3 * 3 + i][j3 * 3 + j].setPossible(k, false);
                    n++;
                }
            }
            //for(int i = 1; i <= 9; i++) printf("%d,", (int)kratka[4][3].possible(i));
        }
    }
    void definePossible(bool b){//zdefiniuj czy plansza jest mozliwa do osiagniecia czy nie
        Possible = b;
    }
    void checkIfPossible(){
        if(Possible == false) return;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(kratka[i][j].numberOfPossible() == 0)
                {
                    Possible = false;
                    return;
                }
    }
    bool possible(){ //zwroc wartosc parametru Possible - czy ta plansza jest mozliwa czy tez nie
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
                    kratka[i - 1][j - 1].setValue(c - 48);//printf("%d",kratka[i-1][j-1].value());
            }
            //printf("\n");
        }
        Possible = true;
    }
    Coords nextTarget(){// policz i zwroc wspolrzedne kratki w ktorej jest NAJMNIEJ mozliwych cyfr do wstawienia
        Coords K;
        K.x = 10;
        K.y = 10;
        //znajdujemy na razie JEDNA kratke, ktora nie jest wypelniona. dowolna.
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                if(kratka[i][j].value() == 0){
                    K.x = i;
                    K.y = j;
                    break;
                }
            if(K.x != 10)
                break;
        }
        //printf("%d_%d\n", K.x, K.y);
        if(K.x == 10) return K;//to oznacza, że wszystkie pola sa uzupelnione i mozna zwrocic ten fakt jako wynik

        //a jezeli nie sa wszystkie pola uzupelnione, to wowczas sprawdzamy w ktorym miejscu jest najmniej mozliwosci

        for(int i = 0; i < 9; i++) //if gdziekolwiek numberofpossible == 0, to tez od razu return mozna zrobic, bo brak mozliwosci
        {
            for(int j = 0; j < 9; j++)
            {
                if((kratka[i][j].value() == 0) && (kratka[i][j].numberOfPossible() < kratka[K.x][K.y].numberOfPossible()))//jesli kratka jest pusta i jest w niej mniej mozliwosci niz w poprzednio uwazanej za "najmniejsza" pod tym wzgledem
                {
                    K.x = i;
                    K.y = j;
                }
                if(kratka[K.x][K.y].numberOfPossible() == 0)
                {
                    Possible = false;
                    break;
                }
            }
            if(Possible == false)
                break;
        }
        return K;//powinno byc dobrze
    }
    int totalPossibilities(){ //suma mozliwosci we wszystkich kratkach. W pustej planszy wynosi 9x9 (kratek) * 9 (mozliwych cyfr w jednej kratce) = 729
        int n = 0;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(kratka[i][j].value() == 0)
                    n += kratka[i][j].numberOfPossible();
        return n;
    }
    void setPossible(int x, int y, int n, bool b){
        kratka[x][y].setPossible(n, b);
    }
    void setValue(int x, int y, int n){
        kratka[x][y].setValue(n);
    }
    void fillOnes(){//wypelnij
        Coords K = nextTarget();
        do{
            if(kratka[K.x][K.y].numberOfPossible() == 1)
                for(int i = 1; i <= 9; i++)
                    if(kratka[K.x][K.y].possible(i)){
                        kratka[K.x][K.y].setValue(i);
                        calculatePossiblities();
                        break;
                    }
            K = nextTarget();
        }while((kratka[K.x][K.y].numberOfPossible() == 1) && kratka[K.x][K.y].empty());//naprawione - wczesniej sie zapetlalo bo jak jest wypelniona kratka to numberofpossible zwraca 1
    }
    int totalEmpty(){ //suma mozliwosci we wszystkich kratkach. W pustej planszy wynosi 9x9 (kratek) * 9 (mozliwych cyfr w jednej kratce) = 729
        int n = 0;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(kratka[i][j].empty())
                    n++;
        return n;
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
        Coords K = nextTarget();
        printf("%d, %d\n", K.x + 1, K.y + 1);
    }
    bool solveStare(){
        calculatePossiblities();
        checkIfPossible();//sprawdza czy WARTOSC ZMIENNEJ Possible jest prawdziwa, a nie czy sudoku jest mozliwe
        if(!Possible)
            return false;
            //printf("Sudoku zawiera bledy\n");
        else{
            fillOnes();
            Coords c = nextTarget();
            for(int m = 1; m < 10; m++)
            if(kratka[c.x][c.y].possible(m))//jezeli w nastepnej rozpatrywanej kratce mozliwe jest m
            {//utworzenie dokladnej kopii
                Plansza P;
                for(int i = 0; i < 9; i++)
                    for(int j = 0; j < 9; j++)
                        for(int k = 0; k < 10; k++)
                        {
                            P.setValue(i, j, k);
                            P.setPossible(i, j, k, kratka[i][j].possible(k));
                        }
                //P.setPossible(c.x, c.y, m, false);//zalozmy, ze ODEJMUJEMY jeden wariant
                //ale lepiej bedzie zrobic inaczej! lepiej bedzie zalozyc ze NADAJEMY TE WARTOSC!
                P.setValue(c.x, c.y, m);
                bool b;
                b = P.solve();
                if(!b)//jesi rozwiazanie wyszlo niemozliwe
                    kratka[c.x][c.y].setPossible(m, false);
                //else
            }//koniec dokladnej kopii (jednej)
            return true;
        }
    }
    void setKratka(int x, int y, Kratka k){
        kratka[x][y] = k;
    }
    bool solve(){
        do{
                print();//printf("assert 1\n");
                system("pause");
            calculatePossiblities();//printf("assert 2\n");
            checkIfPossible();//printf("assert 3\n");
            if(!Possible)
                return false;//printf("assert 4\n");

            int sp;
            do{
                sp = totalEmpty();//printf("assert 5\n");
                fillOnes();//printf("assert 6\n");
                calculatePossiblities();//printf("assert 7\n");
            }while(sp != totalEmpty());//printf("assert 8\n");

            if(totalEmpty() == 0)
                return true;

            checkIfPossible();//printf("assert 9\n");
            if(!Possible)
                return false;//printf("assert 10\n");

            Coords c = nextTarget();//printf("assert 11\n");

            for(int i = 1; i < 10; i++)
                if(kratka[c.x][c.y].possible(i)){//printf("assert 12\n");
                    Plansza P;
                    P.reset();
                    for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                        {//printf("assert 13\n");
                            P.setValue(i, j, kratka[i][j].value());//printf("assert 14\n");
                            for(int k = 1; k < 10; k++)
                                P.setPossible(i, j, k, kratka[i][j].possible(k));//printf("assert 15\n");
                        }//printf("assert 16\n");
                    P.setValue(c.x, c.y, i);//printf("assert 17\n");
                    bool b = P.solve();//printf("assert 18\n");
                    if(b == false)
                    {
                        kratka[c.x][c.y].setPossible(i, false);//printf("assert 19\n");
                        break;
                    }//printf("assert 20\n");
                }//printf("assert 21\n");

        }while(totalEmpty() > 0);//printf("assert 22\n");
        /*
        calculatePossiblities();
        checkIfPossible();//sprawdza czy WARTOSC ZMIENNEJ Possible jest prawdziwa, a nie czy sudoku jest mozliwe
        if(!Possible)
            {return false;
            printf("Sudoku zawiera bledy\n");}
        else{
            fillOnes();
            Coords c = nextTarget();
            for(int m = 1; m < 10; m++)
            if(kratka[c.x][c.y].possible(m))//jezeli w nastepnej rozpatrywanej kratce mozliwe jest m
            {//utworzenie dokladnej kopii, przepisanie zawartosci obecnej planszy do nowej
                Plansza P;
                P.reset();
                for(int i = 0; i < 9; i++)
                    for(int j = 0; j < 9; j++)
                    {
                        P.setValue(i, j, kratka[i][j].value());
                        for(int k = 1; k < 10; k++)
                            P.setPossible(i, j, k, kratka[i][j].possible(k));
                    }
                //P.setPossible(c.x, c.y, m, false);//zalozmy, ze ODEJMUJEMY jeden wariant
                //ale lepiej bedzie zrobic inaczej! lepiej bedzie zalozyc ze NADAJEMY TE WARTOSC!
                P.setValue(c.x, c.y, m);
                bool b;
                b = P.solve();
                if(!b)//jesi rozwiazanie wyszlo niemozliwe
                    kratka[c.x][c.y].setPossible(m, false);
                //else
            }//koniec dokladnej kopii (jednej)
            return true;*/


    }
};

int main(){
    srand(time(NULL));
    Plansza plansza;

    std::string input[] = {
                 "    6  58",
                 " 52  9 74",
                 " 78      ",
                 " 3 49 58 ",
                 "  5   4 7",
                 " 67 83  2",
                 " 2 93 865",
                 "  9  8  3",
                 "38  45 91"
    };
    std::string input2[] = {
                 "913  7   ",
                 " 87  53 2",
                 "   6  1  "
                 "  2  87 4",
                 "        5",
                 "   76   9",
                 "  5   92 ",
                 "726   8  ",
                 "   2  4  "
    };
    std::string input3[] = { //bardzo trudne
                 "5    2   ",
                 "      39 ",
                 "2 84 6   ",
                 " 9 53    ",
                 " 65     8",
                 " 8    9 3",
                 "6 4   7  ",
                 "      21 ",
                 "   274   "
    };
    std::string input4[] = { //bardzo latwe
                 "  57     ",
                 "1 4365872",
                 "  38   4 ",
                 " 1  8 5  ",
                 " 8 61 4 7",
                 " 4    2  ",
                 "26    7  ",
                 "   5761 9",
                 "7 1  96 3"
    };
    std::string input5[] = { //bardzo trudne
                 "    7 4  ",
                 "673      ",
                 "   39 5  ",
                 "3 2     8",
                 "  7 1   9",
                 "   5 2   ",
                 "   258 3 ",
                 "     7 4 ",
                 "86       "
    };

    plansza.read(input5);
    //printf("%d", plansza.totalEmpty());

    if(plansza.solve()){
        plansza.print();
        printf("Kunc\n");
    }
    else
        printf("Sudoku zawiera bledy.\n");



    /*std::stack<Plansza> stosPlansz;
    stosPlansz.push(plansza);
    //stosPlansz.top().
    printf("%d\n", stosPlansz.top().totalPossibilities());*/
    return 0;
}
