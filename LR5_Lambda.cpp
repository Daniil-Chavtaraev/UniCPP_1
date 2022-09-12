#include <iostream>
#include <functional>
#include <string>
#include <map>

using namespace std;

const int start = 4, fin = 29, point1 = 9, point2 = 19; // Начальное и конечное числа; Ограничения.
//Числа: 4 29 Операции: +2 (*2-1) Ограничения: 9 или 19

int main() {
    // Прямой ход расчета
    int branchCount = 0; // Счётчик просмотренных веток дерева
    function<int (int, int, string)> calc = [&calc, &branchCount](int x, int fin, string way) {
        branchCount++;
        if (x < fin) return calc(x + 2, fin, way + " +2") + calc(x * 2 - 1 , fin, way + " *2-1");
        else
            if(x == fin) {
                cout << way << endl;
                return 1;
            }
        return 0;
    };
    cout << "Forward\nCount:\n" << calc(start, fin, "") << endl;
    cout << "branchCount: " << branchCount << endl;
    branchCount = 0;

    bool pointCheck = false;
    function<int (int, int, int, int, bool, string)> calcPoints = [&calcPoints, &branchCount](int x, int fin, int point1, int point2, bool pointCheck, string way) {
        branchCount++;
        if (x == point1) {
            pointCheck = true;
        }
        if (x == point2) {
            pointCheck = true;
        }
        if (x < fin) return calcPoints(x + 2, fin, point1, point2, pointCheck, way + " +2") + calcPoints(x * 2 - 1 , fin, point1, point2, pointCheck, way + " *2-1");
        else
            if (x == fin  && pointCheck) {
                cout << way << endl;
                return 1;
            }
        return 0;
    };
    cout << "Counting through points:\nCount:\n" << calcPoints(start, fin, point1, point2, pointCheck, "") << endl;
    cout << "branchCount: " << branchCount << endl;
    branchCount = 0; 

    // Расчет обратным ходом
    function<int (int, int, string)> calcBack = [&calcBack, &branchCount](int x, int fin, string way) {
        branchCount++;
        int t = 0;
        if(x > fin) {
            t += calcBack(x - 2, fin, way + " -2");
            if (x % 2 == 1) {
                t += calcBack((x + 1) / 2, fin , way + " (x+1)/2");
            }
            return t;
        }
        else {
            if(x == fin) {
                cout << way << endl;
                return 1;
            }
            return 0;
        }
    };
    cout << "Back\nCount:\n" << calcBack(fin, start, "") << endl;
    cout << "branchCount: " << branchCount << endl;
    branchCount = 0;

    // Расчет методом исследования операций
    map<int,int> Space;
    function<int (int, int)> calcOp = [&Space, &calcOp, &branchCount](int x, int fin) {
    branchCount++;
    if(Space.count(x)) return Space[x];
        if(x == fin) {
            Space[x] = 1;
            return 1;
        }
        if(x < fin) {
            Space[x] = calcOp(x + 1, fin) + calcOp(x * 2, fin);
            return Space[x];
        }
        return 0;
    };
    cout << "OR\nCount:\n" << calcOp(start, fin) << endl;
    cout << "BranchCount: "<< branchCount <<endl;
    // Вывод вектора фазового пространства
    for(auto i: Space) cout << i.first << " " << i.second << endl;
    return 0;
}