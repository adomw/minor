#include<cstdio>
#include<fstream>
#include<string>

//boards coords are 0..8 x 0..8
//field values are 1..9 and 0 means empty

const bool Rule[] = {  //array which determines which rules are to be taken into account; the first 3 are classical sudoku rules
                      1, // rows
                      1, // columns
                      1, // 3x3 squares
                      0  // dummy, in case more rules are added (i.e. killer sudoku rules)
                      };

char line(int x, int y){//function which returns the ascii character needed to construct the board's visual representation
    if((x == 0) || (y == 0) || (x == 72) || (y == 36)){
        if((x == 0) && (y == 0)) return (char)201;
        if((x == 0) && (y == 36)) return (char)200;
        if((x == 72) && (y == 0)) return (char)187;
        if((x == 72) && (y == 36)) return (char)188;
        if((x == 0) && (y % 4 == 0)) return (char)204;
        if((x == 72) && (y % 4 == 0)) return (char)185;
        if((y == 0) && (x % 8 == 0)) return (char)203;
        if((y == 36) && (x % 8 == 0)) return (char)202;
        if(y % 36 == 0) return (char)205;
        return (char)186;
    }

    if(x % 8 == 0){
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

struct Coords{//simple coords structure
    int x, y;
};

class Field{
private:
    bool Possible[10];
    int NumberOfPossible;
    int C; // velue of the field; 0 - empty, 1-9: digit inside
public:
    bool empty(){//return true if C is 0
        if(C == 0) return true;
        else return false;
    }
    void reset(){//reset the field - empty and all digits possible
        for(int i = 1; i < 10; i++)
            Possible[i] = true;
        C = 0;
    }
    bool possible(int n){//return whether the digit n is possible in this field
        return Possible[n];
    }
    void setPossible(int n, bool b){//define whether this field is technically possible
        Possible[n] = b;
    }
    int value(){//return the value for this field
        return C;
    }
    void setValue(int n){//set the value for this field
        C = n;
    }
    void calculatePossible(){//CALCULATE how many digits are possible in this field
        int n = 0;
        if(C) n = 1;
        else for(int i = 1; i < 10; i++)
            if(Possible[i]) n++;
        NumberOfPossible = n;
    }
    int numberOfPossible(){//RETURN how many digits are possible in this field
        calculatePossible();
        return NumberOfPossible;
    }
};

class Board{
private:
    Field field[9][9];
    bool Possible;
public:
    void reset(){//reset the board to blank
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                field[i][j].reset();
        Possible = true;
    }
    void calculatePossiblities(){//for each field, calculate which digits are possible, according to sudoku rules (and possibly additional rules, i.e. killer sudoku, if defined)
        if(Rule[0]){//check rows
            for(int j = 0; j < 9; j++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = field[n][j].value();
                    if(k != 0)
                        for(int i = 0; i < 9; i++)
                            field[i][j].setPossible(k, false);
                    n++;
                }
            }
        }
        if(Rule[1]){//check columns
            for(int i = 0; i < 9; i++)//ta sama procedura dla kazdego wiersza po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = field[i][n].value();
                    if(k != 0)
                        for(int j = 0; j < 9; j++)
                            field[i][j].setPossible(k, false);
                    n++;
                }
            }
        }
        if(Rule[2]){//check 3x3 squares
            for(int i3 = 0; i3 < 3; i3++) for(int j3 = 0; j3 < 3; j3++)//ta sama procedura dla kazdego kwadratu po kolei
            {
                int n = 0;
                int k = 0;
                while(n < 9){
                    k = field[i3 * 3 + n % 3][j3 * 3 + n / 3].value();
                    if(k != 0)
                        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++)
                            field[i3 * 3 + i][j3 * 3 + j].setPossible(k, false);
                    n++;
                }
            }
        }
    }
    void checkIfPossible(){//calculate whether the board is technically possible or not
        if(Possible == false) return;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(field[i][j].numberOfPossible() == 0)
                {
                    Possible = false;
                    return;
                }
    }
    void read(std::string input[]){//read board from string
        for(int j = 1; j <= 9; j++)
        {
            std::string s = input[j - 1];
            for(int i = 1; i <= 9; i++)
            {
                char c = s[i - 1];
                field[i - 1][j - 1].reset();
                if(!(c == ' '))
                    field[i - 1][j - 1].setValue(c - 48);
            }
        }
        Possible = true;
    }
    Coords nextTarget(){//calculate and return the coordinates of the field which contains the LEAST number of possible digits
        Coords K;
        K.x = 10;
        K.y = 10;
        //first, we find one field which is not yet filled. Any one field.
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
                if(field[i][j].value() == 0){
                    K.x = i;
                    K.y = j;
                    break;
                }
            if(K.x != 10)
                break;
        }
        if(K.x == 10) return K;//that means that all the fields have been filled and this can be returned as result

        //if not all fields have been filled, check where the least possibilities are

        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if((field[i][j].value() == 0) && (field[i][j].numberOfPossible() < field[K.x][K.y].numberOfPossible()))//if field is enpty and contains fewer possibilities that the one previously considered as the "minimum"
                {
                    K.x = i;
                    K.y = j;
                }
                if(field[K.x][K.y].numberOfPossible() == 0)
                {
                    Possible = false;
                    break;
                }
            }
            if(Possible == false)
                break;
        }
        return K;
    }
    void setPossible(int x, int y, int n, bool b){//set whether in the field (x,y), the number n is b-possible (true/false)
        field[x][y].setPossible(n, b);
    }
    void setValue(int x, int y, int n){//set the value of field (x,y) to n
        field[x][y].setValue(n);
    }
    void fillOnes(){//fill those fields which have exactly one number possible
        Coords K = nextTarget();
        do{
            if(field[K.x][K.y].numberOfPossible() == 1)
                for(int i = 1; i <= 9; i++)
                    if(field[K.x][K.y].possible(i)){
                        field[K.x][K.y].setValue(i);
                        calculatePossiblities();
                        break;
                    }
            K = nextTarget();
        }while((field[K.x][K.y].numberOfPossible() == 1) && field[K.x][K.y].empty());//naprawione - wczesniej sie zapetlalo bo jak jest wypelniona field to numberofpossible zwraca 1
    }
    int totalEmpty(){//how many empty fields remain
        int n = 0;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(field[i][j].empty())
                    n++;
        return n;
    }
    void print(){//print the board
        int x, y, k;

        for(int j = 0; j < 37; j++){
            y = (j - 1) / 4;
            for(int i = 0; i < 73; i++){
                if(line(i, j) == 'x'){
                    x = (i - 2) / 8;
                    if(field[x][y].value() == 0){
                        k = ((i - 2) % 8) / 2 + 3 * ((j - 1) % 4) + 1;
                        if(i % 2 == 0)
                            if(field[x][y].possible(k)) printf("%d", k);
                            else printf(" ");
                        else printf(" ");
                    }
                    else{
                        //179, 196
                        if(i % 8 == 4)
                            if(j % 4 == 2) printf("%d", field[x][y].value());
                            else printf("%c", 196);
                        else printf(" ");
                    }
                }
                else printf("%c", line(i, j));
            }
            printf("\n");
        }
    }
    bool solve(){//recursive solving function. false returned means that it's impossible
        do{
            calculatePossiblities();
            checkIfPossible();
            if(!Possible)
                return false;

            int sp;
            do{
                sp = totalEmpty();
                fillOnes();
                calculatePossiblities();
            }while(sp != totalEmpty());

            if(totalEmpty() == 0)
                return true;

            checkIfPossible();
            if(!Possible)
                return false;

            Coords c = nextTarget();

            for(int i = 1; i < 10; i++)
                if(field[c.x][c.y].possible(i)){
                    Board P;
                    P.reset();
                    for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                        {
                            P.setValue(i, j, field[i][j].value());
                            for(int k = 1; k < 10; k++)
                                P.setPossible(i, j, k, field[i][j].possible(k));
                        }
                    P.setValue(c.x, c.y, i);
                    bool b = P.solve();
                    if(b == false)
                    {
                        field[c.x][c.y].setPossible(i, false);
                        break;
                    }
                }

        }while(totalEmpty() > 0);

    }
    void readFromFile(){//read sudoku from file
        std::string row[9];
        std::string s;
        int n = 0;
        std::ifstream File("input.txt");
        while(getline(File, s)){
            row[n] = s;
            n++;
        }
        read(row);
    }
};

int main(){
    Board board;

    board.readFromFile();

    if(board.solve()){
        board.print();
        //printf(" # Kunc\n");//"The end" in Kashubian
    }
    else
        printf("Sudoku contains errors.\n");

    system("pause");
    return 0;
}
