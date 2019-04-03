#include <iostream>
#include <vector>
#include<algorithm>
/*
Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог (вернее, мостов). По каждому мосту можно перемещаться в обе стороны. Был разработан план очередности строительства мостов и известно, что после постройки всех мостов можно будет проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные острова).

Однако, этот момент может наступить до того, как будут построены все мосты. Ваша задача состоит такое минимальное количество мостов, после постройки которых (в порядке строительства по плану) можно будет попасть с любого острова на любой другой.
Формат входных данных
Первая строка содержит два числа: N — число островов (1 ≤ N ≤ 100000) и M — количество мостов в плане (1 ≤ M ≤ 200000). В каждой следующей строке содержится описание моста – два числа x и y (0 ≤ x, y ≤ N-1) – номера соединяемых островов.
Формат результата
Выведите в выходной файл одно число – минимальное количество построенных мостов, по которым можно попасть с любого острова на любой.

 Входные данные:
 4 5
 0 1
 0 2
 1 2
 2 3
 3 0

 Результат работы:
 4
 */
using namespace std;
class DSU{
public:
    vector<int> p;
    vector<int> size;

    DSU(int _n){
        p.resize(_n);
        size.resize(_n);
        for(int i = 0; i < _n; ++i) {
            p[i] = i;
            size[i] = 1;
        }
    }

    int find_set(int x){
        if(p[x] == x)
            return x;
        return p[x] = find_set(p[x]);
    }

    void make_union(int x, int y){
        x = find_set(x);
        y = find_set(y);
        if(x != y){
            if(size[x] < size[y])
                swap(x, y);
            p[y] = x;
            size[x] += size[y];
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    int count = 1;
    for(int  i = 0; i < m; ++i){
        int l, r;
        cin >> l >> r;
        dsu.make_union(l, r);
        if(dsu.size[dsu.find_set(l)] == n){
            cout << count << endl;
            return 0;
        }
        count++;
    }
}