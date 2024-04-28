#include<cstdio>

short int other(int a, int b){ //which of the three fields is other than a and b
    int c;
    if((a != 1) && (b != 1)) c = 1;
        else if((a == 2) || (b == 2)) c = 3;
            else c = 2;
    return c;
}

void move(int w1, int w2, //from field w1 to field w2
          int bot){ //how many we move from the top
          char * s;
          if(bot == 1){
                if(w1 == 1)
                    if(w2 == 2) s = "Left to middle.\n";
                    else s = "Left to right.\n";
                else if(w1 == 2)
                    if(w2 == 1) s = "Middle to left.\n";
                    else s = "Middle to right.\n";
                else if(w2 == 1) s = "Right to left.\n";
                    else s = "Right to middle.\n";
                printf("%s", s);
          }
          else{
                move(w1, other(w1, w2), bot - 1);
                move(w1, w2, 1);
                move(other(w1, w2), w2, bot - 1);
          }
}

int main(){
    int n;
    char * question = "How many Hanoi discs are to be moved from the left to the right? [enter 0 to quit]\n";
    printf("%s", question);
    scanf("%d", &n);

    while(n){
        printf("Here's how you do it:\n\n");
        move(1, 3, n);
        printf("\n");
        printf("%s", question);
        scanf("%d", &n);
    }
    return 0;

}
