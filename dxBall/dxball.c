#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#define BUFF_SIZE 1000




int brickArrray[50];    // BRICK color array
int skillBrickArray[50];
int columnNumber = 10;
int rowNumber = 3;

void brick(int x, int y);                               // FINDS THE BRICK THE BALL TOUCHED
void checkColor(int x, int y);                          // ADJUST BAR SIZE ACCORDING TO ABILITY
void drawBall(int x, int y, int x_rad, int y_rad, int color);
void drawRectangle(int left, int top, int right ,int bottom, int color);

void initial();
void movingObj();
void ball();
void healthCheck();
void hitCheck();
void makeBricks();
void findSkillbricks();
void skills(int brickNumber, int d);
int fall(int y, int fall_vel);
void game_restart_adjust();
void restart();
void skill_timer();
void game_timer();
void score();
void scoreIncrease();
int middleOfTheBoard();
void highScoreSaver();

int timer_color = CYAN;
int skill_color;
int startTimer = 0;
float timeLeft = 300;         // SKILL DURATION
int game_score;
int game_timeLeft = 3000;
char scoreWriter[50];

int prej;
int prei;
int j = middleOfTheBoard();
int i = 920;

int x = 0;
int y = 0;

int prey;
int b;
int skill_bricks_Id[10];
int skill_brick_x[10];
int skill_brick_y[10];


int maxy;
int maxx;

int leftC = 400;
int rightC = 600;

int previousleftC = 400;
int previousrightC = 600;

int health = 5;                                // ADJUST HEALTH NUMBER
int ballonStick = 1;

int vel = 40;
char che;

bool finish = false;
bool start = true;

