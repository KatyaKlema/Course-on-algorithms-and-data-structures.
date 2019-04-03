#include <iostream>
#include<vector>
using namespace std;
/*Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000). Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.
Формат входных данных
Граф задан во входном файле следующим образом: первая строка содержит числа N и M. Каждая из следующих M строк содержит описание ребра — два целых числа из диапазона от 1 до N — номера начала и конца ребра.
Формат результата
На первой строке выведите число K — количество компонент сильной связности в заданном графе. На следующей строке выведите N чисел — для каждой вершины выведите номер компоненты сильной связности, которой принадлежит эта вершина. Компоненты сильной связности должны быть занумерованы таким образом, чтобы для любого ребра номер компоненты сильной связности его начала не превышал номера компоненты сильной связности его конца.
 Входные данные:
10 19
1 4
7 8
5 10
8 9
9 6
2 6
6 2
3 8
9 2
7 2
9 7
4 5
3 6
7 3
6 7
10 8
10 1
2 9
2 7
 Результат работы:
2
1 2 2 1 1 2 2 2 2 1
 */
vector<char> used;
vector<int> order, component;

int count_component = 0;

void dfs1 (vector<vector<int> > &G, int &v) {
    used[v] = true;
    for (size_t i = 0; i < G[v].size(); ++i)
        if (!used[ G[v][i] ])
            dfs1 (G, G[v][i]);
    order.push_back (v);
}

void dfs2 (vector<vector<int> > &Gr, int &v) {
    used[v] = true;
    component.push_back (v);
    for (size_t i = 0; i < Gr[v].size(); ++i)
        if (!used[ Gr[v][i] ])
            dfs2 (Gr, Gr[v][i]);
}

int main() {
    int N, M;
    cin >> N >> M;
    int get_1, get_2;
    vector<vector<int> > G(N), Gr(N);
    vector<int> ans(N);

    for(int  i = 0; i < M; ++i){
        cin >> get_1 >> get_2;
        G[get_1 - 1].push_back(get_2 - 1);
        Gr[get_2 - 1].push_back(get_1 - 1);
    }

    used.assign (N, false);
    for (int i = 0; i < N; ++i)
        if (!used[i])
            dfs1 (G, i);

    used.assign (N, false);
    for (int i = 0; i < N; ++i) {
        int v = order[N - 1 - i];
        if (!used[v]) {
            dfs2 (Gr, v);
            int temp_size = component.size();
            for(int k = 0; k < temp_size; ++k){
                ans[component.back()] = count_component + 1;
                component.pop_back();
            }
            count_component++;
        }
    }

    cout<<count_component<<endl;

    int SIZE = ans.size();
    for(int i = 0; i < SIZE; ++i)
        cout<<ans[i]<<" ";

}