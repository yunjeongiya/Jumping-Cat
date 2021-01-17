//참고: https://github.com/BlockDMask/Google_Dino.git

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define HURDLE_Y 14
#define HURDLE_startX 52
#define BOTTOM 14

void Goto(int x, int y);
void Color(unsigned short text, unsigned short back);
void RunningCat(int CatY);
void JumpingCat(int CatY);
void LandingCat(int CatY);
void Hurdle(int HurdleX);
int crash(const int HurdleX, const int CatY);
int Level();
int GetKey();
int GameOver(const int score);

int main(void)
{
    system("mode con:cols=60 lines=20"); //콘솔창 크기 설정
    int gameplay = 1;
    while (gameplay)
    {
        int level = Level();
        int isJumping = 0;
        int isBottom = 1;
        const int updown = 1;
        int CatY = BOTTOM; //고양이는 바닥에서 출발
        int HurdleX = HURDLE_startX;
        int score = 0;
        while (1)
        {
            int speed = 100 - 10 * level; //빠르기 입력받기
            if (crash(HurdleX, CatY)) //충돌 시 반복 종료
                break;
            Goto(21, 1);
            //printf("허들X %d, 고양이Y: %d, 점수:%d", HurdleX, CatY, score); 높이 확인용
            printf("[ level:%d, score:%d ]", level, score);
            Color(15, 0);
            if (GetKey() == ' ' && isBottom)
            {
                isJumping = 1;
                isBottom = 0;
            }

            if (isJumping)
            {
                CatY -= updown;
            }
            else
            {
                CatY += updown;
            }
            if (CatY >= BOTTOM) //바닥 밑으로 내려가지 못하게 함
            {
                CatY = BOTTOM;
                isBottom = 1;
            }
            if (CatY <= 5)
                isJumping = 0;

            //고양이 액션
            if (isJumping)
                JumpingCat(CatY);
            else
            {
                if (isBottom)
                    RunningCat(CatY);
                else
                    LandingCat(CatY);
            }

            //뜀틀 지나가기
            HurdleX -= 2;
            if (HurdleX <= 0)
            {
                HurdleX = HURDLE_startX;
                score++; //하나 통과할 때마다 점수 추가
                if (score % 5 == 0 && score > 0 && level < 10) //점수 추가 시 5점마다 레벨업
                    level++;
            }
            Hurdle(HurdleX);

            Sleep(speed);
            system("cls"); //콘솔창 내용 지우기

        }
        gameplay = GameOver(score);
    }
    return 0;
}

//커서위치 이동
void Goto(int x, int y)
{
    COORD Pos;
    Pos.X = x; //가로 2칸 길이 = 세로 1줄 길이
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//색상 결정
void Color(unsigned short text, unsigned short back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

//고양이 등장
/*
13칸(여백5칸)*5줄
  ∧,,∧
∩- ω - ）　
|　　 ⊂ﾉ
|　　 _⊃
し ⌒

  ∧,,∧
 (- ω - ∩
  t⊃　　｜
 ⊂_ 　　｜
     ⌒ J
*/
void RunningCat(int CatY)
{
    Goto(0, CatY);
    static int cat_action = 1;
    if (cat_action)
    {
        printf("       ∧,,∧  \n");
        printf("     ∩- ω - )\n");
        printf("     |　　 ⊂/ \n");
        printf("     |　　 _⊃ \n");
        printf("     し ⌒     \n");
        Sleep(0);
        cat_action = 0;
    }
    else
    {
        printf("       ∧,,∧  \n");
        printf("     (- ω - ∩\n");
        printf("      t⊃　　｜\n");
        printf("     ⊂_ 　　｜\n");
        printf("          ⌒ J \n");
        Sleep(0);
        cat_action = 1;
    }

}

//고양이 점프
/*
 ∧,,∧
(> ω <)　웃챠 ~~
⊂∪∪⊃
   ..
   ﾉﾉ
*/
void JumpingCat(int CatY)
{
    Goto(0, CatY);
    printf("      ∧,,∧          \n");
    printf("     (> ω <)　웃챠 ~~\n");
    printf("     ⊂∪∪⊃         \n");
    printf("        ..            \n");
    printf("        J|            \n");
}

//고양이 착지
/*
 q      p
 |∧,,∧|
 (> ω <)
  |____|
  J    J
*/
void LandingCat(int CatY)
{
    Goto(0, CatY);
    printf("     q      p\n");
    printf("     |∧,,∧|\n");
    printf("     (> ω <)\n");
    printf("      |____| \n");
    printf("      J    J \n");
}


//뜀틀 등장
/*

8칸*5줄(말풍선 1줄)

    지나가요!!!
　 　 ∧_∧
　　(`+ω+´) 三
　　  O┳0 )
　　 ◎し◎- 三

*/
void Hurdle(int HurdleX)
{
    Goto(HurdleX, HURDLE_Y);
    printf(" 지나가요!!!\n");
    Goto(HurdleX, HURDLE_Y + 1);
    printf("  ∧_∧     \n");
    Goto(HurdleX, HURDLE_Y + 2);
    printf("(`+ω+´) 三\n");
    Goto(HurdleX, HURDLE_Y + 3);
    printf("  O┳0 )    \n");
    Goto(HurdleX, HURDLE_Y + 4);
    printf(" ◎し◎- 三\n");
}

//충돌
int crash(const int HurdleX, const int CatY)
{
    if (HurdleX <= 13 && CatY > 10)
    {
        return 1;
    }
    return 0;
}


//시작 레벨 입력
int Level()
{
    system("cls");
    int level = 0;
    Goto(15, 8);
    Color(7, 0);
    printf("         [Jumping Cat]        ");
    Goto(15, 11);
    Color(15, 0);
    printf("   *Press Spacebar to Jump*   ");
    Goto(15, 9);
    Color(7, 0);
    printf("Choose the Start Level (0~10) : ");
    scanf_s("%d", &level);

    return level;
}

//키보드입력
int GetKey()
{
    if (_kbhit() != 0)
        return _getch();
    return 0;
}

//게임끝
/*
.　｡・｡∧_∧｡・｡
｡ﾟ 　( ﾟ´Д｀)　 ﾟ｡
　　o( U   U
　　　'ｰ'ｰ'
*/
int GameOver(const int score)
{
    system("cls");
    Goto(19, 6);
    printf("====== GAME OVER =====");
    Goto(19, 7);
    printf("        ∧_∧  , * ,    ");
    Goto(19, 8);
    printf("   , * (ㅜДㅜ)      *. ");
    Goto(19, 9);
    printf("  *.  o(U_  U           ");
    Goto(19, 10);
    printf(" *      U 'J            ");
    Goto(19, 11);
    printf("====== SCORE: %d ======", score);
    Goto(18, 14);
    printf("Press Spacebar to Restart");

    while (1)
    {
        if (GetKey() == ' ')
            return 1;
        else
            continue;
    }
}