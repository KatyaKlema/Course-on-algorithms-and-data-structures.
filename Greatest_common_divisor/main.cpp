#include <iostream>
#include <algorithm>
#include <vector>
#include<math.h>
#include<set>
using namespace std;
/*
 Реализуйте структуру данных для эффективного вычисления НОД нескольких подряд идущих элементов массива.
Формат входных данных
В первой строке вводится одно натуральное число N(1 ≤ N ≤ 105) - количество чисел в массиве.

Во второй строке вводятся N чисел от 1 до 100000 - элементы массива.

В третьей строке вводится одно натуральное число K(1 ≤ K ≤ 30000) - количество запросов на вычисление НОД.

В следующих K строках вводится по два числа - номера левого и правого элементов отрезка массива (считается, что элементы массива нумеруются с единицы).
Формат результата
Для каждого запроса выведите НОД всех чисел соответствующего участка массива. Разделяйте числа переводами строк.
 Входные данные:
5
2 2 2 1 5
2
2 3
2 5
 Результат работы:
2
1

 */
long GCD(long a, long b) {
    long nod = 1L;
    long tmp;
    if (a == 0L)
        return b;
    if (b == 0L)
        return a;
    if (a == b)
        return a;
    if (a == 1L || b == 1L)
        return 1L;
    while (a != 0 && b != 0) {
        if (a % 2L == 0L && b % 2L == 0L) {
            nod *= 2L;
            a /= 2L;
            b /= 2L;
            continue;
        }
        if (a % 2L == 0L && b % 2L != 0L) {
            a /= 2L;
            continue;
        }
        if (a % 2L != 0L && b % 2L == 0L) {
            b /= 2L;
            continue;
        }
        if (a > b) {
            tmp = a;
            a = b;
            b = tmp;
        }
        tmp = a;
        a = (b - a) / 2L;
        b = tmp;
    }
    if (a == 0)
        return nod * b;
    else
        return nod * a;
}


class SparceTable{
private:
    vector<vector<long long>> ST;
    vector<int> lg2;

    void build(vector<long long> &nums){
        int n = nums.size();
        ST.push_back(nums);
        for(int k = 1; (1 << k) <= n; ++k){
            ST.push_back(vector<long long> ());
            for(int i = 0; i + (1 << (k - 1)) < ST[k - 1].size(); ++i){
                ST[k].push_back(GCD(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]));
            }
        }
        lg2.push_back(0);
        lg2.push_back(0);
        for(int i = 2; i <= n; ++i){
            lg2.push_back(lg2[i / 2] + 1);
        }
    }

public:
    SparceTable(vector<long long> &nums){
        build(nums);
    }

    long long get_GCD(int l, int r){
        if(l > r)
            swap(l, r);
        int k = lg2[r - l + 1];
        return GCD(ST[k][l], ST[k][r - (1 << k) + 1]);
    }

};

int main(){
    int n;
    cin >> n;
    vector<long long> nums(n);
    for(int i = 0; i < n; ++i)
        cin >> nums[i];

    SparceTable element(nums);

    int k;
    cin >> k;

    for(int i = 0; i < k; ++i){
        int l, r;
        cin >> l >> r;
        cout << element.get_GCD(l - 1, r - 1) << endl;
    }
}