#include<iostream>
#include<conio.h>
#include<direct.h>
#include<windows.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include<vector>

using namespace std;

//start of car game

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define PIPE_DIF 45

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;

    int enemyY[3];
    int enemyX[3];
    int enemyFlag[3];
    char car[4][4] = { ' ','#','#',' ',
                       '#','#','#','#',
                       ' ','#','#',' ',
					   '#','#','#','#' };

    int carPos = WIN_WIDTH/2;
    int score = 0;

    void gotoxy(int x, int y)
    {
        CursorPosition.X = x;
        CursorPosition.Y = y;
        SetConsoleCursorPosition(console, CursorPosition);
    }

    void setcursor(bool visible, DWORD size)
    {
        if(size == 0)
        {
            size = 20;
        }
		CONSOLE_CURSOR_INFO lpCursor;
		lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console,&lpCursor);
    }

    void drawBorder()
    {
        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            for(int j=0; j<17; j++)
            {
                gotoxy(0+j,i); cout<<"*";
                gotoxy(WIN_WIDTH-j,i); cout<<"*";
            }
        }
        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            gotoxy(SCREEN_WIDTH,i); cout<<"ą";
        }
    }

    void genEnemy(int ind)
    {
        enemyX[ind] = 17 + rand()%(33);
    }

    void drawEnemy(int ind)
    {
        if( enemyFlag[ind] == true )
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout<<"****";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout<<" ** ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout<<"****";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout<<" ** ";
        }
    }

    void eraseEnemy(int ind)
    {
        if( enemyFlag[ind] == true )
        {
            gotoxy(enemyX[ind], enemyY[ind]);
            cout<<"    ";
            gotoxy(enemyX[ind], enemyY[ind]+1);
            cout<<"    ";
            gotoxy(enemyX[ind], enemyY[ind]+2);
            cout<<"    ";
            gotoxy(enemyX[ind], enemyY[ind]+3);
            cout<<"    ";
        }
    }

    void resetEnemy(int ind)
    {
        eraseEnemy(ind);
        enemyY[ind] = 1;
        genEnemy(ind);
    }

    void drawCar()
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout<<car[i][j];
            }
        }
    }

    void eraseCar()
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+carPos, i+22);
                cout<<" ";
            }
        }
    }

    int collision()
    {
        if( enemyY[0]+4 >= 23 )
        {
            if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  )
            {
                return 1;
            }
        }
        return 0;
    }

    void gameover()
    {
        system("cls");
        cout<<endl;
        cout<<"\t\t--------------------------"<<endl;
        cout<<"\t\t-------- Game Over -------"<<endl;
        cout<<"\t\t--------------------------"<<endl<<endl;
        cout<<"\t\tPress any key to go back to menu.";
        getch();
    }

    void updateScore()
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout<<"Score: "<<score<<endl;
    }

    void instructionscar()
    {
        system("cls");
        cout<<"Instructions";
        cout<<"\n----------------";
        cout<<"\n Avoid Cars by moving left or right. ";
        cout<<"\n\n Press 'a' to move left";
        cout<<"\n Press 'd' to move right";
        cout<<"\n Press 'escape' to exit";
        cout<<"\n\nPress any key to go back to menu";
        getch();
    }

    void playcar()
    {
        carPos = -1 + WIN_WIDTH/2;
        score = 0;
        enemyFlag[0] = 1;
        enemyFlag[1] = 0;
        enemyY[0] = enemyY[1] = 1;
        system("cls");
        drawBorder();
        updateScore();
        genEnemy(0);
        genEnemy(1);

        gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game";
        gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
        gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
        gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
        gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
        gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left";
        gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right";

        gotoxy(18, 5);cout<<"Press any key to start";
        getch();
        gotoxy(18, 5);cout<<"                      ";

        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if( ch=='a' || ch=='A' )
                {
                    if( carPos > 18 )
                    {
                        carPos -= 4;
                    }

                }
                if( ch=='d' || ch=='D' )
                {
                    if( carPos < 50 )
                    {
                        carPos += 4;
                    }
                }
                if(ch==27)
                {
                    break;
                }
            }

            drawCar();
            drawEnemy(0);
            drawEnemy(1);
            if( collision() == 1  )
            {
                gameover();
                return;
            }
            Sleep(50);
            eraseCar();
            eraseEnemy(0);
            eraseEnemy(1);

            if( enemyY[0] == 10 )
                if( enemyFlag[1] == 0 )
                    enemyFlag[1] = 1;

            if( enemyFlag[0] == 1 )
                enemyY[0] += 1;

            if( enemyFlag[1] == 1 )
                enemyY[1] += 1;

            if( enemyY[0] > SCREEN_HEIGHT-4 )
            {
                resetEnemy(0);
                score++;
                updateScore();
            }

            if( enemyY[1] > SCREEN_HEIGHT-4 )
            {
                resetEnemy(1);
                score++;
                updateScore();
            }
        }
    }

