/* 2553825 卓20 权楷之 */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <climits>
#include "hanoi.h"
#include "cmd_console_tools.h"
#include "cmd_hdc_tools.h"
#include "hanoi_const_value.h"
using namespace std;

/* ----------------------------------------------------------------------------------

     本文件功能：
	1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int towers[3][MAX_LAYER] = { 0 };
static int top[3] = { -1, -1, -1 };
static int step = 1;
static int yanshi;

// (A-C)to(0-2)
int translate1(char a)
{
    return a - 'A';
}

// (0-2)to(A-C)
char translate2(int a)
{
    return 'A' + a;
}

//输出横向数组状态
void printarry()
{
    cout << " A:";
    for (int j = 0; j <= top[0]; j++)
    {
        cout << setw(2) << setiosflags(ios::right) << towers[0][j];
    }
    for (int j = top[0] + 1; j <= MAX_LAYER - 1; j++)
    {
        cout << "  ";
    }
    cout << " B:";
    for (int j = 0; j <= top[1]; j++)
    {
        cout << setw(2) << setiosflags(ios::right) << towers[1][j];
    }
    for (int j = top[1] + 1; j <= MAX_LAYER - 1; j++)
    {
        cout << "  ";
    }
    cout << " C:";
    for (int j = 0; j <= top[2]; j++)
    {
        cout << setw(2) << setiosflags(ios::right) << towers[2][j];
    }
    for (int j = top[2] + 1; j <= MAX_LAYER - 1; j++)
    {
        cout << "  ";
    }
    cout << endl;
}

//数组移动
void move(char src, char dst)
{
    src = translate1(src);
    dst = translate1(dst);
    int plate = towers[src][top[src]--];
    towers[dst][++top[dst]] = plate;
}
void back(char src, char dst)
{
    src = translate1(src);
    dst = translate1(dst);
    top[src]++;
    top[dst]--;
}

//移走数字
void cleantower(char src, char dst ,int choice)
{
    if (src == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 3 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[0]);
        cout << "  ";
    }
    else if (src == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1 + Underpan_Distance, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 3 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[1]);
        cout << "  ";
    }
    else if (src == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1 + 2 * Underpan_Distance, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 3 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[2]);
        cout << "  ";
    }
    if (dst == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[0]);
        cout << setw(2) << towers[0][top[0]];
    }
    else if (dst == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1 + Underpan_Distance, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[1]);
        cout << setw(2) << towers[1][top[1]];
    }
    else if (dst == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X - 1 + 2 * Underpan_Distance, MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2 + (choice / 8) * (MenuItem8_Start_Y - MenuItem4_Start_Y) - top[2]);
        cout << setw(2) << towers[2][top[2]];
    }
}
void cleantower8(char src, char dst, int choice)
{
    if (src == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 3 - top[0]);
        cout << "  ";
    }
    else if (src == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1 + Underpan_Distance, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 3 - top[1]);
        cout << "  ";
    }
    else if (src == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1 + 2 * Underpan_Distance, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 3 - top[2]);
        cout << "  ";
    }
    if (dst == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - top[0]);
        cout << setw(2) << towers[0][top[0]];
    }
    else if (dst == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1 + Underpan_Distance, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - top[1]);
        cout << setw(2) << towers[1][top[1]];
    }
    else if (dst == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X - 1 + 2 * Underpan_Distance, MenuItem8_Start_Y + Underpan_A_Y_OFFSET - 2 - top[2]);
        cout << setw(2) << towers[2][top[2]];
    }
}
void cleantower9(char src, char dst, int choice)
{
    if (src == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 3 - top[0]);
        cout << "  ";
    }
    else if (src == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1 + Underpan_Distance, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 3 - top[1]);
        cout << "  ";
    }
    else if (src == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1 + 2 * Underpan_Distance, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 3 - top[2]);
        cout << "  ";
    }
    if (dst == 'A')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 2 - top[0]);
        cout << setw(2) << towers[0][top[0]];
    }
    else if (dst == 'B')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1 + Underpan_Distance, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 2 - top[1]);
        cout << setw(2) << towers[1][top[1]];
    }
    else if (dst == 'C')
    {
        cct_gotoxy(Underpan_A_X_OFFSET + MenuItem9_Start_X - 1 + 2 * Underpan_Distance, MenuItem9_Start_Y + Underpan_A_Y_OFFSET - 2 - top[2]);
        cout << setw(2) << towers[2][top[2]];
    }
}

//延时
void sleeptime(int yanshi)
{
    if (yanshi == 0)
    {
        while (_getch() != 13);
    }
    else if(yanshi==-1)
    {
        Sleep(0);
    }
    else
    {
        Sleep(yanshi);
    }
    return;
}

//重置
void reset() 
{
    for (int i = 0; i < 3; i++)
    {
        top[i] = { -1 };
        for (int j = 0; j < MAX_LAYER; j++)
        {
            towers[i][j] = { 0 };
        }
    }
    step = 1;
}

//纵向数组打印
void print4(int n, char src, char tmp, char dst, int yanshi)
{
    int x = Underpan_A_X_OFFSET + MenuItem4_Start_X - 1 + (int(src) - int('A')) * Underpan_Distance;
    int y = MenuItem4_Start_Y + Underpan_A_Y_OFFSET - 2;
    int t = n;
    int s = n;
    int length = 2 * Underpan_Distance + 5;
    cct_cls();
    cct_gotoxy(Underpan_A_X_OFFSET + MenuItem4_Start_X-2, MenuItem4_Start_Y + Underpan_A_Y_OFFSET-1);
    cout << setw(length) << setfill('=') << "=" << setfill(' ') << endl;
    cct_gotoxy(Underpan_A_X_OFFSET+ MenuItem4_Start_X, MenuItem4_Start_Y+ Underpan_A_Y_OFFSET);
    cout << "A" << setw(Underpan_Distance) << "B" << setw(Underpan_Distance) << "C";
    cct_gotoxy(x, y);
    for (int i = 0; i < t; i++)
    {
        cout << setw(2) << s--;
        cct_gotoxy(x, --y);
    }
    cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
    cout << "初始: ";
    printarry();
    cct_gotoxy(Status_Line_X, Status_Line_Y);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层，延时设置为 " << yanshi << "ms";
    sleeptime(yanshi);
    return;
}
void print7(int n, char src, char tmp, char dst, int yanshi, int choice)
{
    cct_gotoxy(Status_Line_X, Status_Line_Y);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层" << endl;
    return;
}
void print89(int n, char src, char tmp, char dst, int yanshi ,int choice)
{
    int x = Underpan_A_X_OFFSET + MenuItem8_Start_X - 1 + (int(src) - int('A')) * Underpan_Distance;
    int y = Underpan_A_Y_OFFSET + MenuItem8_Start_Y - 2;
    int t = n;
    int s = n;
    int length = 2 * Underpan_Distance + 5;
    cct_cls();
    cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X-2, Underpan_A_Y_OFFSET + MenuItem8_Start_Y-1);
    cout << setw(length) << setfill('=') << "=" << setfill(' ') << endl;
    cct_gotoxy(Underpan_A_X_OFFSET + MenuItem8_Start_X, Underpan_A_Y_OFFSET+ MenuItem8_Start_Y);
    cout << "A" << setw(Underpan_Distance) << "B" << setw(Underpan_Distance) << "C";
    cct_gotoxy(x, y);
    for (int i = 0; i < t; i++)
    {
        cout << setw(2) << s--;
        cct_gotoxy(x, --y);
    }
    cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
    cout << "初始: ";
    printarry();
    cct_gotoxy(Status_Line_X, Status_Line_Y);
    cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
    if (choice == 8)
    {
        cout << "，延时设置为 " << yanshi << "ms（前7步，后面自动变为0ms）";
    }
    return;
}


void end()
{
    cout << endl << "按回车键继续";
    while (getchar() != '\n');
    return;
}

//盘子竖直移动（上升）
void plate_move_up(char src, int yanshi)
{
    int a = translate1(src);
    int plate_number = towers[a][top[a]];//盘子宽度对应HDC_Base_Width的倍数
    int middle_x = HDC_Start_X + a * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (23 * HDC_Base_Width) / 2;
    int plate_width = (2 * plate_number + 1) * HDC_Base_Width; // 盘子总宽度
    int plate_height = HDC_Base_High;                         // 盘子总高度

    //盘子初始位置
    int plate_top_y = HDC_Start_Y - (top[a] + 1) * plate_height; //盘子顶Y
    int plate_bottom_y = plate_top_y + plate_height;             //盘子底Y
    int plate_end_y = HDC_Top_Y;                                 //移动终止Y

    //柱子
    int pole_x = middle_x - HDC_Base_Width / 2;        // 柱子左上角X
    int pole_top_y = HDC_Start_Y - 12 * HDC_Base_High; // 柱子顶部Y

    while (plate_top_y > plate_end_y)
    {
        hdc_rectangle(middle_x - plate_width / 2, plate_bottom_y - HDC_Step_Y, plate_width, HDC_Step_Y, HDC_COLOR[0]);

        plate_top_y -= HDC_Step_Y;
        plate_bottom_y -= HDC_Step_Y;
        hdc_rectangle(middle_x - plate_width / 2, plate_top_y, plate_width, HDC_Step_Y, HDC_COLOR[plate_number]);

        if (plate_bottom_y >= pole_top_y)
        {
            hdc_rectangle(pole_x, plate_bottom_y, HDC_Base_Width, HDC_Step_Y, HDC_COLOR[11]);
        }
        sleeptime(yanshi);
    }
    return;
}

//盘子竖直移动（下移）
void plate_move_drop(char src, char dst, int yanshi)
{
    int a = translate1(src);
    int b = translate1(dst);

    int plate_number = towers[a][top[a]];
    //目标柱子中心X坐标
    int middle_x = HDC_Start_X + b * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (23 * HDC_Base_Width) / 2;
    int plate_width = (2 * plate_number + 1) * HDC_Base_Width; //盘子宽度
    int plate_height = HDC_Base_High;                         //盘子高度

    //初始/终止位置
    int plate_top_y = HDC_Top_Y;
    int plate_bottom_y = plate_top_y + plate_height;
    //盘子落到栈顶上方
    int plate_end_y = HDC_Start_Y - (top[b] + 2) * plate_height;
    int pole_x = middle_x - HDC_Base_Width / 2;        // 柱子左上角X
    int pole_top_y = HDC_Start_Y - 12 * HDC_Base_High; // 柱子顶部Y

    while (plate_top_y < plate_end_y)
    {
        hdc_rectangle(middle_x - plate_width / 2, plate_top_y, plate_width, HDC_Step_Y, HDC_COLOR[0]);
        plate_top_y += HDC_Step_Y;
        plate_bottom_y += HDC_Step_Y;
        hdc_rectangle(middle_x - plate_width / 2, plate_bottom_y - HDC_Step_Y, plate_width, HDC_Step_Y, HDC_COLOR[plate_number]);
        if (plate_top_y <= HDC_Start_Y && plate_top_y >= pole_top_y) // 柱子范围内
        {
            hdc_rectangle(pole_x, pole_top_y, HDC_Base_Width, plate_top_y - pole_top_y, HDC_COLOR[11]);
        }
        sleeptime(yanshi);
    }
    top[b]++;
    towers[b][top[b] + 1] = plate_number;
    top[a]--;
    return;
}

//盘子水平移动
void plate_move_horizontal(char src, char dst, int yanshi)
{
    int a = translate1(src);
    int b = translate1(dst);
    int plate_number = towers[a][top[a]];
    int a_middle_x = HDC_Start_X + a * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (23 * HDC_Base_Width) / 2;
    int b_middle_x = HDC_Start_X + b * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (23 * HDC_Base_Width) / 2;
    int plate_width = (2 * plate_number + 1) * HDC_Base_Width; // 盘子总宽度
    int plate_height = HDC_Base_High;// 盘子总高度
    int plate_start_x = a_middle_x - plate_width / 2;
    int plate_target_x = b_middle_x - plate_width / 2;
    int plate_y = HDC_Top_Y;

    if (plate_start_x < plate_target_x)
    {
        //向右移动
        while (plate_start_x < plate_target_x)
        {
            //清除原位置
            hdc_rectangle(plate_start_x, plate_y, HDC_Step_X, plate_height, HDC_COLOR[0]);

            //更新盘子X坐标右移
            plate_start_x += HDC_Step_X;
            //绘制新盘子
            hdc_rectangle(plate_start_x + plate_width - HDC_Step_X, plate_y, HDC_Step_X, plate_height, HDC_COLOR[plate_number]);
            sleeptime(yanshi);
        }
    }
    else if (plate_start_x > plate_target_x)
    {
        //向左移动
        while (plate_start_x > plate_target_x)
        {
            //清除原位置
            hdc_rectangle(plate_start_x + plate_width - HDC_Step_X, plate_y, HDC_Step_X, plate_height, HDC_COLOR[0]);
            //更新盘子X坐标左移
            plate_start_x -= HDC_Step_X;
            //绘制新盘子
            hdc_rectangle(plate_start_x , plate_y, HDC_Step_X, plate_height, HDC_COLOR[plate_number]);
            sleeptime(yanshi);
        }
    }
    return;
}

//输出打印
void output(int n, char src, char tmp, char dst, int choice, int yanshi)
{
    if (choice == 1)
    {
        cout << n << "# " << src << "---->" << dst << endl;
    }
    if (choice == 2)
    {
        cout << "第" << setw(4) << setiosflags(ios::right) << step++ << " 步（" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
    }
    if (choice == 3)
    {
        cout << "第" << setw(4) << setiosflags(ios::right) << step++ << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        move(src, dst);
        printarry();
    }
    if (choice == 4)
    {
        cct_gotoxy(MenuItem4_Start_X, MenuItem4_Start_Y);
        cout << "第" << setw(4) << step++ << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        move(src, dst);
        printarry();
        cleantower(src, dst, choice);
        sleeptime(yanshi);
    }
    if (choice == 6)
    {
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层" << endl;
    }
    if (choice == 7)
    {
        plate_move_up(src, yanshi);
        plate_move_horizontal(src, dst, yanshi);
        plate_move_drop(src, dst, yanshi);
    }
    if (choice == 8)
    {
        sleeptime(yanshi);
        cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y);
        cout << "第" << setw(4) << step++ << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        move(src, dst);
        printarry();
        cleantower8(src, dst, choice);
        back(src, dst);
        if (step > 8)
        {
            yanshi = -1;
        }
        plate_move_up(src, yanshi);
        plate_move_horizontal(src, dst, yanshi);
        plate_move_drop(src, dst, yanshi);
    }
    return;
}

//递归函数
void hanoi(int n, char src, char tmp, char dst, int yanshi, int choice)
{
    if (n == 1)
    {
        output(n, src, tmp, dst, choice, yanshi);
        return;
    }
    hanoi(n - 1, src, dst, tmp, yanshi, choice);
    if (choice == 7)
    {
        return;
    }
    output(n, src, tmp, dst, choice, yanshi);
    hanoi(n - 1, tmp, src, dst, yanshi, choice);
}

//画三个圆柱
void draw_poles()
{
    //画三个底座
    for (int i = 0; i < 3; i++)
    {
        int x = HDC_Start_X + i * 23 * HDC_Base_Width + i * HDC_Underpan_Distance;
        int y = HDC_Start_Y;
        hdc_rectangle(x, y, 23 * HDC_Base_Width, HDC_Base_High, HDC_COLOR[11]);
        Sleep(HDC_Init_Delay);
    }
    for (int i = 0; i < 3; i++)
    {
        // 画柱子
        int x = HDC_Start_X + i * 23 * HDC_Base_Width + i * HDC_Underpan_Distance;
        int y = HDC_Start_Y;
        int pole_x = x + 11 * HDC_Base_Width;
        int pole_y = y - 12 * HDC_Base_High;
        hdc_rectangle(pole_x, pole_y , HDC_Base_Width , 12 * HDC_Base_High, HDC_COLOR[11]);
        Sleep(HDC_Init_Delay);
    }
    return;
}

//画盘子
void print_plate(int n, char src) 
{
    int Plate_Middle_x;//柱子中心
    int a = translate1(src);

    Plate_Middle_x= HDC_Start_X + a * (23 * HDC_Base_Width + HDC_Underpan_Distance) + (23 * HDC_Base_Width) / 2;
    for (int i = n; i > 0; i--) 
    {
        int plate_width = (2 * i + 1) * HDC_Base_Width;

        int draw_x = Plate_Middle_x - plate_width / 2;
        int draw_y = HDC_Start_Y - (n - i + 1) * HDC_Base_High;

        //盘子颜色
        int plate_color = HDC_COLOR[i];

        //绘制盘子
        hdc_rectangle(draw_x, draw_y, plate_width, HDC_Base_High, plate_color);
        Sleep(HDC_Init_Delay);
    }
    return;
}

void input(int* n, char* src, char* dst, char* tmp, int choice,int* yanshi)
{
    while (choice != 5 && choice != 0)
    {
        cout << "请输入汉诺塔的层数(1-"<< MAX_LAYER<<")：" << endl;
        cin >> *n;
        while (getchar() != '\n');
        if (cin.good() == 0)
        {
            cin.clear();
        }
        if (*n >= 1 && *n <= MAX_LAYER)
        {
            break;
        }
    }
    while (choice != 5 && choice != 0)
    {
        cout << "请输入起始柱(A-C)：" << endl;
        *src = getchar();
        while (*src == '\n')
        {
            *src = getchar();
        }
        while (getchar() != '\n');
        if (*src >= 'A' && *src <= 'C')
        {
            break;
        }
        else if (*src >= 'a' && *src <= 'c')
        {
            *src -= 32;
            break;
        }
    }
    while (choice != 5 && choice != 0 )
    {
        cout << "请输入目标柱(A-C)：" << endl;
        *dst = getchar();
        while (*dst == '\n')
        {
            *dst = getchar();
        }
        while (getchar() != '\n');
        if (*dst >= 'a' && *dst <= 'c')
        {
            *dst -= 32;
        }
        if (*dst >= 'A' && *dst <= 'C' && *dst != *src)
        {
            break;
        }
        else if (*dst >= 'A' && *dst <= 'C' && *dst == *src)
        {
            cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
        }
    }
    reset();
    int src_idx = translate1(*src);
    top[src_idx] = *n - 1;
    for (int i = 0; i < *n; i++)
    {
        towers[src_idx][i] = *n - i;
    }
    *tmp = 'A' + 'B' + 'C' - *src - *dst;
    if (choice == 4)
    {
        while (1)
        {
            cout << "请输入移动速度(0-200：0-按回车单步演示 1-200:延时1-200ms) ";
            cin >> *yanshi;
            while (getchar() != '\n');
            if (cin.good() == 0)
            {
                cin.clear();
                continue;
            }
            if (*yanshi >= 0 && *yanshi <= 200)
            {
                break;
            }
        }
    }
    if (choice == 7|| choice == 8 || choice == 9)
    {
        while (1)
        {
            cout << "请输入移动速度(0-20：0-按回车单步演示 1-20:延时1-20ms) ";
            cin >> *yanshi;
            while (getchar() != '\n');
            if (cin.good() == 0)
            {
                cin.clear();
                continue;
            }
            if (*yanshi >= 0 && *yanshi <= 20)
            {
                break;
            }
        }
        cct_gotoxy(Status_Line_X, Status_Line_Y);
        cout << "从 " << *src << " 移动到 " << *dst << "，共 " << *n << " 层"<< *yanshi << "ms" << endl;
    }
    return;
}

void hanoi_game(int n, char dst, int yanshi) 
{
    char input_src, input_dst;
    int get_plate, end_pole;

    sleeptime(yanshi);
    //输入指令
    cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 2);
    cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
    while (1) 
    {
        cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
        cout << "  ";
        cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
        bool b = 1;
        //读取输入
        input_src = getchar();
        while (input_src == '\n')
        {
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            input_src = getchar();
        }
        //输入合法性
        if (input_src != 'A' && input_src != 'B' && input_src != 'C' &&input_src != 'Q' && input_src != 'a' && input_src != 'b' && input_src != 'c' && input_src != 'q')
        {
            b = 0;
        }
        //读取目标柱
        input_dst = getchar();
        //处理退出指令（Q/q + 回车）
        if ((input_src == 'Q' || input_src == 'q') && input_dst == '\n')
        {
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "游戏中止!!!!!" << endl;
            break;
        }
        // 校验目标柱合法性
        if (input_dst == '\n')
        {
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            cout << "  ";
            continue;
        }
        if (input_dst != 'A' && input_dst != 'B' && input_dst != 'C' && input_dst != 'a' && input_dst != 'b' && input_dst != 'c') 
        {
            b = 0;
        }
        //校验输入格式（必须是 2 字符 + 回车）
        char judge = getchar();
        int num = 2;
        if (judge != '\n') 
        {
            b = 0;
            num = 3;
            while (getchar() != '\n')
            {
                num++;
            }
        }
        //转大写
        if (input_src >= 'a' && input_src <= 'z')
        {
            input_src -= 32;
        }
        if (input_dst >= 'a' && input_dst <= 'z')
        {
            input_dst -= 32;
        }
        //源柱和目标柱相同
        if (input_src == input_dst)
        {
            b = 0;
        }
        if (b == 0)
        {
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            for (;num>0;num--)
            {
                cout << " ";
            }
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            continue;
        }
        //校验源柱是否为空
        int src_idx = translate1(input_src);
        if (top[src_idx] == -1)
        {
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "源柱为空!";
            Sleep(2000);
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "         ";
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            cout << "  ";
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            continue;
        }
        get_plate = towers[src_idx][top[src_idx]];

        //校验大盘压小盘
        int dst_idx = translate1(input_dst);
        if (top[dst_idx] == -1)
        {
            end_pole = MAX_LAYER + 1; //目标柱空允许任意盘子
        }
        else
        {
            end_pole = towers[dst_idx][top[dst_idx]];
        }
        if (get_plate > end_pole)
        {
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "大盘压小盘，非法移动!";
            Sleep(2000);
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "                     ";
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            cout << "  ";
            cct_gotoxy(MenuItem8_Start_X + 60, MenuItem8_Start_Y + 2);
            continue;
        }
        //打印步数 + 更新栈 + 绘制移动
        cct_gotoxy(MenuItem8_Start_X , MenuItem8_Start_Y);
        cout << "第" << setw(4) << step++ << " 步( " << get_plate << "#: " << input_src << "-->" << input_dst << ") ";
        if (step > 8)
        {
            yanshi = -1;
        }
        move(input_src, input_dst);
        printarry();
        cleantower9(input_src, input_dst, 9);
        back(input_src, input_dst);
        plate_move_up(input_src, yanshi);
        plate_move_horizontal(input_src, input_dst, yanshi);
        plate_move_drop(input_src, input_dst, yanshi);
        int dst_final_idx = translate1(dst);
        bool is_win = 1;
        if (top[dst_final_idx] != n - 1)
        {
            is_win = 0;
        }
        else 
        {
            for (int i = n - 1; i >= 0; i--)
            {
                if (towers[dst_final_idx][i] != i + 1) 
                {
                    is_win = 0;
                    break;
                }
            }
        }
        if (is_win)
        {
            cct_gotoxy(MenuItem8_Start_X, MenuItem8_Start_Y + 3);
            cout << "游戏结束!!!!!" ;
            break;
        }
    }
}

void hanoi_multi_solutions(int choice)
{
    int n,yanshi;
    char src, tmp, dst;
    reset();
    if (choice != 5)
    {
        input(&n, &src, &dst, &tmp, choice, &yanshi);
    }
    switch (choice)
    {
        case 1:
            hanoi(n, src, tmp, dst,yanshi,choice);
            end();
            break;
        case 2:
            hanoi(n, src, tmp, dst, yanshi, choice);
            end();
            break;
        case 3:
            hanoi(n, src, tmp, dst, yanshi, choice);
            end();
            break;
        case 4:
            print4(n, src, tmp, dst, yanshi);
            hanoi(n, src, tmp, dst, yanshi, choice);
            cct_gotoxy(Status_Line_X, Status_Line_Y);
            end();
            break;
        case 5:
            cct_cls();
            hdc_cls();
            cct_gotoxy(Status_Line_X, Status_Line_Y);
            Sleep(100);
            draw_poles();
            end();
            break;
        case 6:
            cct_cls();
            hdc_cls();
            Sleep(100);
            output(n, src, tmp, dst, choice, yanshi);
            draw_poles();
            print_plate(n,src);
            end();
            break;
        case 7:
            cct_cls();
            hdc_cls();
            print7(n, src, tmp, dst, yanshi, choice);
            Sleep(30);
            draw_poles();
            print_plate(n, src);
            hanoi(n, src, tmp, dst, yanshi, choice);
            cct_gotoxy(Status_Line_X, Status_Line_Y);
            end();
            break;
        case 8:
            cct_cls();
            hdc_cls();
            print89(n, src, tmp, dst, yanshi, choice);
            Sleep(30);
            draw_poles();
            print_plate(n, src);
            hanoi(n, src, tmp, dst, yanshi, choice);
            cct_gotoxy(Status_Line_X, Status_Line_Y);
            end();
            break;
        case 9:
            cct_cls();
            hdc_cls();
            print89(n, src, tmp, dst, yanshi, choice);
            Sleep(30);
            draw_poles();
            print_plate(n, src);
            hanoi_game(n, dst, yanshi);
            cct_gotoxy(Status_Line_X, Status_Line_Y);
            end();
            break;
    }
}