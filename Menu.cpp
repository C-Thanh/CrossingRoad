#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <thread>
#pragma comment(lib, "Winmm.lib")
// compile by this code: g++ Menu.cpp -o Menu.exe -lWinmm
using namespace std;
void moveToXY(int x, int y)
{
    COORD cursor;
    cursor.X = x;
    cursor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
void color(int backgroundColor, int text_color)
{
    int wColor = backgroundColor * 16 + text_color; // 16*16 + 0
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void playMenuMusic();
thread music(playMenuMusic);
class Menu
{
    int x, y;
    int counter, hoverColor, defaultColor, background_color;

public:
    Menu(int PosX, int PosY, int hoverColor_, int TextColor, int backgroundColor_)
    {
        x = PosX;
        y = PosY;
        counter = 1;
        hoverColor = hoverColor_;
        defaultColor = TextColor;
        background_color = backgroundColor_;
    }
    void drawMenu();
    void drawMenuPlay();
    void drawMenuOption();
};
void Menu::drawMenuOption()
{
    int set[] = {7, 7};
    char key;
    while (true)
    {
        moveToXY(x, y);
        color(background_color, set[0]);
        cout << "1.Turn off music";

        moveToXY(x, y + 1);
        color(background_color, set[1]);
        cout << "2.Back to Menu";

        moveToXY(x, y + 2);
        cout << "               ";

        key = getch();
        if (key == 'w' && counter > 1)
            counter--;
        if (key == 's' && counter < 2)
            counter++;
        if (GetAsyncKeyState('\r'))
        {
            if (counter == 1)
            {
                moveToXY(x + 12, y);
                goto choice;
            }
            if (counter == 2)
                goto choice;
        }

        if (counter == 1)
            set[0] = hoverColor;
        else
            set[0] = defaultColor;

        if (counter == 2)
            set[1] = hoverColor;
        else
            set[1] = defaultColor;
    }
choice:
    if (counter == 1)
    {
        cout << "Music is off :>";
        moveToXY(x, y);
        cout << "               ";
        music.detach();
    }
    else
        drawMenu();
}
void Menu::drawMenuPlay()
{
    int set[] = {3, 3, 3};
    char key;
    while (true)
    {
        moveToXY(x, y);
        color(background_color, set[0]);
        cout << "1.New Game ";

        moveToXY(x, y + 1);
        color(background_color, set[1]);
        cout << "2.Load Game";

        moveToXY(x, y + 2);
        color(background_color, set[2]);
        cout << "3.Back to Menu";

        key = getch();
        if (key == 'w' && counter > 1)
            counter--;
        if (key == 's' && counter < 3)
            counter++;
        if (GetAsyncKeyState('Q'))
            break;
        if (GetAsyncKeyState('\r'))
        {
            if (counter == 1)
                moveToXY(x + 12, y);
            if (counter == 2)
                moveToXY(x + 12, y + 1);
            if (counter == 3)
            {
                goto choice;
            }
            cout << " Event " << counter << " occur ";
        }

        if (counter == 1)
            set[0] = hoverColor;
        else
            set[0] = defaultColor;

        if (counter == 2)
            set[1] = hoverColor;
        else
            set[1] = defaultColor;

        if (counter == 3)
            set[2] = hoverColor;
        else
            set[2] = defaultColor;
    }
choice:
    if (counter == 1)
        cout << "PLAY GAME";
    if (counter == 2)
        cout << "LOAD GAME";
    else
        drawMenu();
}

void Menu::drawMenu()
{
    int set[] = {3, 3, 3};
    char key;
    while (true)
    {
        moveToXY(x, y);
        color(background_color, set[0]);
        cout << "1.Play Game       ";

        moveToXY(x, y + 1);
        color(background_color, set[1]);
        cout << "2.Option      ";

        moveToXY(x, y + 2);
        color(background_color, set[2]);
        cout << "3.Quit        ";

        key = getch();
        if (key == 'w' && counter > 1)
            counter--;
        if (key == 's' && counter < 3)
            counter++;

        // I dont know why but GetKeyState seem to be much more sensitive :3
        // if (GetKeyState('W') & 0x8000 && counter > 1)
        //     counter--;
        // if (GetKeyState('S') & 0x8000 && counter < 3)
        //     counter++;

        if (GetAsyncKeyState('Q'))
            break;
        if (GetAsyncKeyState('\r'))
        {
            break;
            // if (counter == 1)
            // {
            //     goto choice;
            // }
            // if (counter == 2)
            // {
            //     goto choice;
            // }
            // if (counter == 3)
            // {
            //     moveToXY(x + 12, y + 2);
            //     break;
            // }
            // cout << " Event " << counter << " occur ";
        }

        if (counter == 1)
            set[0] = hoverColor;
        else
            set[0] = defaultColor;

        if (counter == 2)
            set[1] = hoverColor;
        else
            set[1] = defaultColor;

        if (counter == 3)
            set[2] = hoverColor;
        else
            set[2] = defaultColor;
    }
choice:
    if (counter == 1)
        drawMenuPlay();
    if (counter == 2)
    {
        moveToXY(x, y + 2);
        cout << "           ";
        drawMenuOption();
    }
    music.detach();
}
void SetWindowSize(int height, int width)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void noCursor()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void playMenuMusic()
{
    // you can choose any of them, but remember to link -lWinmm
    // PlaySound(TEXT("D:\\COLLEGE\\Object-Oriented-Programming\\Self_practice\\BlueDream.wav"), NULL, SND_SYNC);
    // PlaySound(TEXT("Music/BlueDream.wav"), NULL, SND_LOOP);
}
void SetFontAttribute() // used to design the font of the text
{
    CONSOLE_FONT_INFOEX letter;
    letter.cbSize = sizeof(letter);
    letter.nFont = 0;
    letter.dwFontSize.X = 0;  // Width of each character in the font
    letter.dwFontSize.Y = 24; // Height
    letter.FontFamily = FF_DONTCARE;
    letter.FontWeight = FW_NORMAL;
    wcscpy(letter.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &letter);
}
int main()
{
    int SCREEN_WIDTH = 110, SCREEN_HEIGHT = 60;
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetConsoleTitle(TEXT("My Game Menu"));
    SetFontAttribute();
    int x = 30, y = 10;
    Menu *GAME = new Menu(x, y, 2, 0, 15);
    system("color f0"); // remember to change this color too, its the whole background color
    noCursor();

    thread UI(&Menu::drawMenu, *GAME); // require a pointer to member function, an object, parameters (maybe)
    //music.join();
    UI.join();
    system("pause");
}