//end of car game

//start of ticktactoe

    char square[10] = {'0','1','2','3','4','5','6','7','8','9'};

    int checkwin();
    void board();

/*********************************************
    FUNCTION TO RETURN GAME STATUS
    1 FOR GAME IS OVER WITH RESULT
    -1 FOR GAME IS IN PROGRESS
    O GAME IS OVER AND NO RESULT
**********************************************/

    int checkwin()
    {
        if (square[1] == square[2] && square[2] == square[3])
            return 1;

        else if (square[4] == square[5] && square[5] == square[6])
            return 1;

        else if (square[7] == square[8] && square[8] == square[9])
            return 1;

        else if (square[1] == square[4] && square[4] == square[7])
            return 1;

        else if (square[2] == square[5] && square[5] == square[8])
            return 1;

        else if (square[3] == square[6] && square[6] == square[9])
            return 1;

        else if (square[1] == square[5] && square[5] == square[9])
            return 1;

        else if (square[3] == square[5] && square[5] == square[7])
            return 1;

        else if (square[1] != '1' && square[2] != '2' && square[3] != '3'&& square[4] != '4' && square[5] != '5' && square[6] != '6'&& square[7] != '7' && square[8] != '8' && square[9] != '9')
            return 0;
        else
            return -1;
    }


