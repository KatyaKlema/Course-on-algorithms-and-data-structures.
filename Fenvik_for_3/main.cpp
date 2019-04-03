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
 Вася любит наблюдать за звездами. Но следить за всем небом сразу ему тяжело. Поэтому он наблюдает только за частью пространства, ограниченной кубом размером n на n на n. Этот куб поделён на маленькие кубики размером 1x1x1. Во время его наблюдений могут происходить следующие события:

• в каком-то кубике появляются или исчезают несколько звезд;
• к нему может заглянуть его друг Петя и поинтересоваться, сколько видно звезд в части пространства, состоящей из нескольких кубиков.
Формат входных данных
Первая строка входного файла содержит натуральное число n (n ≤ 128). Координаты кубиков - целые число от 0 до n-1. Далее следуют записи о происходивших событиях по одной в строке.

В начале строки записано число m. Если m равно:

• 1, то за ним следуют 4 числа: x, y, z, k. (0 ≤ x, y, z < N, -20000 ≤ k ≤ 20000) - координаты кубика и величина, на которую в нем изменилось количество видимых звезд;
• 2, то за ним следуют 6 чисел: x1, y1, z1, x2, y2, z2 (0 ≤ xi, yi, zi < N, x1 ≤ x2, y1 ≤ y2, z1 ≤ z2 которые означают, что Петя попросил подсчитать количество звезд в кубиках (x', y', z') из области: x1 ≤ x' ≤ x2, y1 ≤ y' ≤ y2, z1 ≤ z' ≤ z2.
• 3, то это означает, что Васе надоело наблюдать за звездами и отвечать на вопросы Пети. Эта запись встречается во входном файле только один раз и будет последней записью. Количество записей во входном файле не превосходит 100500.
Формат результата
Для каждого Петиного вопроса выведите на отдельной строке одно число - искомое количество звезд.
 Входные данные
2
2 1 1 1 1 1 1
1 0 0 0 1
1 0 1 0 3
2 0 0 0 0 0 0
2 0 0 0 0 1 0
1 0 1 0 -2
2 0 0 0 1 1 1
3

 Результат работы
0
1
4
2
 */
class FenvikTree{
private:
    vector<vector<vector<long long>>> T;
    long long n;
public:
    FenvikTree(long long nn): n(nn){
        T.assign(nn, vector<vector<long long>>(nn, vector<long long>(nn, 0)));
    }

    void update(long long &ii, long long &jj, long long &kk, long long &delta){
        for(long long i = ii; i < n; i = i | (i + 1)){
            for(long long j = jj; j < n; j = j | (j + 1)){
                for(long long k = kk; k < n; k = k | (k + 1))
                    T[i][j][k] += delta;
            }
        }
    }

    long long sum(long long x, long long y, long long z) {
        if (x >= 0 && y >= 0 && z >= 0) {
            long long result = 0;
            for (long long i = x; i >= 0; i = (i & (i + 1)) - 1) {
                for (long long j = y; j >= 0; j = (j & (j + 1)) - 1) {
                    for(long long k = z; k >= 0; k = (k & (k + 1)) - 1)
                        result += T[i][j][k];
                }
            }
            return result;
        } else
            return 0;
    }
};
int main() {
    long long n;
    cin >> n;

    FenvikTree Tree(n);
    int cmd = 0;
    cin >> cmd;
    while(cmd != 3){
        if(cmd == 1){
            long long x, y, z, delta;
            cin >> x >> y >> z >> delta;
            Tree.update(x, y, z, delta);
        }
        else{
            long long x_1, y_1, z_1, x_2, y_2, z_2, x_3, y_3, z_3;
            cin >> x_1 >> y_1 >> z_1 >> x_2 >> y_2 >> z_2;
            cout << Tree.sum(x_2, y_2, z_2)
                    - Tree.sum(x_2, y_2, z_1 - 1)
                    - Tree.sum(x_2, y_1 - 1, z_2) - Tree.sum(x_1 - 1, y_2, z_2)
                    + Tree.sum(x_1 - 1, y_1 - 1, z_2)
                    + Tree.sum(x_1 - 1, y_2, z_1 - 1) + Tree.sum(x_2, y_1 - 1, z_1 - 1)
                    - Tree.sum(x_1 - 1, y_1 - 1, z_1 - 1) << endl;
        }
        cin >> cmd;
    }


}