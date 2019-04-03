#include <iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
/* Дан неориентированный граф. Требуется найти все точки сочленения в нём.
 Формат входных данных
 Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).
 
 Ребро номер i описывается двумя натуральными числами b_i, e_i — номерами концов ребра (1 ≤ b_i,e_i ≤ n).
 Формат результата
 Первая строка выходного файла должна содержать одно натуральное число b — количество точек сочленения в заданном графе. На следующих b строках выведите b целых чисел — номера вершин, которые являются точками сочленения, в возрастающем порядке.
 Входные данные:
 9 12
 1 2
 2 3
 4 5
 2 6
 2 7
 8 9
 1 3
 1 4
 1 5
 6 7
 3 8
 3 9
 Результат работы:
 3
 1
 2
 3
 */

vector<bool> used;
int timer;
vector<int> fup, tin;
set<int> cutVertex;
void DFS(int &v, vector<vector<int> > &G, int parent = -1){
    used[v] = true;
    timer++;
    fup[v] = tin[v] = timer;
    int children = 0;
    int n = G.size();
    for(int i = 0; i < G[v].size(); ++i){
        int to = G[v][i];
        if(to == parent)
            continue;
        else if (used[to])
            fup[v] = min(fup[v], tin[to]);
        else {
            DFS(to, G, v);
            fup[v] = min(fup[to], fup[v]);
            if(fup[to] >= tin[v] && parent != -1)
                cutVertex.insert(v + 1);
            children++;
        }
    }
    if(parent == -1 && children > 1)
        cutVertex.insert(v + 1);

}

void find_cutVertex(vector<vector<int> > &G){
    int n = G.size();
    timer = 0;
    fup.resize(n);
    tin.resize(n);
    cutVertex.clear();
    used.assign(n, false);
    for(int i = 0; i < n; ++i){
        if(!used[i])
            DFS(i, G);
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > G(n);
    for(int i = 0; i < m; ++i){
        int l, r;
        cin >> l >> r;
        l--; r--;
        G[l].push_back(r);
        G[r].push_back(l);
    }
    find_cutVertex(G);

    cout << cutVertex.size() << endl;
    auto it = cutVertex.begin();
    while(it != cutVertex.end()){
        cout << *it++ << endl;
    }
}
