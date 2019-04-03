#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
/*Дан массив из n чисел. Требуется написать программу, которая будет отвечать на запросы следующего вида: найти минимум на отрезке между u и v включительно.
Формат входных данных
В первой строке входного файла даны три натуральных числа n, m (1 ≤ n ≤ 105, 1 ≤ m ≤ 107) и a1 0 ≤ a_1 < 16714589) количество элементов в массиве, количество запросов и первый элемент массива соответственно. Вторая строка содержит два натуральных числа u1 и v1 (1 ≤ u1, v1 ≤ n) первый запрос.

Элементы a2, a3, ..., an задаются следующей формулой:

ai + 1 = (23 · ai + 21563) % 16714589.
Например, при n = 10, a1 = 12345 получается следующий массив: a = (12345, 305498, 7048017, 11694653, 1565158, 2591019, 9471233, 570265, 13137658, 1325095).


Запросы генерируются следующим образом:
ui + 1 = (17 · ui + 751 + ansi + 2i) % n + 1,
vi + 1 = (13 · vi + 593 + ansi + 5i) % n + 1
где ansi - ответ на запрос номер i.

Обратите внимание, что ui может быть больше, чем vi.
Формат результата
В выходной файл выведите um, vm и ansm (последний запрос и ответ на него).
 Входные данные:
10 8 12345
3 9
 Результат работы:
5 3 1565158
 */

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
                ST[k].push_back(min(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]));
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

    long long get_min(int l, int r){
        if(l > r)
            swap(l, r);
        int k = lg2[r - l + 1];
        return min(ST[k][l], ST[k][r - (1 << k) + 1]);
    }
};

int main() {
    long long  n, m, a_1;
    cin >> n >> m >> a_1;


    vector<long long> a(n);
    a[0] = a_1;
    for(int i = 1; i < n; ++i){
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }

    long long u, v;
    cin >> u >> v;

    SparceTable S(a);

    long long ans = 0;


    for(int i = 1; i < m; ++i){
        ans = S.get_min(u - 1, v - 1);
        u = (17 * u + 751 + ans + 2 * i) % n + 1;
        v = (13 * v + 593 + ans + 5 * i) % n + 1;

    }

    cout << u << " " <<  v << " " << S.get_min(u - 1, v - 1);
}