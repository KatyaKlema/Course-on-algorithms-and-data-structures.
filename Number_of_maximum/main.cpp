#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
/*Реализуйте структуру данных для эффективного вычисления значения максимального из нескольких подряд идущих элементов массива, а также количества элементов, равных максимальному на данном отрезке.
Формат входных данных
В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.

Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.

В третьей строке вводится одно натуральное число K(1 ≤ K ≤ 30000) — количество запросов на вычисление максимума.

В следующих K строках вводится по два числа - номера левого и правого элементов отрезка массива (считается, что элементы массива нумеруются с единицы).
Формат результата
Для каждого запроса выведите в отдельной строке через пробел значение максимального элемента на указанном отрезке массива и количество максимальных элементов на этом отрезке.
 Входные данные:
5
2 2 2 1 5
2
2 3
2 5
 Результат работы:
2 2
5 1
 */
vector<pair<int,int> > t(4 * 1e5);

pair<int,int> combine (pair<int,int> a, pair<int,int> b) {
    if (a.first > b.first)
        return a;
    if (b.first > a.first)
        return b;
    return make_pair (a.first, a.second + b.second);
}

void build (vector<int> &a, int v, int tl, int tr) {
    if (tl == tr)
        t[v] = make_pair (a[tl], 1);
    else {
        int tm = (tl + tr) / 2;
        build (a, v*2, tl, tm);
        build (a, v*2+1, tm+1, tr);
        t[v] = combine (t[v*2], t[v*2+1]);
    }
}

pair<int,int> get_max (int v, int tl, int tr, int l, int r) {
    if (l > r)
        return make_pair (-1e9, 0);
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine (
            get_max (v * 2, tl, tm, l, min(r,tm)),
            get_max (v * 2 + 1, tm+1, tr, max(l,tm + 1), r)
    );
}

void update (int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        t[v] = make_pair (new_val, 1);
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update (v * 2, tl, tm, pos, new_val);
        else
            update (v * 2 + 1, tm + 1, tr, pos, new_val);
        t[v] = combine (t[v * 2], t[v * 2 + 1]);
    }
}

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }

    build(a, 1, 0, n - 1);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i){
        int l, r;
        cin >> l >> r;

        pair<int, int> p = get_max(1, 0, n - 1, l - 1, r - 1);
        cout << p.first << " " << p.second << endl;
    }
}