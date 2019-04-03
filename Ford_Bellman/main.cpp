#include <iostream>
#include<vector>
using namespace std;
/* Дан ориентированный граф, в котором могут быть кратные ребра и петли. Каждое ребро имеет вес, выражающийся целым числом (возможно, отрицательным). Гарантируется, что циклы отрицательного веса отсутствуют.

Требуется посчитать длины кратчайших путей от вершины номер 1 до всех остальных вершин.
Формат входных данных
Программа получает сначала число N (1 ≤ N ≤ 100) – количество вершин графа и число M (0 ≤ M ≤ 10000) – количество ребер. В следующих строках идет M троек чисел, описывающих ребра: начало ребра, конец ребра и вес (вес – целое число от -100 до 100).
Формат результата
Программа должна вывести N чисел – расстояния от вершины номер 1 до всех вершин графа. Если пути до соответствующей вершины не существует, вместо длины пути выведите число 30000.
 Входные данные:
6 4
1 2 10
2 3 10
1 3 100
4 5 -10
 Результат работы:
0 10 20 30000 30000 30000
*/

class edge{
public:
    int a, b, w;
    edge(): a(0), b(0), w(0)
    {}

    edge(int u, int v, int w): a(u), b(v), w(w)
    {}
};

vector<int> p;
vector<int> d;

void Initialize(vector<edge> &G, int n, int s){
    int MAX = 30000;
    p.resize(n);
    d.resize(n);
    d.assign(n, MAX);
    p.assign(n, 0);
    d[s] = 0;
}

void Relax(edge e){
    if(d[e.b] > d[e.a] + e.w){
        d[e.b] = d[e.a] + e.w;
        p[e.b] = e.a;
    }
}

void FordBellman(vector<edge> G, int n, int s){
    Initialize(G, n, s);
    int m = G.size();
    for(int i = 0; i < n - 1; ++i){
        for(int j = 0; j < m; ++j){
            if(d[G[j].a] < 30000)
                Relax(G[j]);
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<edge> G;
    for(int i = 0; i < m; ++i){
        int l, r, w;
        cin >> l >> r >> w;
        l--; r--;
        edge e(l, r, w);
        G.push_back(e);
    }

    FordBellman(G, n, 0);
    for(int i = 0; i < n; ++i){
        cout << d[i] << " ";
    }
}
