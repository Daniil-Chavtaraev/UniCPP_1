#include <set>
#include <string>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <cassert>
#include <iterator>

using namespace std;

template<typename T>
T input()
{
	T variable;
	cin >> variable;
	while (!cin) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input! Try again: " << endl;
		cin >> variable;
	}
	return variable;
}

int main() {
	cout << "\nEnter U: ";
    set<int> U, A, B;
    string inp = " ";
	int intInp;
	while (getline(cin, inp)){
		if (inp.empty()){break;}
		else {
			intInp = stoi(inp);
			U.insert(intInp);
		}
	}
	cout << "\nSet U: ";
    for_each(U.begin(), U.end(), [](int i) {cout << i << ' '; });
	for (set<int>::iterator it=U.begin(); it!=U.end(); ++it){
		if (*it % 2 == 0){A.insert(*it);}
	}
	cout << "\nSet A: ";
    for_each(A.begin(), A.end(), [](int i) {cout << i << ' '; });
	inp = " ";
	//bool check = false;
	cout << "\nEnter B: ";
	while (getline(cin, inp)){
		if (inp.empty()){break;}
		else {
			intInp = stoi(inp);
			if(find(U.begin(), U.end(), intInp) != U.end()) {
				B.insert(intInp);
			} else {
				cout << "\nValue is not set U, please re-enter value!\n";
			}
		}
	}
	cout << "\nSet B: ";
	for_each(B.begin(), B.end(), [](int i) {cout << i << ' '; });
	set<int> AOrB;
	set<int> NotAOrB;
	set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(AOrB, AOrB.begin()));
	set_difference(U.begin(), U.end(), AOrB.begin(), AOrB.end(), inserter(NotAOrB, NotAOrB.begin()));
	cout << "\nA and B union:\n";
	for_each(AOrB.begin(), AOrB.end(), [](int i) {cout << i << ' '; });
	cout << "\nFirst transition (!(A+B)):\n";
	for_each(NotAOrB.begin(), NotAOrB.end(), [](int i) {cout << i << ' '; });
	set<int> notA;
	set<int> notB;
	set<int> NotAAndNOtB;
	set_difference(U.begin(), U.end(), A.begin(), A.end(), inserter(notA, notA.begin()));
	cout << "\nNot A:\n";
	for_each(notA.begin(), notA.end(), [](int i) {cout << i << ' '; });
	set_difference(U.begin(), U.end(), B.begin(), B.end(), inserter(notB, notB.begin()));
	cout << "\nNot B\n";
	for_each(notB.begin(), notB.end(), [](int i) {cout << i << ' '; });
	set_intersection(notA.begin(), notA.end(), notB.begin(), notB.end(), std::inserter(NotAAndNOtB, NotAAndNOtB.begin()));
	cout << "\nSecond transition (!A*!B):\n";
	for_each(NotAAndNOtB.begin(), NotAAndNOtB.end(), [](int i) {cout << i << ' '; });
	assert(NotAOrB == NotAAndNOtB);
	cout << "\nResults Checked!";
	cout << "\nFinal Set: ";
	for_each(NotAAndNOtB.begin(), NotAAndNOtB.end(), [](int i) {
		if (i % 2 != 0) {
			cout << i << ' ';
		}
	});
}