/*******************************************************************
     FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/

    void board()
    {
        system("cls");
        cout << "\n\n\tTic Tac Toe\n\n";

        cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
        cout << endl;

        cout << "     |     |     " << endl;
        cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;

        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;

        cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;

        cout << "_____|_____|_____" << endl;
        cout << "     |     |     " << endl;

        cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;

        cout << "     |     |     " << endl << endl;
    }

//end of ticktactoe

//start of toh

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5

    int towers[3][DISKS];
    int towerTop[3] = {DISKS-1,-1,-1};
    int tries = 0;

    void instructionstoh()
    {
        system("cls");
        cout<<"Instructions";
        cout<<"\n----------------";
        cout<<"\n Shift Disks from Tower 1 to Tower 3. ";
        cout<<"\n You can not place large disk on small disk";
        cout<<"\n Towers are Numbered as 1,2 and 3";
        cout<<"\n\nPress any key to go back to menu";
        getch();
    }

    void drawTile(int tower, int tileNo, int y)
    {
        int x;
        if( tower == 1 )
            x = T1POS;
        else if( tower == 2 )
            x = T2POS;
        else if( tower == 3 )
            x = T3POS;

        x -= tileNo;

        for(int j=0; j<((tileNo)*2)-1; j++)
        {
            gotoxy(x,y);
            cout<<"*";
            x++;
        }
    }

    void drawTower(int tower)
    {
        int y = 9;

        gotoxy(10, 10); cout<<"==========";
        gotoxy(25, 10); cout<<"==========";
        gotoxy(40, 10); cout<<"==========";

        gotoxy(15, 11); cout<<"1";
        gotoxy(30, 11); cout<<"2";
        gotoxy(45, 11); cout<<"3";

        for(int i=0; i<5; i++)
        {
            drawTile(tower, towers[tower-1][i], y);
            y--;
        }
    }

    int isEmpty(int towerNo)
    {
        for(int i=0; i<DISKS; i++)
            if( towers[towerNo][i] != 0 )
                return 0;
        return 1;
    }

    int validate(int from, int to)
    {
        if( !isEmpty(to) )
        {
            if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
                return 1;
            else
                return 0;
        }
        return 1;
    }

    int move(int from, int to)
    {
        if( isEmpty(from) )
            return 0;
        if( validate(from, to) )
        {
            if( towers[from][towerTop[from]] != 0 )
            {
                towerTop[to]++;
                towers[to][towerTop[to]] = towers[from][towerTop[from]];
                towers[from][towerTop[from]] = 0;
                towerTop[from]--;
                return 1;
            }
        }
        return 0;
    }

    int win()
    {
        for(int i=0; i<DISKS; i++)
            if( towers[2][i] != DISKS-i )
                return 0;
        return 1;
    }

    void playtoh()
    {
        int from,to;
        for(int i=0; i<DISKS; i++)
            towers[0][i] = DISKS-i;

        for(int i=0; i<DISKS; i++)
            towers[1][i] = 0;

        for(int i=0; i<DISKS; i++)
            towers[2][i] = 0;

        do
        {
            system("cls");

            cout<<"============================================================"<<endl;
            cout<<"                       TOWER OF HANOI                       "<<endl;
            cout<<"============================================================"<<endl<<endl;

            drawTower(1);
            drawTower(2);
            drawTower(3);

            if( win() )
            {
                system("cls");
                cout<<"============================================================"<<endl;
                cout<<"                           YOU WIN                          "<<endl;
                cout<<"============================================================"<<endl;
                cout<<endl<<endl<<endl;
                cout<<"Press any key to go back to menu...";
                getch();
                break;
            }

            gotoxy(10,15);
            cout<<"From (Values: 1,2,3): ";
            cin>>from;
            gotoxy(10,16);
            cout<<"To (Values: 1,2,3): ";
            cin>>to;

            if( to < 1 || to > 3 )
                continue;
            if( from < 1 || from > 3 )
                continue;
            if( from == to )
                continue;

            from--;
            to--;

            move(from, to);

            if(kbhit())
            {
                char ch = getch();
                if( ch=='a' || ch=='A' )
                {

                }
                if( ch=='d' || ch=='D' )
                {

                }
                if(ch==27)
                {
                    break;
                }
            }

        }while(1);
    }

//end of toh
//start of flappy bird

    int pipePos[3];
    int gapPos[3];
    int pipeFlag[3];
    char bird[2][6] = { '/','-','-','o','\\',' ',
                        '|','_','_','_',' ','>' };
    int birdPos = 6;
    int score1 = 0;

    void drawBorder1()
    {
        for(int i=0; i<SCREEN_WIDTH; i++)
        {
            gotoxy(i,0);
            cout<<"*";
            gotoxy(i,SCREEN_HEIGHT);
            cout<<"*";
        }

        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            gotoxy(0,i);
            cout<<"*";
            gotoxy(SCREEN_WIDTH,i);
            cout<<"*";
        }

        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            gotoxy(WIN_WIDTH,i); cout<<"ą";
        }
    }

    void genPipe(int ind)
    {
        gapPos[ind] = 3 + rand()%14;
    }

    void drawPipe(int ind)
    {
        if( pipeFlag[ind] == true )
        {
            for(int i=0; i<gapPos[ind]; i++)
            {
                gotoxy(WIN_WIDTH-pipePos[ind],i+1);
                cout<<"***";
            }
            for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++)
            {
                gotoxy(WIN_WIDTH-pipePos[ind],i+1);
                cout<<"***";
            }
        }
    }

    void erasePipe(int ind)
    {
        if( pipeFlag[ind] == true )
        {
            for(int i=0; i<gapPos[ind]; i++)
            {
                gotoxy(WIN_WIDTH-pipePos[ind],i+1);
                cout<<"   ";
            }
            for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++)
            {
                gotoxy(WIN_WIDTH-pipePos[ind],i+1);
                cout<<"   ";
            }
        }
    }

    void drawBird()
    {
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<6; j++)
            {
                gotoxy(j+2,i+birdPos); cout<<bird[i][j];
            }
        }
    }

    void eraseBird()
    {
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<6; j++)
            {
                gotoxy(j+2,i+birdPos); cout<<" ";
            }
        }
    }

    int collision1()
    {
        if( pipePos[0] >= 61  )
        {
            if( birdPos<gapPos[0] || birdPos >gapPos[0]+GAP_SIZE )
            {
                return 1;
            }
        }
        return 0;
    }

    void updateScore1()
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout<<"Score: "<<score1<<endl;
    }

    void instructionsflappy()
    {
        system("cls");
        cout<<"Instructions";
        cout<<"\n----------------";
        cout<<"\n Press spacebar to make bird fly";
        cout<<"\n\nPress any key to go back to menu";
        getch();
    }

    void playflappy()
    {
        birdPos = 6;
        score1 = 0;
        pipeFlag[0] = 1;
        pipeFlag[1] = 0;
        pipePos[0] = pipePos[1] = 4;

        system("cls");
        drawBorder1();
        genPipe(0);
        updateScore1();

        gotoxy(WIN_WIDTH + 5, 2);cout<<"FLAPPY BIRD";
        gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
        gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
        gotoxy(WIN_WIDTH + 7, 12);cout<<"Control ";
        gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
        gotoxy(WIN_WIDTH + 2, 14);cout<<" Spacebar = jump";

        gotoxy(10, 5);cout<<"Press any key to start";
        getch();
        gotoxy(10, 5);cout<<"                      ";

        while(1)
        {
            if(kbhit())
            {
                char ch = getch();
                if(ch==32)
                {
                    if( birdPos > 3 )
                        birdPos-=3;
                }
                if(ch==27)
                {
                    break;
                }
            }
            drawBird();
            drawPipe(0);
            drawPipe(1);
            if( collision1() == 1 )
            {
                gameover();
                return;
            }
            Sleep(100);
            eraseBird();
            erasePipe(0);
            erasePipe(1);
            birdPos += 1;

            if( birdPos > SCREEN_HEIGHT - 2 )
            {
                gameover();
                return;
            }

            if( pipeFlag[0] == 1 )
                pipePos[0] += 2;

            if( pipeFlag[1] == 1 )
                pipePos[1] += 2;

            if( pipePos[0] >= 40 && pipePos[0] < 42 )
            {
                pipeFlag[1] = 1;
                pipePos[1] = 4;
                genPipe(1);
            }
            if( pipePos[0] > 68 )
            {
                score1++;
                updateScore1();
                pipeFlag[1] = 0;
                pipePos[0] = pipePos[1];
                gapPos[0] = gapPos[1];
            }

        }
    }

//end of flappy bird

//start of rock paper scissor

    const char ROCK = 'r';
    const char PAPER = 'p';
    const char SCISSORS = 's';

    char getComputerOption()
    {
        srand(time(0));
        // Random number
        int num = rand() % 3 + 1;

        if(num==1) return 'r';
        if(num==2) return 'p';
        if(num==3) return 's';
        else return 0;
    }

    char getUserOption()
    {
        char c;
        cout << "Rock, Paper and Scissors Game!" << endl;
        cout << "Choose one of the following options"  << endl;
        cout << "-----------------------------------"  << endl;
        cout << "(r) for rock " << endl << "(p) for paper" << endl << "(s) for scissors " << endl;
        cin >> c;

        while (c!='r' && c!='p' && c!='s' )
        {
            cout << "Please enter one of the following options only. " << endl;
            cout << "(r) for rock " << endl << "(p) for paper" << endl << "(s) for scissors " << endl;
            cin >> c;
        }
        return c;
    }

    void showSelectedOption(char option)
    {
        if (option == 'r')
            cout << "Rock" << endl;
        if (option == 'p')
            cout << "Paper" << endl;
        if (option == 's')
            cout << "Scissors" << endl;
    }

    void chooseWinner(char uChoice, char cChoice)
    {
        if (uChoice == ROCK && cChoice == PAPER)
        {
            cout << "Computer Wins! Paper wraps Rock."<< endl;
        }
        else if (uChoice == PAPER && cChoice == SCISSORS)
        {
            cout << "Computer Wins! Scissors cut Paper."<< endl;
        }
        else if (uChoice == SCISSORS && cChoice == ROCK)
        {
            cout << "Computer Wins! Rock smashes Scissors."<< endl;
        }
        else if (uChoice == ROCK && cChoice == SCISSORS)
        {
            cout << "You Win! Paper wraps Rock."<< endl;
        }
        else if (uChoice == PAPER && cChoice == ROCK)
        {
            cout << "You Win! Paper wraps Rock."<< endl;
        }
        else if (uChoice == SCISSORS && cChoice == PAPER)
        {
            cout << "You Win! Scissors cut Paper."<< endl;
        }
        else
        {
            cout << "Tie. Play again win the Game." << endl;
        }
    }


//end of rock paper scissor

//start of hangman

    void greet()
    {
        cout<<"============\n";
        cout<<"hangman: the game\n";
        cout<<"=========\n";
        cout<<"instructions: save your friend from being hanged by guessing the letter in the codeword.\n";
    }

    void display_misses(int misses)
    {
        if(misses==0)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==1)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==2)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"   o       | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==3)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"   o       | \n";
            cout<<"   |       | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==4)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"   o       | \n";
            cout<<"   |       | \n";
            cout<<"  /|\\      | \n";
            cout<<"           | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==5)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"   o       | \n";
            cout<<"   |       | \n";
            cout<<"  /|\\      | \n";
            cout<<"   |       | \n";
            cout<<"           | \n";
            cout<<"           | \n";
        }
        else if(misses==6)
        {
            cout<<"   +-------+ \n";
            cout<<"   |       | \n";
            cout<<"   o       | \n";
            cout<<"   |       | \n";
            cout<<"  /|\\      | \n";
            cout<<"   |       | \n";
            cout<<"  / \\      | \n";
            cout<<"           | \n";
        }
    }

    void display_status(vector<char> incorrect,string answer)
    {
        int i;
        cout<<"incorrect guesses: \n";

        for(i=0;i<incorrect.size();i++)
        {
            cout<<incorrect[i]<<" ";
        }
        cout<<"\ncodeword:\n";

        for(i=0;i<answer.length();i++)
        {
            cout<<answer[i]<<" ";
        }
    }

    void end_game(string answer,string codeword)
    {
        if(answer==codeword)
        {
            cout<<"\nyes!you saved a person\n";
            cout<<"\ncongo\n";
        }
        else
        {
            cout<<"\noh!the person is hanged\n";
        }
    }

//end of hangman

//start of snake game

    bool gameOver;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score3;
    int tailX[100], tailY[100];
    int nTail;
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
    eDirecton dir;

    void Setup()
    {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score3 = 0;
    }

    void Draw()
    {
        system("cls"); //system("clear");
        for (int i = 0; i < width+2; i++)
        cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    cout << "#";
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX)
                    cout << "F";
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }


                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width+2; i++)
            cout << "#";
        cout << endl;
        cout << "Score:" << score3 << endl;
    }

    void Input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'l':
                dir = LEFT;
                break;
            case 'r':
                dir = RIGHT;
                break;
            case 'u':
                dir = UP;
                break;
            case 'd':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void Logic()
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }
        //if (x > width || x < 0 || y > height || y < 0)
        //  gameOver = true;
        if (x >= width) x = 0; else if (x < 0) x = width - 1;
        if (y >= height) y = 0; else if (y < 0) y = height - 1;

        for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = true;

        if (x == fruitX && y == fruitY)
        {
            score3 += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            nTail++;
        }
    }

//end of snake game

void loading()
{
        system("cls");
        cout<<"\t************************************************************************************************\n\n\n\n";
        cout<<"\t\t\t\t\t\tLOADING.";
	Sleep(1000);
	cout<<".";
	Sleep(1000);
	cout<<".";
	Sleep(1000);
	cout<<".\n\n\n\n";
	Sleep(3500);
	        cout<<"\t************************************************************************************************\n\n\n\n";
	        Sleep(1000);
	system("cls");
   }
        void welcome()
        {
        cout<<"\t************************************************************************************************\n\n\n\n";
        cout<<"\t\t\t\t\t\tWELCOME......\n\n\n\n";
        cout<<"\t************************************************************************************************\n\n";
        }


        void mmnue()
        {
                    cout<<"\t\t\t\t1PLAY GAME \n\n";
                    cout<<"\t\t\t\t2 INSTRUCTION ON HOW TO PLAY GAME\n\n";
                    cout<<"\t\t\t\t3 MAIN MENU\n\n";
                    cout<<"\t************************************************************************************************\n";
                    cout<<"\t************************************************************************************************\n\n\n\n";
        }


//Main screen function code.........
void option(int choice)
{
	int ch;
	ch = choice;

        switch(ch)
        {
            case 1:
            {
                loading();
                setcursor(0,0);
                srand( (unsigned)time(NULL));
              do
              {
                    system("cls");
                    cout<<"\t************************************************************************************************\n";
                    cout<<"\t************************************************************************************************\n\n\n\n";
                    cout<<"\t\t\t\tCAR GAME:-\n\n";
                    mmnue();

                    char op = getche();

                    if( op=='1')
                        playcar();
                    else if( op=='2')
                        instructionscar();
                    else if( op=='3')
                       break;

            }while(1);
                break;

            }
            case 2:
            {
                loading();
                int player = 1,i,choice;
                char mark;
                do
                {
                    board();
                    player=(player%2)?1:2;

                    cout << "Player " << player << ", enter a number:  ";
                    cin >> choice;

                    mark=(player == 1) ? 'X' : 'O';

                    if (choice == 1 && square[1] == '1')
                        square[1] = mark;

                    else if (choice == 2 && square[2] == '2')
                        square[2] = mark;

                    else if (choice == 3 && square[3] == '3')
                        square[3] = mark;

                    else if (choice == 4 && square[4] == '4')
                        square[4] = mark;

                    else if (choice == 5 && square[5] == '5')
                        square[5] = mark;

                    else if (choice == 6 && square[6] == '6')
                        square[6] = mark;

                    else if (choice == 7 && square[7] == '7')
                        square[7] = mark;

                    else if (choice == 8 && square[8] == '8')
                        square[8] = mark;

                    else if (choice == 9 && square[9] == '9')
                        square[9] = mark;

                    else
                    {
                        cout<<"Invalid move ";
                        player--;
                        cin.ignore();
                        cin.get();
                    }
                    i=checkwin();
                    player++;
                }while(i==-1);
                board();
                if(i==1)
                    cout<<"==>\aPlayer "<<--player<<" win ";
                else
                    cout<<"==>\aGame draw";

                cin.ignore();
                cin.get();
		Sleep(4000);
                break;
        }
        case 3:
        {
            setcursor(0,0);
            srand( (unsigned)time(NULL));

            do
            {
                system("cls");
                loading();
                gotoxy(10,5); cout<<" -------------------------- ";
                gotoxy(10,6); cout<<" |     Tower of Hanoi     | ";
                gotoxy(10,7); cout<<" --------------------------";
                gotoxy(10,9); cout<<"1. Start Game";
                gotoxy(10,10); cout<<"2. Instructions";
                gotoxy(10,11); cout<<"3. Quit";
                gotoxy(10,13); cout<<"Select option: ";
                char op = getche();

                if( op=='1') playtoh();
                else if( op=='2') instructionstoh();
                else if( op=='3') break;
            }while(1);
            break;
        }
        case 4:
        {
            setcursor(0,0);
            srand( (unsigned)time(NULL));
          do
            {
                system("cls");
                cout<<"\t************************************************************************************************\n";
                cout<<"\t************************************************************************************************\n\n\n\n";
                    cout<<"\t\t\t\tflappy GAME:-\n\n";
                    mmnue();
                char op = getche();

                if( op=='1') playflappy();
                else if( op=='2') instructionsflappy();
                else if( op=='3') break;

            }while(1);
            break;
        }
        case 5:
        {
            system("cls");
            //User's choice
            char uChoice;
            //Compter's choice
            char cChoice;

            uChoice = getUserOption();
            cout << "Your choice is: "<< endl;
            showSelectedOption(uChoice);

            cout << "Computer's choice is: "<< endl;
            cChoice = getComputerOption();
            showSelectedOption(cChoice);

            chooseWinner(uChoice, cChoice);
	    Sleep(4000);
            break;
        }
        case 6:
        {
            greet();

            string codeword="codingcleverly";
            string answer=  "______________";

            int misses=0;
            vector<char> incorrect;
            bool guess=false;
            char letter;

            while(answer!=codeword && misses<7)
            {
                display_misses(misses);
                display_status(incorrect,answer);

                cout<<"\n\nplease enter your guess: ";
                cin>>letter;

                for(int i=0;i<codeword.length();i++)
                {
                    if(letter==codeword[i])
                    {
                        answer[i]=letter;
                        guess=true;
                    }
                }
                if(guess)
                {
                    cout<<"\ncorrect!\n";
                }
                else
                {
                    cout<<"\nincorrect! danger\n";
                    incorrect.push_back(letter);
                    misses++;
                }
                guess=false;
            }

            end_game(answer,codeword);
	    Sleep(4000);
            break;
        }
        case 7:
        {
            Setup();
            while (!gameOver)
            {
                Draw();
                Input();
                Logic();
                Sleep(3000); //sleep(10);
            }
            break;
        }

        }

}


void mainscreen()
{
	int choice;


 do
 {
     system("cls");
     loading();
        cout<<"\n\t************************************************************************************************\n\n\n\n";
        cout<<"\t\t\t\tlist of games are as follows:-\n\n";
        cout<<"\t\t\t\t1 cargame\n\n";
        cout<<"\t\t\t\t2 tick tac toe\n\n";
        cout<<"\t\t\t\t3 tower of hanoi\n\n";
        cout<<"\t\t\t\t4 flappy bird\n\n";
        cout<<"\t\t\t\t5 rock paper scissor\n\n";
        cout<<"\t\t\t\t6 hangman\n\n";
        cout<<"\t\t\t\t7 snake game\n\n";
        cout<<"\t\t\t\t0 exit\n\n";
        cout<<"\t************************************************************************************************\n";
        cout<<"\t************************************************************************************************\n\n\n\n";
        cout<<"ENTER YOU CHOICE : ";
            cin>>choice;
        cout<<"\n\n\t************************************************************************************************\n\n\n\n";
        Sleep(1000);

	system("cls");

	if(choice!=0)
	{
		option(choice);
 	}


 }while(choice!=0);


}






   int main()
    {
        loading();


        welcome();
        cout<<"\t\t\t\t*******  ******  *       *  *****\t\n";
        cout<<"\t\t\t\t*        *    *  * *   * *  *    \t\n";
        cout<<"\t\t\t\t* ****   ******  *   *   *  *****\t\n";
        cout<<"\t\t\t\t* *  *   *    *  *       *  *    \t\n";
        cout<<"\t\t\t\t***  *   *    *  *       *  *****\t\n\n";
        cout<<"\t\t\t\t\t\t\t******   *****  *****  **     *  ****** \t\n";
        cout<<"\t\t\t\t\t\t\t*    *   *   *  *      * *    *  *    * \t\n";
        cout<<"\t\t\t\t\t\t\t******   *****  *****  *   *  *  ****** \t\n";
        cout<<"\t\t\t\t\t\t\t*    *   * *    *      *    * *  *    * \t\n";
        cout<<"\t\t\t\t\t\t\t*    *   *  *   *****  *     **  *    * \t\n\n";
        cout<<"\t************************************************************************************************\n";
        cout<<"\t************************************************************************************************\n\n\n\n";
        Sleep(3000);
        mainscreen();
        exit(0);

    return 0;
    }

