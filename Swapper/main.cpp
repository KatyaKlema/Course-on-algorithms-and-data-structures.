#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
using namespace std;
/*
 Перед возвращением в штаб-квартиру корпорации Аазу и Скиву пришлось заполнить на местной таможне декларацию о доходах за время визита. Получилась довольно внушительная последовательность чисел. Обработка этой последовательности заняла весьма долгое время.

— Своппер кривой, — со знанием дела сказал таможенник.

— А что такое своппер? — спросил любопытный Скив.

Ааз объяснил, что своппер — это структура данных, которая умеет делать следующее.

• Взять отрезок чётной длины от x до y и поменять местами число x с x+1, x+2 с x+3, и т.д.
• Посчитать сумму чисел на произвольном отрезке от a до b.

Учитывая, что обсчёт может затянуться надолго, корпорация "МИФ" попросила Вас решить проблему со своппером и промоделировать ЭТО эффективно.
Формат входных данных
Во входном файле заданы один или несколько тестов. В первой строке каждого теста записаны число N - длина последовательности и число M - число операций (1 ≤ N, M ≤ 100000). Во второй строке теста содержится N целых чисел, не превосходящих 106 по модулю - сама последовательность.
Далее следуют M строк - запросы в формате "1 xi yi" - запрос первого типа, и "2 ai bi" - запрос второго типа. Сумма всех N и M по всему файлу не превосходит 200000. Файл завершается строкой из двух нулей. Гарантируется, что xi < yi, а ai ≤ bi.
Формат результата
Для каждого теста выведите ответы на запросы второго типа, как показано в примере. Разделяйте ответы на тесты пустой строкой.
 Входные данные:5 5
1 2 3 4 5
1 2 5
2 2 4
1 1 4
2 1 3
2 4 4
2 1
1 2
2 1 2
0 0
 Результат работы:
Swapper 1:
10
9
2

Swapper 2:
3
 */
class Treap {
public:
    int x;
    int y;
    long long size;
    long long sum;

    Treap *left ;
    Treap *right;

    Treap(): x(0), y(0), left(NULL), right(NULL), size(0), sum(0)
    {}
    Treap(int key): x(key), y(rand()), left(NULL), right(NULL), size(1), sum(key)
    {}

};

long long getSize(Treap *root){
    return ((root == NULL) ? 0 : root->size);
}


long long getSum(Treap *root){
    return ((root == NULL) ? 0 : root->sum);
}
void update(Treap *root){
    root->size = 1 + getSize(root->left) + getSize(root->right);
    root->sum = root->x + getSum(root->left) + getSum(root->right);
}

Treap* merge(Treap *Left, Treap *Right){
    if(Left == NULL)
        return Right;
    if(Right == NULL)
        return Left;
    if(Left->y >= Right->y){
        Left->right = merge(Left->right, Right);
        update(Left);
        return Left;
    }
    else{
        Right->left = merge(Left, Right->left);
        update(Right);
        return Right;
    }
}

void split(Treap *root, int index, Treap *&L, Treap *&R, int left = 0){
    if(root == NULL){
        L = NULL;
        R = NULL;
        return;
    }
    int newKey = left + getSize(root->left);
    if (newKey <= index){
        split(root->right, index, root->right, R, newKey + 1);
        L = root;
    }
    else{
        split(root->left, index, L, root->left, left);
        R = root;
    }
    update(root);
}

void insert(Treap *&root, long long val, int pos){
    Treap *newRoot = new Treap(val);
    Treap *L, *R;
    split(root, pos, L, R);
    root = merge(merge(L, newRoot), R);

}

void get_trees(Treap*& odd_root, Treap*& even_root, int left, int right, Treap*& odd_first, Treap*& odd_second, Treap*& odd_third, Treap*& odd_fourth,
               Treap*& even_first, Treap*& even_second, Treap*& even_third, Treap*& even_fourth) {
    int odd_left, odd_right, even_left, even_right;
    if (left % 2 == 1) {
        odd_left = (left + 1) / 2;
        even_left = left / 2;
    }
    else {
        odd_left = left / 2;
        even_left = (left + 1) / 2;
    }
    if (right % 2 == 1) {
        odd_right = (right - 1) / 2;
        even_right = right / 2;
    }
    else {
        odd_right = right / 2;
        even_right = (right - 1) / 2;
    }
    split(odd_root, odd_right, odd_first, odd_second);
    split(odd_first, odd_left - 1, odd_third, odd_fourth);
    split(even_root, even_right, even_first, even_second);
    split(even_first, even_left - 1, even_third, even_fourth);
}

void change(Treap*& odd_root, Treap*& even_root, int left, int right) {
    Treap* odd_first, *odd_second, *odd_third, *odd_fourth;
    Treap* even_first, *even_second, *even_third, *even_fourth;
    get_trees(odd_root, even_root, left, right, odd_first, odd_second, odd_third, odd_fourth, even_first, even_second, even_third, even_fourth);
    odd_root = merge(merge(odd_third, even_fourth), odd_second);
    even_root = merge(merge(even_third, odd_fourth), even_second);
}

long long int count_sum(Treap* odd_root, Treap* even_root, int left, int right) {
    Treap* odd_first, *odd_second, *odd_third, *odd_fourth;
    Treap* even_first, *even_second, *even_third, *even_fourth;
    get_trees(odd_root, even_root, left, right, odd_first, odd_second, odd_third, odd_fourth, even_first, even_second, even_third, even_fourth);
    long long int result;
    if (left == right && left % 2 == 0) {
        result = getSum(odd_fourth);
    }
    else if (left == right && left % 2 == 1) {
        result = getSum(even_fourth);
    }
    else {
        result = getSum(odd_fourth) + getSum(even_fourth);
    }
    odd_root = merge(merge(odd_third, odd_fourth), odd_second);
    even_root = merge(merge(even_third, even_fourth), even_second);
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    int counter = 1;
    while (n != 0 || m != 0) {
        Treap* odd_root = NULL;
        Treap* even_root = NULL;
        for (int i = 0; i < n; i++) {
            int current;
            cin >> current;
            if (i % 2 == 0) {
                insert(odd_root, current, i);
            }
            else {
                insert(even_root, current, i);
            }
        }
        cout << "Swapper " << counter++ << ":" << endl;
        for (int i = 0; i < m; i++) {
            int command, left, right;
            cin >> command >> left >> right;
            left--;
            right--;
            if (command == 1) {
                change(odd_root, even_root, left, right);
            }
            else {
                cout << count_sum(odd_root, even_root, left, right) << endl;
            }
        }
        cout << endl;
        cin >> n >> m;
    }
    return 0;
}