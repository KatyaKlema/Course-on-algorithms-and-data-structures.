#include <iostream>
#include <vector>
/*Саша любит наблюдать за ромашками. Но следить за всем полем сразу ей тяжело. Поэтому она наблюдает только за его частью, ограниченной прямоугольником размером x на y. Этот прямоугольник поделён на маленькие прямоугольники размером 1x1. Во время её наблюдений могут происходить следующие события:

• в каком-то прямоугольнике появляются или исчезают несколько ромашек;
• к ней может заглянуть её подруга Настя и поинтересоваться, сколько видно ромашек в части поля, состоящей из нескольких прямоугольников.
Формат входных данных
Первая строка входного файла содержит два натуральных числа x и y (1 ≤ x, y ≤ 1000). Следующая строка содержит единственное натуральное число n (1 ≤ n ≤ 100000) - количество произошедших событий. Далее следуют n записей о происходивших событиях по одной в строке. В начале строки записано число t. Если t равно:

• 1, то за ним следуют 3 числа: x1, y1 (1 ≤ x1 ≤ x, 1 ≤ y1 ≤ y) и k(-10000 ≤ k ≤ 10000) - координаты прямоугольника и величина, на которую в нём изменилось количество видимых ромашек;
• 2, то за ним следуют 4 числа: x1, y1, x2, y2 (1 ≤ x1 ≤ x2 ≤ x, 1 ≤ y1 ≤ y2 ≤ y), которые означают, что Настя попросила подсчитать количество ромашек в прямоугольниках (x', y') из области: x1 ≤ x' ≤ x2, y1 ≤ y' ≤ y2.
Формат результата
Для каждого Настиного вопроса выведите в отдельной строке искомое количество ромашек (оно может быть отрицательным).
 Входные данные:
8 8
3
1 2 2 2
1 1 1 1
2 1 1 2 2
  Результат работы:
 3
 */
using namespace std;
class FenvikTree{
private:
    vector<vector<long long>> T;
    long long n, m;
public:
    FenvikTree(long long nn, long long mm): n(nn), m(mm){
        T.assign(nn, vector<long long> (mm, 0));
    }
    void update(long long ii, long long jj, long long delta){
        for(long long i = ii; i < n; i = i | (i + 1)){
            for(long long j = jj; j < m; j = j | (j + 1)){
                T[i][j] += delta;
            }
        }
    }

    long long sum(long long x, long long y) {
        if (x >= 0 && y >= 0) {
            long long result = 0;
            for (long long i = x; i >= 0; i = (i & (i + 1)) - 1) {
                for (long long j = y; j >= 0; j = (j & (j + 1)) - 1) {
                    result += T[i][j];
                }
            }
            return result;
        } else
            return 0;
    }
};
int main() {
    long long n, m;
    cin >> n >> m;
    int numberCmd;
    cin >> numberCmd;

    FenvikTree Tree(n, m);
    for(unsigned int i = 0; i < numberCmd; ++i){
        int cmd;
        cin >> cmd;
        if(cmd == 1){
            long long x, y, delta;
            cin >> x >> y >> delta;
            Tree.update(x - 1, y - 1, delta);
        }
        else{
            long long x_1, y_1, x_2, y_2;
            cin >> x_1 >> y_1 >> x_2 >> y_2;
            cout << Tree.sum(x_2 - 1, y_2 - 1) - Tree.sum(x_2 - 1, y_1 - 2) - Tree.sum(x_1 - 2, y_2 - 1) + Tree.sum(x_1 - 2, y_1 - 2) << endl;
        }
    }
}