int main()
{
    initwindow(1600, 1000, "DXBALL", 100, 0);

    initial();

        while (finish == false) {

            makeBricks();

            movingObj();

            ball();

            healthCheck();

            hitCheck();
            int k = 1;
            int n;
            for(n=0; n<9; n++)
            {
                skills(skill_bricks_Id[k], k);
                k++;
            }

            skill_timer();

            game_timer();

            score();

            delay(10);

            }

    getch();
    closegraph();
    return 0;

}
void initial()
{

    //int maxx;
    //int maxy;
    maxx = getmaxx();
    maxy = getmaxy();


    bar(0,0,20,1000);   //sol
    bar(1580,0,1600,1000);  //sağ
    bar(0, 0, 1600, 20);    //üst
    //bar(0, 980, 1600, 1000);   // alt

    int q;
    int t = 1;
    int n;
    int k = 1;

    for(q=0; q<columnNumber*rowNumber; q++)
    {
        brickArrray[t] = GREEN;
        t++;
    }
    for(q=0; q<9; q++)
    {
        n = rand() % 30 + 1;

        skill_bricks_Id[k] = n;
        k++;
        brickArrray[n] = MAGENTA;
    }
    for(q=0; q<4; q++)
    {
        n = rand() % 9 + 1;
        skillBrickArray[k] = n;
        k++;
        //arr2[n] = MAGENTA;
    }
    findSkillbricks();
    //MessageBox(NULL, "Message", "Title", MB_OK);

    //setfillstyle(1, WHITE);
    //circle(j, i, 10);
    //floodfill(j , i, WHITE);

}
void makeBricks()                // MAKES THE GAME BRICKS
{
    int p;
    int e;
    int brickNumber = 1;
    int left = 100;
    int top = 200;
    int right = 200;
    int bottom = 220;

    for(e=0; e<rowNumber; e++)
    {
        for(p=0; p<columnNumber; p++)
        {

            setfillstyle(1, brickArrray[brickNumber]); //               BRICKS
            bar(left, top, right, bottom);

            brickNumber++;
            left = left + 150;
            right = right + 150;
        }
        left = 100;
        right = 200;
        top = top+ 50;
        bottom = bottom + 50;
    }

}
void skills(int brickNumber, int d)
{

    int x;
    int a = 50;
    int y;
    int b = 220;
    int n = 1;
    skill_color = BLUE;

    if(brickArrray[brickNumber] == BLACK)
    {

        if(start != false)
        {
            for(;n<=4; n++)
            {
                if(skillBrickArray[n] == skill_bricks_Id[brickNumber])
                {
                    skill_color = CYAN;
                }


            }

            b = 1;
            prey = skill_brick_y[d]-5;

            drawBall(skill_brick_x[d], prey, 30, 5, BLACK);
            drawBall(skill_brick_x[d], skill_brick_y[d], 30, 5, skill_color);

            checkColor(skill_brick_x[d], skill_brick_y[d]+5);
            skill_brick_y[d] = fall(skill_brick_y[d], 5);

        }
        else if(b==1)
        {
            drawBall(skill_brick_x[d], skill_brick_y[d], 30, 5, BLACK);
            b = 0;
        }
    }

}
void drawRectangle(int left, int top, int right ,int bottom, int color)
{
    setfillstyle(1, color);
    rectangle(left, top, right, bottom);

}
void drawBall(int x, int y, int x_rad, int y_rad, int color)
{
    setfillstyle(1, color);
    setcolor(color);
    fillellipse(x, y, x_rad, y_rad);
}
void findSkillbricks()
{
    int k;
    int i = 1;
    int n = 1;
    int columnN;

    int p =  10;
    int c;
    int left = 150;
    int bottom = 220;

    columnN = columnNumber;
    for(c=0; c < 9; c++)
    {
        bottom = 220;
        left = 150;

        for(k=0; k < rowNumber; k++)
        {

            for( ; i <= columnN; i++)
            {

                if(skill_bricks_Id[n] == i)
                {

                    skill_brick_x[n] = left;
                    skill_brick_y[n] = bottom;

                    break;
                }
                else if(i%10==0)
                {
                    left = 150;
                    bottom = bottom + 50;
                    columnN = columnN + 10;
                }
                else
                {
                    left = left + 150;

                }

            }
            if(skill_bricks_Id[n] == i)
            {

                left = 150;
                bottom = 220;
                n++;
                i = 1;
                break;
            }


        }


    }


}
int fall(int y, int fall_vel)
{
    prey = y;
    y = y + fall_vel;
    return y;

}
void checkColor(int x, int y)
{
    int color;
    int color_skill;
    int a;
    int b;

    color = getpixel(x, y);
    color_skill = getpixel(x, y-3);


    if(color == 15 && y+10 > 900 && start == true && rightC-leftC != 300 && color_skill == BLUE)
    {
        startTimer = 1;
        leftC = leftC - 50;
        rightC = rightC + 50;

        setfillstyle(1, WHITE);
        bar(leftC, maxy - 60, rightC, maxy - 40);
        //setfillstyle(1, BLACK);
        //bar(rightC, maxy - 60, maxx, maxy - 40);
        //start = false;
    }

    if(color == 15 && y+10 > 900 && start == true && rightC-leftC != 100 && color_skill == CYAN)
    {
        startTimer = 1;
        leftC = leftC + 50;
        rightC = rightC - 50;

        setfillstyle(1, BLACK);
        bar(0, maxy - 60, leftC, maxy - 40);
        setfillstyle(1, BLACK);
        bar(rightC, maxy - 60, maxx, maxy - 40);
        //start = false;

    }
}
void ball()
{
    prei = i;
    prej = j;

    drawBall(prej, prei, 10, 10, BLACK);

    j = j + x;
    i = i + y;

    drawBall(j, i, 10, 10, WHITE);
}
void movingObj()
{


    char direction;
    char che2;

    int vel;

    vel = 40;


    if(kbhit())
    {

        direction = getch();

        switch(direction)
        {
        case 'a':

            if(leftC > 20)
            {
                previousleftC = leftC;
                previousrightC = rightC;
                leftC = leftC - vel;
                rightC = rightC - vel;
                if(ballonStick == 1)
                {
                    j = middleOfTheBoard();
                    //prej = j+40;
                    drawBall(prej, prei, 10, 10, BLACK);

                }
            }
            break;
        case 'd':

            if(rightC < 1580)
            {
                previousleftC = leftC;
                previousrightC = rightC;
                leftC = leftC + vel;
                rightC = rightC + vel;
                if(ballonStick == 1)
                {
                    j = middleOfTheBoard();
                    //prej = j-40;
                    drawBall(prej, prei, 10, 10, BLACK);

                }
            }
            break;
                                    // BALL CONTROLS WITH KEYBOARD
        case 'w':                   // 'W'   THROWS THE BALL IF IT IS ON THE STICK
            x = 10;
            y = 10;
            ballonStick = 0;
            break;
        case 'u':                   // FOR GO 'UP'
            x = 0;
            y = 10*-1;
            ballonStick = 0;
            break;
        case 'j':                   // FOR GO 'DOWN'
            x = 0;
            y = 10;
            ballonStick = 0;
            break;
        case 'h':                   // FOR GO 'LEFT'
            x = 10*-1;
            y = 0;
            ballonStick = 0;
            break;
        case 'k':                   // FOR GO 'RIGHT'
            x = 10;
            y = 0;
            ballonStick = 0;
            break;

        }

        setfillstyle(1, BLACK);
        bar(previousleftC, maxy - 60, previousrightC, maxy - 40);

        setfillstyle(1, WHITE);
        bar(leftC, maxy - 60, rightC, maxy - 40);

    }
    //delay(10);
}
void healthCheck()
{

    char healthStr[3];
    sprintf(healthStr, "%d", health);
    setcolor(3);
    outtextxy(maxx/2 - 70, 50, "player1:");
    outtextxy(maxx/2 - 10, 50, healthStr);

    char res;

    if(i >= 950)  // zemin
    {
        if(health == 0)
        {

            outtextxy(maxx/2, maxy/2, "GAME OVER");
            highScoreSaver();                           // HIGH SCORE SAVER
            res = getch();

            if(res == 'r')
            {
                game_restart_adjust();
                initial();
            }

        }
        else
        {
            drawBall(j, i, 10, 10, BLACK);

            i = 920;
            j = middleOfTheBoard();

            ballonStick = 1;

            x = 0;
            y = 0;

            health --;
        }

    }
}
void hitCheck()
{
    int color;

    if(y < 0)               // UPWARD BALL MOVEMENT
    {
        color = getpixel(j, i - 11);
        if(color == 15 || color == 2 || color == 14 || color == 4 || color == 5)
        {
            y = y*-1;
            if(i > 30)
            {
                //getch();
                brick(j,i);
                scoreIncrease();
            }
        }
    }

    else if(y > 0)             // DOWNWARD BALL MOVEMENT
    {
        color = getpixel(j, i + 11);

        if(color == 15 || color == 2 || color == 14 || color == 4 || color == 5)
        {
            if(i <= 950)
            {
                y = y*-1;
            }
            if(i < 400)
            {
                brick(j ,i);
                scoreIncrease();
            }
        }

    }

    if(x > 0)                   // RIGHT BALL MOVEMENT
    {
        color = getpixel(j + 10, i);
        if(color == 15 || color == 2 || color == 14 || color == 4 || color == 5)
        {
            x = x*-1;
            if(j != 1570 && i < 900)
            {
                brick(j, i);
                scoreIncrease();
            }

        }
    }

    else if(x < 0)               // LEFT BALL MOVEMENT
    {
        color = getpixel(j - 20, i);
        if(color == 15 || color == 2 || color == 14 || color == 4 || color == 5)
        {
            x = x*-1;
            if(j != 30 && i < 900)
            {
                brick(j, i);
                scoreIncrease();
            }


        }
    }

}
void brick(int x, int y)
{
    char color;

    int n = 1;
    int i;
    int k;
    int lx = 90;
    int rx = 210;
    int ty = 190;
    int by = 230;

    for(i=0; i < columnNumber; i++)
    {

        if(lx <= x)
        {


            if(x <= rx)
            {
               break;
            }

            lx = lx + 150;
            rx = rx + 150;
            n++;

        }

    }

    for(k=0; k<rowNumber; k++)
    {

        if(ty <= y)
        {

            if(by >= y)
            {
                  break;
            }

        }
        n = n + 10;
        ty = ty + 50;
        by = by + 50;
    }


    lx = 90;
    rx = 210;
    ty = 190;
    by = 230;


    if(brickArrray[n] == GREEN)
    {
        brickArrray[n] = YELLOW;
    }
    else if(brickArrray[n] == YELLOW)
    {
        brickArrray[n] = RED;
    }
    else if(brickArrray[n] == RED)
    {
        brickArrray[n] = BLACK;
    }
    else if(brickArrray[n] == MAGENTA)
    {
        brickArrray[n] = BLACK;
    }

    n = 1;
}
void skill_timer()
{
    char timer[3];

    if(startTimer == 1)
    {
        sprintf(timer, "%.1f", timeLeft);
        setcolor(timer_color);
        outtextxy(maxx/2 - 10, maxy - 100, timer);
        if(timeLeft != 0)
        {
            timeLeft = timeLeft - 1;

        }
        else if(timeLeft == 0 )
        {
            if(rightC-leftC == 300)
            {
                leftC = leftC + 50;
                rightC = rightC - 50;
                setfillstyle(1, BLACK);
                bar(0, maxy - 60, leftC, maxy - 40);
                setfillstyle(1, BLACK);
                bar(rightC, maxy - 60, maxx, maxy - 40);
            }
            else if(rightC-leftC == 100)
            {
                leftC = leftC - 50;
                rightC = rightC + 50;
                setfillstyle(1, WHITE);
                bar(leftC, maxy - 60, rightC, maxy - 40);

            }

            startTimer = 0;
            timeLeft = 300;

            setfillstyle(1, BLACK);
            bar(maxx/2 - 100, maxy - 100, maxx/2 + 100, maxy - 60);


        }

    }

}
void game_timer()
{
    char game_time[50];
    sprintf(game_time, "%d", game_timeLeft);

    setcolor(BROWN);
    outtextxy(maxx/2 + 300, maxy - 950, game_time);

    if(game_timeLeft == 0)
    {
        restart();
    }
    else
    {
        game_timeLeft = game_timeLeft -1;
    }

}
void restart()
{
    char res;
    outtextxy(maxx/2, maxy/2, "GAME OVER");
    res = getch();
    if(res == 'r')
    {
        game_restart_adjust();

    }
}
void score()
{

    sprintf(scoreWriter, "%d", game_score);
    setcolor(CYAN);
    outtextxy(maxx/2 + 100, maxy - 950, "score:");
    outtextxy(maxx/2 + 200, maxy - 950, scoreWriter);


}
void game_restart_adjust()
{
        health = 6;
        game_score = 0;
        game_timeLeft = 3000;

        leftC = 400;
        rightC = 600;
        i = maxy - 70;
        j = 500;



        cleardevice();

        initial();
}
void highScoreSaver()
{
    char name[50];
    char userName[20];
    char c;
    int n = 0;
    int nameX = maxx/2 - 100;
    int nameY = maxy/2;
    int xIncrease = 0;
    int score;
    int fileLineNumber = 0;
    int x = 0;
    int y = 0;



    FILE *fp;
    //fp = fopen("C:\\Users\\Guest1\\Desktop\\emir code\\DXBALL_Grafik\\grafik_230921\\recordList.txt", "r");
    fp = fopen("recordList.txt", "r");

    while(fscanf(fp, "%s\t%d\n", name, &score) != EOF)
    {
        fileLineNumber++;

        if(game_score > score)
        {
            cleardevice();
            settextstyle(2,1,10);
            setcolor(WHITE);
            outtextxy(maxx/2 - 250, maxy/2 - 250, "NEW HIGHEST SCORE");
            bar(maxx/2 - 200, maxy/2 - 200, maxx/2 - 180, maxy/2 + 200); //sol
            bar(maxx/2 + 200, maxy/2 - 200, maxx/2 + 180, maxy/2 + 200); //sag
            bar(maxx/2 - 200, maxy/2 - 200, maxx/2 + 200, maxy/2 - 180); //yukari
            bar(maxx/2 - 200, maxy/2 + 180, maxx/2 + 200, maxy/2 + 200); //asağı
            settextstyle(2,1,8);
            outtextxy(maxx/2 - 150, maxy/2 - 50, "your score: ");
            outtextxy(maxx/2 , maxy/2 - 50, scoreWriter);
            outtextxy(maxx/2 - 150, maxy/2 - 30, "Enter your name: ");
            x = 1;
            y = 1;

        }

    }

    if(fileLineNumber < 5 && x == 0)
    {
        cleardevice();
        settextstyle(2,1,10);
        setcolor(WHITE);
        outtextxy(maxx/2 - 250, maxy/2 - 250, "NEW TOP 5 SCORE");
        bar(maxx/2 - 200, maxy/2 - 200, maxx/2 - 180, maxy/2 + 200); //sol
        bar(maxx/2 + 200, maxy/2 - 200, maxx/2 + 180, maxy/2 + 200); //sag
        bar(maxx/2 - 200, maxy/2 - 200, maxx/2 + 200, maxy/2 - 180); //yukari
        bar(maxx/2 - 200, maxy/2 + 180, maxx/2 + 200, maxy/2 + 200); //asağı
        settextstyle(2,1,8);
        outtextxy(maxx/2 - 150, maxy/2 - 50, "your score: ");
        outtextxy(maxx/2 , maxy/2 - 50, scoreWriter);
        outtextxy(maxx/2 - 150, maxy/2 - 30, "Enter your name: ");

        y = 1;
    }
    fclose(fp);


    if(y == 1)
    {
        while(c != '\r')
        {
            c = getch();

            if(c == '\b')     // DELETE LETTER 'backspace'
            {
                nameX -= 20;
                xIncrease -= 20;

                setfillstyle(1, WHITE);
                bar(maxx/2 - 80 + xIncrease, maxy/2 + 10, maxx/2 - 78 + xIncrease, maxy/2 + 20);
                delay(100);
                setfillstyle(1, BLACK);
                bar(maxx/2 - 80 + xIncrease, maxy/2 + 10, maxx/2 - 78 + xIncrease, maxy/2 + 20);
                setfillstyle(1, BLACK);
                bar(maxx/2 - 100 + xIncrease, maxy/2 , maxx/2 - 80 + xIncrease, maxy/2 + 30);
                n--;
                userName[n] = NULL;

            }
            else if(c != '\r')     // LETTER WRITING
            {
                setfillstyle(1, WHITE);
                bar(maxx/2 - 80 + xIncrease, maxy/2 + 10, maxx/2 - 78 + xIncrease, maxy/2 + 20);
                delay(100);
                setfillstyle(1, BLACK);
                bar(maxx/2 - 80 + xIncrease, maxy/2 + 10, maxx/2 - 78 + xIncrease, maxy/2 + 20);
                if(c != '\0')
                userName[n] = c;
                sprintf(name, "%c", c);
                settextstyle(8,0,3);
                outtextxy(nameX, nameY, name);
                nameX += 20;
                xIncrease += 20;
                n++;

            }
            if(c == '\r')     // SAVE NICKNAME 'enter'
            {
                cleardevice();
                int a = 0;
                int n = 0;
                char cacheName[fileLineNumber][20];
                int cacheScore[fileLineNumber];

                int tempScore;
                char tempName[50];
                int score;
                char fileLine[BUFF_SIZE];

                FILE *fp;
                //fp = fopen("C:\\Users\\Guest1\\Desktop\\emir code\\DXBALL_Grafik\\grafik_230921\\recordList.txt","r");
                fp = fopen("recordList.txt","r");


                while(fscanf(fp, "%s\t%d\n", name, &score) != EOF)
                {
                    cacheScore[n] = score;
                    sprintf(cacheName[n], name);

                    n++;
                    if(a == 0)
                    {
                        sprintf(cacheName[n], userName);    // userName TO cacheName[n] ASSIGNMENT
                        cacheScore[n] = game_score;

                        n++;
                        a = 1;

                    }
                }
                fclose(fp);


                int k = 0;
                int done = 0;
                while(start != false)                                 // COMPARE THE SCORS
                {
                    if(cacheScore[k] < cacheScore[k+1])
                    {
                        tempScore = cacheScore[k];
                        sprintf(tempName, cacheName[k]);

                        cacheScore[k] = cacheScore[k+1];
                        sprintf(cacheName[k], cacheName[k+1]);

                        cacheScore[k+1] = tempScore;
                        sprintf(cacheName[k+1], tempName);

                        k++;
                        done = 0;
                    }
                    else
                    {
                        k++;
                        done++;
                        if(done == fileLineNumber)
                        {
                            start = false;
                        }

                    }
                    if(k == fileLineNumber)
                    {
                        k = 0;
                    }

                    //printf("1. = %d name= %s\n", cacheScore[0], cacheName[0]);
                    //printf("2. = %d name= %s\n", cacheScore[1], cacheName[1]);
                    //printf("3. = %d name= %s\n", cacheScore[2], cacheName[2]);
                    //printf("4. = %d name= %s\n", cacheScore[3], cacheName[3]);
                    //printf("5. = %d name= %s\n", cacheScore[4], cacheName[4]);


                }
                int m = 0;
                //remove("C:\\Users\\Guest1\\Desktop\\emir code\\DXBALL_Grafik\\grafik_230921\\recordList.txt");
                remove("recordList.txt");
                FILE *fp1;
                //fp1 = fopen("C:\\Users\\Guest1\\Desktop\\emir code\\DXBALL_Grafik\\grafik_230921\\recordList.txt", "a");
                fp1 = fopen("recordList.txt", "a");


                if(n>5)
                {
                    n = 5;
                }
                for(i=0; i<n; i++)
                {
                    fprintf(fp1, "%s\t%d\n", cacheName[m], cacheScore[m]);
                    m++;
                }
                fclose(fp1);

            }
        }
    }
}
void scoreIncrease()
{
    game_score = game_score + 100;
}
int middleOfTheBoard()
{
    int middleOfTheBoard;
    middleOfTheBoard = leftC + (rightC - leftC)/2;
    return middleOfTheBoard;
}




