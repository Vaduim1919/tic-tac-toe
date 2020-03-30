#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

int board[26] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};   // perredelat na rangex (python)
int turn = 1,flag = 0;
int player,comp;

void menu();
void go(int n);
void start_game();
void check_draw();
void draw_board();
void player_first();
void put_X_O(char ch,int pos);
COORD coord= {0,0}; // Глобальна зміна
//центер осі 
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void main()
{
    system("cls");
    menu();
    getch();

}

void menu()
{
    int choice;
    system("cls");
    printf("\n--------MENU--------");
    printf("\n1 : Play with X");
    printf("\n2 : Play with O");
    printf("\n3 : Exit");
    printf("\nEnter your choice:>");
    scanf("%d",&choice);
    turn = 1;
    switch (choice)
    {
    case 1:
        player = 1;
        comp = 0;
        player_first();
        break;
    case 2:
        player = 0;
        comp = 1;
        start_game();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

int make2()     //peredelat nazvanie na smilslovoy
{
    if(board[8] == 2)
        return 8;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[12] == 2)
        return 12;
    if(board[2] == 2)
        return 2; 
    if(board[16]== 2)
        return 16;
    if(board[19]== 2)
        return 19;
    if(board[25]== 2)
        return 25;
    if(board[17]== 2)
        return 17;
    if(board[13]== 2)
        return 13;
    if(board[11]== 2)
        return 11;
    if(board[21]== 2)
        return 21;
    if(board[23]== 2)
        return 23;
    return 0;
}

int make4()
{
    if(board[1] == 2)
        return 1;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[10] == 2)
        return 10;
    if(board[9]== 2)
        return 9;
    if(board[14]== 2)
        return 14;
    if(board[15] == 2)
        return 15;
    if(board[18] == 2)
        return 18;
    if(board[22]== 2)
        return 22;
    if(board[24]== 2)
        return 24;
    if(board[5]== 2)
        return 5;
    if(board[20]== 2)
        return 20;
    return 0;
}

int posswin(int p)
{
//p == 1, то X p == 0, то O
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;

    i = 1;
    while(i<=25)//перевірка рядків

    {
        if(board[i] * board[i+1] * board[i+2] * board[i+3] * board[i+4]  == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+4] == 2)
                return i+4;
            
        }
        i+=5;
    }

    i = 1;
    while(i<=5)//перевірка стовпців

    {
        if(board[i] * board[i+5] * board[i+10]  * board[i+15]  * board[i+20] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+5] == 2)
                return i+5;
            if(board[i+10] == 2)
                return i+10;
            if(board[i+15] == 2)
                return i+15;
            if(board[i+20] == 2)
                return i+20;
            
        }
        i++;
    }

    if(board[1] * board[7] * board[13] * board[19] * board[25] == check_val) //діагональ
    {
        if(board[1] == 2)
            return 1;
        if(board[7] == 2)
            return 7;
        if(board[13] == 2)
      		 return 13;
      	if(board[19] == 2)
      		 return 19;
      	if(board[25] == 2)
      		 return 25;
	
    }

    if(board[5] * board[9] * board[13] * board[17] * board[21] == check_val) //діагональ
    {
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
        if(board[13] == 2)
            return 13;
        if(board[17] == 2)
            return 17;
        if(board[21] == 2)
            return 21;            
    }
    return 0;
}

//
void go(int n)
{
    if(turn % 2)
        board[n] = 5;
    else
        board[n] = 13;
    turn++;
}

void player_first()
{
    int pos;

    check_draw();
    draw_board();
    gotoxy(30,25);
    printf("Number :> ");
    scanf("%d",&pos);

    if(board[pos] != 2)
        player_first();

    if(pos == posswin(player))
    {
        go(pos);
        draw_board();
        gotoxy(25,27);
        

        printf("You win");
        getch();
        exit(0);
    }

    go(pos);
    draw_board();
    start_game();
}

void start_game()
{
// p == 1, то X p == 0

    if(posswin(comp))
    {
        go(posswin(comp));
        flag = 1;
    }
    else if(posswin(player))
        go(posswin(player));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        gotoxy(25,27);

        printf("Computer wins");
        getch();
    }
    else
        player_first();
}

void check_draw()
{
    if(turn > 25)
    {
        gotoxy(25,27);

        printf("Game Draw");
        getch();
        exit(0);
    }
}

void draw_board()
{
    int j;

    for(j=9; j<24; j++)
    {
        gotoxy(35,j);
        printf("|       |       |       |");
    }
    gotoxy(28,11);
    printf("----------------------------------------" );
    gotoxy(28,14);
    printf("----------------------------------------");
    gotoxy(28,17);
    printf("----------------------------------------");
    gotoxy(28,20);
    printf("----------------------------------------");

    for(j=1; j<25; j++)
    {
        if(board[j] == 5)
            put_X_O('X',j);
        else if(board[j] == 13)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int pos) //Головна функція вивода
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 5)
    {
        while(m > 5)
        {
            y += 3;
            m -= 3;
            
    
        }
        
    }
    if(pos % 5 == 0)
        x += 20;
    else
    {
        pos %= 5; 
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}
