#include <iostream>
#include <string>
#include <set>
#include <stdio.h>
using namespace std;
//I = ((“true” | “false” | I) | (I (= | <> | > | <) I)“;”)
bool FSM(char ch, int &S) // Возврящается флаг ошибки
{
    switch (S)
    {
    case 0:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            S = 1;
            return false;
        }
        S = -1;
        return true;
    case 1:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
        {
            S = 1;
            return false;
        }
        if (ch == '=')
        {
            S = 2;
            return false;
        }
        S = -1;
        return true;
    case 2:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            S = 10;
            return false;
        }
        if (ch == ';'){
            S = 14;
            return false;
        }
        if (ch == 't')
        {
            S = 3;
            return false;
        }
        if (ch == 'f')
        {
            S = 5;
            return false;
        }
        S = -1;
        return true;
    case 3:
        if (ch == 'r')
        {
            S = 4;
            return false;
        }
        S = -1;
        return true;
    case 4:
        if (ch == 'u')
        {
            S = 8;
            return false;
        }
        S = -1;
        return true;
    case 5:
        if (ch == 'a')
        {
            S = 6;
            return false;
        }
        S = -1;
        return true;
    case 6:
        if (ch == 'l')
        {
            S = 7;
            return false;
        }
        S = -1;
        return true;
    case 7:
        if (ch == 's')
        {
            S = 8;
            return false;
        }
        S = -1;
        return true;
    case 8:
        if (ch == 'e')
        {
            S = 9;
            return false;
        }
        S = -1;
        return true;
    case 9:
        if (ch == ';')
        {
            S = 14;
            return false;
        }
        S = -1;
        return true;
    case 10:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
        {
            S = 10;
            return false;
        }
        if (ch == '<')
        {
            S = 11;
            return false;
        }
        if (ch == '=' || ch == '>')
        {
            S = 12;
            return false;
        }
        if (ch == ';'){
            S = 14;
            return false;
        }
        S = -1;
        return true;
    case 11:
        if (ch == '>')
        {
            S = 12;
            return false;
        }
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            S = 13;
            return false;
        }
        S = -1;
        return true;
    case 12:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        {
            S = 13;
            return false;
        }
        S = -1;
        return true;
    case 13:
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
        {
            S = 13;
            return false;
        }
        if (ch == ';'){
            S = 14;
            return false;
        }
        S = -1;
        return true;
    case 14:
        break;
    }
}

int main()
{
    int S = 0;
    string str;
    set<int> Final = {14}; // Множество конечных состояний автомата
    bool FEnter = false;
    while (getline(cin, str), str != "")
    {
        if (!FEnter)
            FEnter = true;
        else
            FSM('\n', S);
        for (auto i : str)
            if (FSM(i, S))
                break;
    }
    cout << S << endl;
    if (Final.count(S)) // Проверяем, находится ли автомат в конечном состоянии
        cout << "Yes";
    else
        cout << "No";
    return 0;
}