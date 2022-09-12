#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <windows.h>


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

void print_vector(const vector<string>& c) 
{
    for (auto &i : c) {
        cout << i << " ";
    }
    cout << '\n';
}

bool check_polindrom(string word)
{
	int len = word.length();
	for(int i = 0; i < len/2; ++i)
	{
		if(word[i] != word[len-i-1])
		{
			return false;
		}
	}
	return true;
}

int main (){
    //Ввод
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "\nEnter words:";
    vector<string> words, polindromVec;
    string inp;
    while (getline(cin, inp)) {
		if (inp.empty()){break;}
		else {
			words.push_back(inp);
		}
	}
    cout << "\nWords:";
    print_vector(words);
    //Преобразовать исходный массив, вставив в каждое слово длиной более двух и менее 6 символов после второй буквы подстроку из двух конечных букв этого же слова.
    for_each(words.begin(), words.end(), [](string& i) {
            if (i.size() > 2 && i.size() < 6) {
                i.push_back(i[1]);
                i.push_back(i[1]);
            }
        }
    );
    cout << "\nChanged words 1:";
    print_vector(words);
    //Удалить из всех слов массива все латинские буквы.
    for_each(words.begin(), words.end(), [](string& i){i.erase(remove_if(i.begin(), i.end(), [](unsigned char x){return x >= 128;}), i.end());});
    for (auto it = words.begin(); it != words.end(); ) {
        if (*it == "") {
            it = words.erase(it);
        } else {
            ++it;
        }
    }
    cout << "\nChanged words 2:";
    print_vector(words);
    //Сформировать предложение из тех слов полученного массива, которые являются «перевертышами». Слова в предложении должны быть упорядочены по длине слов.
    for (auto it = words.begin(); it != words.end(); ++it) {
        if (check_polindrom(*it)) {
            polindromVec.push_back(*it);
        }
    }
    //sort(polindromVec.begin(), polindromVec.end());
    sort(polindromVec.begin(), polindromVec.end(), [](const string& a, const string& b){ return a.length() < b.length(); });
    cout << "\nSorted polindrons:";
    print_vector(polindromVec);
}