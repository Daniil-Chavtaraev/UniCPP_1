#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <numeric>

using namespace std;

/*
- 30 целочисленных положительных элементов
- Найти разность между максимальным четным и максимальным нечетным элементом
- Реализовать алгоритм с помощью итератора
*/

void N1(){
	srand ( time(NULL) );
	vector<int> vec(30);
	generate(vec.begin(), vec.end(), []() -> int {
		return rand() % 100;
	});
	cout << "Vector: ";
	vector<int>::iterator i, maxEven, maxOdd;
	for (i = vec.begin(); i != vec.end(); ++i) {
		cout << *i << ' ';
	}
	maxEven = maxOdd = vec.begin();
	int diff = 0;
	for (i = ++vec.begin(); i != vec.end(); ++i) {
		if (*i > *maxEven && (*i % 2 == 0)) {
			maxEven = i;
		}
		if (*i > *maxOdd && (*i % 2 == 1)) {
			maxOdd = i;
		}
		diff = *maxEven - *maxOdd;
	}
	cout << "\nМаксимальное четное: " << *maxEven;
	cout << "\nМаксимальное нечетное: " << *maxOdd;
	cout << "\nИскомая разность равна: " << diff << endl;
}

/*
- Реализовать алгоритм с помощью шаблонной функции
- Дан массив из N вещественных чисел. К каждому положительному элементу добавить максимальный
положительный элемент.
- Сжать массив, удалив из него все элементы, лежащие в диапазоне [a,b].
- Освободившиеся в конце массива элементы заполнить суммой положительных элементов в исходном массиве.
- Если элементы, расположенные за первым нулевым элементом, упорядочены в порядке возрастания, то
найти сумму элементов массива, расположенных до последнего максимального элемента.
- Удалить из массива элементы, чей знак не совпадает со знаком максимального элемента.
- Отсортировать по убыванию часть массива между максимальным и минимальным элементами.
*/


//Шаблонная функция ввода переменной
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

//Функция вывода вектора
void print_vector(const vector<double>& c) 
{
    for (auto &i : c) {
        cout << i << " ";
    }
    cout << '\n';
}

void N2(){
	// Ввод вектора
	int N;
	cout << "\nEnter N: ";
	N = input<int>();
	while (N <= 0) {
		cout << "N should be bigger than 0!";
		N = input<int>();
	}
	vector<double> vec(N);
	cout << "\nEnter vector items: ";
	generate(vec.begin(), vec.end(), []() {
		return input<double>();
	});
	cout << "\nVector: ";
	print_vector(vec);

	cout << "\nДан массив из N вещественных чисел. К каждому положительному элементу добавить максимальный положительный элемент.";
	//Дан массив из N вещественных чисел. К каждому положительному элементу добавить максимальный положительный элемент.
	double maxEl = *max_element(vec.begin(), vec.end());
	cout << "\nMax Element: " << maxEl;
	double sumPos = 0;
	if (maxEl > 0){
		for_each(vec.begin(), vec.end(), [maxEl, &sumPos](double& i){
			if (i > 0) {
				i += maxEl;
				sumPos += i; // Заранее вычислим сумму положительных
			}
		});
	}
	else {
		cout << "\nMax element is not positive.";
	}
	cout << "\nSumm of Positive Numbers: " << sumPos;
	cout << "\nNew Vector: ";
	print_vector(vec);

	cout << "\nСжать массив, удалив из него все элементы, лежащие в диапазоне [a,b]";
	cout << "\nОсвободившиеся в конце массива элементы заполнить суммой положительных элементов в исходном массиве.";
	//Сжать массив, удалив из него все элементы, лежащие в диапазоне [a,b].
	//Освободившиеся в конце массива элементы заполнить суммой положительных элементов в исходном массиве.
	double a, b;
	cout << "\nEnter a: ";
	a = input<double>();
	cout << "\nEnter b: ";
	b = input<double>();
	while (a > b) {
		cout << "\na must be lower then b, re-enter values";
		cout << "\nEnter a: ";
		a = input<double>();
		cout << "\nEnter b: ";
		b = input<double>();
	}
	int oldVSize = vec.size();
	auto it = remove_if(vec.begin(), vec.end(), [a, b](double i){return(a <= i && i <= b);});//Удаляет лишние элементы и пересобирает
	for_each(it, vec.end(), [sumPos](double& i){i = sumPos;});
	cout << "\nNew Vector: ";
	print_vector(vec);

	cout << "\nЕсли элементы, расположенные за первым нулевым элементом, упорядочены в порядке возрастания, то\nнайти сумму элементов массива, расположенных до последнего максимального элемента.";
	//Если элементы, расположенные за первым нулевым элементом, упорядочены в порядке возрастания, то
	//найти сумму элементов массива, расположенных до последнего максимального элемента.
	auto zeroIt = find(vec.begin(), vec.end(), 0);
	if (zeroIt != vec.end()){
		double prevEl = *zeroIt, sum = 0;
		auto sortIt = find_if_not(++zeroIt, vec.end(), [&prevEl, &sum](double& i){
			bool res = i > prevEl;
			prevEl = i;
			sum += i;
			return res;});
		if (sortIt == vec.end()){
			cout << "\nSum: " << sum;
		} else {
			cout << "\nElements are not ordered: ";
		}
	} else {
		cout << "\nThere are no zero element";
	}
	
	cout << "\nУдалить из массива элементы, чей знак не совпадает со знаком максимального элемента.";
	//Удалить из массива элементы, чей знак не совпадает со знаком максимального элемента.
	cout << "\nMax Element: " << maxEl << endl;
	if (maxEl > 0) {
			auto it = remove_if(vec.begin(), vec.end(), [](double& i){return i < 0;});
			vec.erase(it, vec.end());
	}
	cout << "\nNew Vector: ";
	print_vector(vec);

	//Отсортировать по убыванию часть массива между максимальным и минимальным элементами.
	cout << "\nОтсортировать по убыванию часть массива между максимальным и минимальным элементами.";
	double minEl = *min_element(vec.begin(), vec.end());
	if (maxEl == minEl){cout << "\nAll elements are equal";} else {
		auto maxIt = find(vec.begin(), vec.end(), maxEl);
		auto minIt = find(vec.begin(), vec.end(), minEl);
		if (minIt < maxIt)
		{
			sort(minIt+1, maxIt);
			reverse(minIt+1, maxIt); 
		} else {
			sort(maxIt+1, minIt);
			reverse(maxIt+1,  minIt); 
		}
	}
	cout << "\nNew Vector: ";
	print_vector(vec);
}


/*
void tryIt(){
	int N;
	cout << "\nEnter N: ";
	N = input<int>();
	while (N <= 0) {
		cout << "N should be bigger than 0!";
		N = input<int>();
	}
	vector<double> vec(N);
	cout << "\nEnter vector items: ";
	generate(vec.begin(), vec.end(), []() {
		return input<double>();
	});
	cout << "\nVector: ";
	print_vector(vec);
}*/

int main(){
	//cout << "Kek:\n";
	//tryIt();
	cout << "First task:\n";
	N1();
	cout << "\nSecond task";
	N2();
}