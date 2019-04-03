#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
/*
 Реализуйте эффективную структуру данных, позволяющую изменять элементы массива и вычислять суммы нескольких подряд идущих элементов.
Формат входных данных
В первой строке вводится одно натуральное число N (1 ≤ N ≤ 100000) — количество чисел в массиве.

Во второй строке вводятся N чисел от 0 до 100000 — элементы массива.

В третьей строке вводится одно натуральное число M (1 ≤ M ≤ 30000) — количество запросов.

Каждая из следующих M строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (s — вычислить сумму, u — обновить значение элемента).

Следом за s вводятся два числа — номера левой и правой границы отрезка.

Следом за u вводятся два числа — номер элемента и его новое значение.
Формат результата
Для каждого запроса s выведите результат. Все числа выводите в одну строку через пробел.
 Входные данные:
10
613 263 312 670 216 142 976 355 488 370
10
s 2 7
s 4 8
u 7 969
u 1 558
s 2 7
u 2 731
s 4 9
s 1 3
u 8 76
u 5 377
 Результат работы:
2579 2359 2572 2840 1601
 */
class RMQ{
private:
    vector<long long> t;
    vector<long long> a;
public:
    RMQ(){
        t.resize(4 * 1e5);
    }

    void assemble(vector<long long > &mas){
        a = mas;
    }

    void build (long long  v, long long  tl, long long  tr) {
        if (tl == tr)
            t[v] = a[tl];
        else {
            long long  tm = (tl + tr) / 2;
            build (v * 2, tl, tm);
            build (v * 2 + 1, tm + 1, tr);
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }

    long long Min(long long a, long long b){
        return a < b ? a : b;
    }
    long long Max(long long a, long long b){
        return a > b ? a : b;
    }
    long long sum (long long v, long long tl, long long tr, long long l, long long r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];
        long long  tm = (tl + tr) / 2;
        return sum (v * 2, tl, tm, l, Min(r, tm)) + sum (v * 2 + 1, tm + 1, tr, Max(l, tm + 1), r);
    }

    void update (long long v, long long tl, long long tr, long long pos, long long new_val) {
        if (tl == tr)
            t[v] = new_val;
        else {
            long long  tm = (tl + tr) / 2;
            if (pos <= tm)
                update (v * 2, tl, tm, pos, new_val);
            else
                update (v * 2 + 1, tm + 1, tr, pos, new_val);
            t[v] = t[v * 2] + t[v * 2 + 1];
        }
    }

};

int main(){
    long long size;
    cin >> size;
    vector<long long> a(size);

    for(long long i = 0; i < size; ++i)
        cin >> a[i];

    long long num_cmd;
    cin >> num_cmd;

    RMQ element;
    element.assemble(a);
    element.build(1, 0, size - 1);
    for(long long i = 0; i < num_cmd; ++i){
        char cmd;
        cin >> cmd;
        if(cmd == 'u'){
            long long pos, new_val;
            cin >> pos >> new_val;
            element.update(1, 0, size - 1, pos - 1, new_val);
        }
        else{
            long long l, r;
            cin >> l >> r;
            cout << element.sum(1, 0, size - 1, l - 1, r - 1) << " ";

        }
    }
}