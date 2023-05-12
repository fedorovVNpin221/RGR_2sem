#include <iostream>     
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;
int KeyNum = 0, Point = 0;
double A = 1.0, B = 10.0, N = 300;
const int screenWidth = 147;
const int screenHeight = 45;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setFontSize(int size)
{
    CONSOLE_FONT_INFOEX info = { 0 };
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = size; 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
}
void gotoxy(short x, short y)
{
    COORD Coor;
    Coor.X = x; Coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor);
}
void fullscreen()
{
    keybd_event(VK_MENU, 0x38, 0, 0); 
    keybd_event(VK_RETURN, 0x1c, 0, 0); 
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0); 
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); 
}
void OffCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void scrollbarsoff() {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
    COORD new_screen_buffer_size;
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
        screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
        screenBufferInfo.srWindow.Top + 1; // Rows
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

void tablemaxminfunc(double value, int colorcode) {
    SetConsoleTextAttribute(hStdOut, colorcode);
    printf("%11f", value);
    SetConsoleTextAttribute(hStdOut, 11);
}
void tablelinefunc(int linesym, int midsym, int opensymbol, int lastsym)
{
    printf("%c", opensymbol);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            printf("%c", linesym);
        }
        if (i != 3)
            printf("%c", midsym);
    }
    printf("%c\n", lastsym);
}
double equalization(double x)
{
    return pow(2, x)-3*x-2;
}
void chordmethod()
{
    double A = 0, B = 2, e = 0.001;
    while (abs(B - A) > e)
    {
        A = (A - (B - A) * equalization(A) / (equalization(B) - equalization(A)));
        B = (B - (A - B) * equalization(B) / (equalization(A) - equalization(B)));
    }
    cout << B;
}
double integral(double x)
{
    return (atan(x)*atan(x))/x;
}
void trapezoidalIntegral()
{
    double h = (B - A) / N;
    double trapezoidal_integral = 0;
    for (int i = 0; i < N; i++)
    {
        const double x1 = A + i * h;
        const double x2 = A + (i + 1) * h;
        trapezoidal_integral += 0.5 * (x2 - x1) * (integral(x1) + integral(x2));
    }
    cout << trapezoidal_integral;
}
void rectangelIntegral()
{
    double h = (B - A) / N;
    double rectangel_integral = 0;
    for (double x = A; x <= B; x += h)
    {
        rectangel_integral += integral(x - h / 2);
    }
    rectangel_integral *= h;
    cout << rectangel_integral;
}
void drawmenu()
{
    switch (KeyNum)
    {
    case 80: // стрелка вниз
        if (Point >= 7) Point = 1;
        else Point++;
        break;
    case 72: // стрелка вверх
        if (Point <= 1) Point = 7;
        else Point--;
        break;
    default:
        break;
    }
    system("cls");
    OffCursor();
    gotoxy(67, 17);
    if (Point == 1)
    {
        gotoxy(60, 17);
        printf(" Таблица <--\n");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 17);
        printf("  Таблица\n");
        gotoxy(0, 0);
    }
    if (Point == 2)
    {
        gotoxy(60, 19);
        printf(" График <--\n");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 19);
        printf("  График\n");
        gotoxy(0, 0);
    }
    if (Point == 3)
    {
        gotoxy(60, 21);
        printf(" Уравнение <--\n");
        gotoxy(0, 0);
    }
    else
    {

        gotoxy(60, 21);
        printf("  Уравнение\n");
        gotoxy(0, 0);
    }
    if (Point == 4)
    {
        gotoxy(60, 23);
        printf(" Интеграл <--\n");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 23);
        printf("  Интеграл\n");
        gotoxy(0, 0);
    }
    if (Point == 5)
    {
        gotoxy(60, 25);
        printf(" Об авторе <--\n");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 25);
        printf("  Об авторе\n");
        gotoxy(0, 0);
    }
    if (Point == 6)
    {
        gotoxy(60, 27);
        printf(" Анимация <--");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 27);
        printf("  Анимация");
        gotoxy(0, 0);
    }
    if (Point == 7)
    {
        gotoxy(60, 29);
        printf(" Выход <--\n");
        gotoxy(0, 0);
    }
    else
    {
        gotoxy(60, 29);
        printf("  Выход\n");
        gotoxy(0, 0);
    }
}
void drawtable()
{
    system("cls");
    setlocale(LC_ALL, "C");
    double a = -2, b = 2, x = -2, n = 14, dx, f1, f2;
    double minF1 = INT_MAX, maxF1 = INT_MIN, minF2 = INT_MAX, maxF2 = INT_MIN;
    double functionarr[3][20]; int countarr[20];
    int count = 1, opensym, linesym, midsym, lastsym;
    dx = abs(b - a) / (n - 1);
    tablelinefunc(linesym = 205, midsym = 203, opensym = 201, lastsym = 187);
    printf("%c%s%c%s%c", 186, "  Step #N  ", 186, "Function #1", 186);
    printf("%s%c%s%c\n", "Function #2", 186, "  X value  ", 186);
    for (int i = 0; i < n; i++)
    {
        f1 = exp(-(x+5));
        f2 = (x-1)*(x-1)*(x-1);
        functionarr[1][i] = f2; functionarr[0][i] = f1; functionarr[2][i] = x;
        countarr[i] = count; x += dx; count++;
        minF1 = min(functionarr[0][i], minF1); maxF1 = max(functionarr[0][i], maxF1);
        minF2 = min(functionarr[1][i], minF2); maxF2 = max(functionarr[1][i], maxF2);
    }
    for (int i = 0; i < n; i++)
    {
        tablelinefunc(linesym = 205, midsym = 206, opensym = 204, lastsym = 185);
        printf("%c%11d%c", 186, countarr[i], 186);
        if (functionarr[0][i] != maxF1 && functionarr[0][i] != minF1)
            printf("%11f", functionarr[0][i]);
        else if (functionarr[0][i] == maxF1)
            tablemaxminfunc(functionarr[0][i], 2);
        else if (functionarr[0][i] == minF1)
            tablemaxminfunc(functionarr[0][i], 4);
        printf("%c%", 186);
        if (functionarr[1][i] != maxF2 && functionarr[1][i] != minF2)
            printf("%11f", functionarr[1][i]);
        else if (functionarr[1][i] == maxF2)
            tablemaxminfunc(functionarr[1][i], 2);
        else if (functionarr[1][i] == minF2)
            tablemaxminfunc(functionarr[1][i], 4);
        printf("%c%11f%c\n", 186, functionarr[2][i], 186);
    }
    tablelinefunc(linesym = 205, midsym = 202, opensym = 200, lastsym = 188); setlocale(LC_ALL, "rus");
    gotoxy(50, 0); cout << "Таблица итераций:"; gotoxy(50, 1);
    cout << "В таблице представлены значений итераций"; gotoxy(50, 2);
    cout << "Данных функций:"; gotoxy(50, 3); cout << "Функция №1: e^(-(x+5))";
    gotoxy(50, 4); cout << "Функция №2: (x-1)^3"; gotoxy(50, 5);
    cout << "Интервал функций: [-2, 2]"; gotoxy(50, 6);
    cout << "Красным цветом отмечены минимальные значения функций"; gotoxy(50, 7);
    cout << "Зеленым цветом отмечены максимальные значения функций";
}
void drawgraph()
{
    system("cls");
    HWND hwn = GetConsoleWindow();
    COLORREF lineColor = RGB(0, 0, 0);
    HDC hdc = GetDC(hwn);
    const int d = 500, k = 125, x0 = 520, y0 = 500, c = 520, n = 40000;
    double F1[n], F2[n], x1[n], x, dx, a = -2, b = 2, minF1 = 20000, maxF1 = -20000, minF2 = 20000, maxF2 = -20000;
    dx = fabs(b - a) / (n - 1);
    x = a;
    for (int i = 0; i < n; i++) { 
        F1[i] = exp(-(5 + x)); 
        F2[i] = (x - 1) * (x - 1) * (x - 1);
        x1[i] = x;
        x += dx;
    }
    for (int i = 0; i < n; i++) {
        SetPixel(hdc, c + k * x1[i], d - k * F2[i], RGB(64, 224, 208));
        MoveToEx(hdc, c + k * x1[i], d - k * F2[i], NULL);
        SetPixel(hdc, c + k * x1[i], d - k * F1[i], RGB(0, 255, 127));
        MoveToEx(hdc, c + k * x1[i], d - k * F1[i], NULL);
    }
    SelectObject(hdc, CreatePen(0, 1, RGB(255, 255, 255)));
    MoveToEx(hdc, 0, d, NULL);
    LineTo(hdc, c * k, d);
    MoveToEx(hdc, c, 0, NULL);
    LineTo(hdc, c, 3 * d);
    for (int i = -4; i < 30; i++) {
        MoveToEx(hdc, x0 - 10, y0 - k * i, NULL);
        LineTo(hdc, x0 + 10, y0 - k * i);
        MoveToEx(hdc, x0 - 10, y0 + k * i, NULL);
        LineTo(hdc, x0 + 10, y0 + k * i);
        MoveToEx(hdc, x0 + k * i, y0 - 10, NULL);
        LineTo(hdc, x0 + k * i, y0 + 10);
        MoveToEx(hdc, x0 - k * i, y0 - 10, NULL);
        LineTo(hdc, x0 - k * i, y0 + 10);
        string s = to_string(i);
        LPCWSTR w;
        wstring ste = wstring(s.begin(), s.end());
        w = ste.c_str();
        if (i < 10) {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 2);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 2);
        }
        else {
            TextOut(hdc, x0 - 10, y0 - k * i, w, 2);
            TextOut(hdc, x0 + k * i, y0 + 10, w, 2);
        }
        LPCWSTR w1 = L"e^(-(x+5))";
        LPCWSTR w2 = L"(x-1)^3";
        TextOut(hdc, 650, 350, w1, 11);
        TextOut(hdc, 300, 450, w2, 9);
    }
}
void drawequation()
{
    system("cls");
    cout << "Нахождение корня уравнения:\n";
    cout << "Уравнение: 2^x - 3x - 2 \n";
    cout << "Интервал решения уравнения: [0, 2]\n";
    cout << "Результат решения уравнения методом хорд: "; chordmethod();;
}
void drawintegral()
{
    system("cls");
    cout << "Вычисление определенного интеграла\n";
    cout << "Предложенный интеграл: ((arctg(x))^2)/x\n";
    cout << "Верхний предел интеграла: 10.0\n";
    cout << "Нижний предел интеграла: 1.0\n";
    cout << "Результат, полученный методом трапеций равен: ";
    trapezoidalIntegral();
    cout << "\nРезультат, полученный методом прямоугольников равен: ";
    rectangelIntegral();
}
void drawauthor()
{
    system("cls");
    gotoxy(49, 18);
    printf("Расчетно - графическая работа по программированию\n");
    gotoxy(36, 20);
    printf("Работу выполнил студент Омского государственного технического университета\n");
    gotoxy(36, 22);
    printf("Факультет информационных технологий и компьютерных систем, группа: ПИН-221\n");
    gotoxy(58, 24);
    printf("Федоров Вячеслав Николаевич\n");
    gotoxy(71, 26);
    printf("2023\n");
}
void drawNumbers()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = { 80, 50 }; 
    SetConsoleScreenBufferSize(console, size);
    srand(time(NULL));
    int lines[15][10];
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            lines[i][j] = rand() % 10;
        }
    }
    int currentPos = 0;
    while (!_kbhit())
    {
        system("cls");
        for (int i = 0; i < 15; i++)
        {
            COORD pos = { 0, currentPos + i };
            SetConsoleCursorPosition(console, pos);
            for (int j = 0; j < 10; j++)
            {
                cout << lines[i][j] << " ";
            }
        }
        currentPos++;
        if (currentPos > 50)
        {
            currentPos = 0;
        }
        Sleep(50);
    }
}
void drawanimation()
{
    system("cls");
    while (!_kbhit())
    {
        drawNumbers();
        Sleep(13);
        system("cls");
    }
}
void drawquit()
{
    exit(0); 
}

int main()
{
    fullscreen();
    setFontSize(24);
    system("color B");
    setlocale(LC_ALL, "rus");
    scrollbarsoff();
    drawmenu();
    while (true)
    {
        KeyNum = _getch();
        drawmenu();
        if (KeyNum == 13)
        {
            switch (Point)
            {
            case 1:
            {
                drawtable();
                break;
            }
            case 2:
            {
                drawgraph();
                break;
            }
            case 3:
            {
                drawequation();
                break;
            }
            case 4:
            {
                drawintegral();
                break;
            }
            case 5:
            {
                drawauthor();
                break;
            }
            case 6:
            {
                drawanimation();
                break;

            }
            case 7:
            {
                drawquit();
                break;
            }
            default:
                break;
            }
        }
    }
}