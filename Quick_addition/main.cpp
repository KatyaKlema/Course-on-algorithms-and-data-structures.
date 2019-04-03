#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
unsigned int a, b;
unsigned int cur = 0;
/*
 Есть массив целых чисел длины n = 224, изначально заполненных нулями. Вам нужно сперва обработать m случайных запросов вида "прибавление на отрезке". Затем обработать q случайных запросов вида "сумма на отрезке".
Формат входных данных
На первой строке числа m, q (1 ≤ m, q ≤ 224). На второй строке пара целых чисел a, b от 1 до 109, используемая в генераторе случайных чисел.


1
2
3
4
5
6
unsigned int a, b; // даны во входных данных
unsigned int cur = 0; // беззнаковое 32-битное число
unsigned int nextRand() {
  cur = cur * a + b; // вычисляется с переполнениями
  return cur >> 8; // число от 0 до 224-1.
}

Каждый запрос первого вида генерируется следующим образом:
1
2
3
4
add = nextRand(); // число, которое нужно прибавить
l = nextRand();
r = nextRand();
if (l > r) swap(l, r); // получили отрезок [l..r]
Каждый запрос второго вида генерируется следующим образом:
1
2
3
l = nextRand();
r = nextRand();
if (l > r) swap(l, r); // получили отрезок [l..r]
Сперва генерируются запросы первого вида, затем второго.
Формат результата
Выведите сумму ответов на все запросы второго типа по модулю 2^32.
 Входные данные:
5 5
13 239
 Результат работы:
811747796
 */
int SIZE = (1 << 24);
unsigned int nextRand(){
    cur = cur * a + b;
    return (cur >> 8);
}

int main() {
    unsigned int m, q;
    cin >> m >> q >> a >> b;
    vector<unsigned int> array(SIZE, 0);
    for(unsigned int i = 0; i < m; ++i){
        unsigned int add = nextRand();
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if(l > r)
            swap(l, r);
        array[l] += add;
        if(r + 1 < SIZE)
            array[r + 1] -= add;
    }

    vector<unsigned int> prefixSum(SIZE, 0);
    unsigned int current = array[0];
    prefixSum[0] = array[0];
    for(unsigned int i = 1; i < SIZE; ++i){
        current += array[i];
        prefixSum[i] = prefixSum[i - 1] + current;
    }
    unsigned int result = 0;
    for(unsigned int i = 0; i < q; ++i){
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if(l > r)
            swap(l, r);
        if(l != 0)
            result += prefixSum[r] - prefixSum[l - 1];
        else
            result += prefixSum[r];
    }

    cout << result ;
}