#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

/*
На вход программы подаются сведения о набранных на ЕГЭ баллах
учениками данной школы по трём предметам. В первой строке сообщается
количество учащихся N (N ≤ 100), каждая из следующих N строк имеет
формат: <Фамилия> <Инициалы> <БаллыПоРусскомуЯзыку>
<БаллыПоМатематике> <БаллыПоИнформатике>, где <Фамилия> — строка,
состоящая не более чем из 20 символов, <Инициалы> — строка, состоящая
из 4 символов (буква, точка, буква, точка), <БаллыПоРусскомуЯзыку>,
<БаллыПоМатематике>, <БаллыПоИнформатике> — целые числа в
диапазоне от 0 до 100. Все элементы одной строки отделены друг от друга
пробелом.
Необходимо вывести на экран фамилии и инициалы учеников,
набравших максимальную сумму баллов по трём предметам (таких учеников
может быть несколько), а также набранную ими сумму баллов. Следует
учитывать, что N ≤100.
*/

int input(int min, int max)
{
	int variable;
	cin >> variable;
	while (!(cin) || variable < min || variable > max) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input! Try again: " << endl;
		cin >> variable;
	}
	return variable;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Enter N: ";
	int N = input(0, INT_MAX);
	cout << "Enter information: ";
	string lastName, initials, fName;
    int rusRes, mathRes, infRes, sumRes, sumResMax = -1;
    map<string, int> pupils;
    for (int i = 0; i < N; ++i){
        cin >> lastName >> initials >> rusRes >> mathRes >> infRes;
        while (!(cin) || lastName.length() > 20 || ((initials[1] != '.')&&(initials[3] != '.')) || rusRes > 100 || rusRes < 0 || mathRes > 100 || mathRes < 0 || infRes > 100 || infRes < 0){ 
            cout << "Invalid input! Try again: " << endl;
			cin.clear();
            cin >> lastName >> initials >> rusRes >> mathRes >> infRes;
        }
        sumRes = rusRes + mathRes + infRes;
        if (sumRes > sumResMax) {
            sumResMax = sumRes;
        }
        fName = lastName + ' ' + initials;
        pupils[fName] = sumRes;
    }
    cout << "____________________________________________________" << endl;
    for (auto it = pupils.begin(); it != pupils.end(); ++it) {
       if (it->second == sumResMax) {
            cout << it->first << " " << it->second << endl;
       }
    }
}
