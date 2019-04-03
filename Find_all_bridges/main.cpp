#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
/*Дан неориентированный граф. Требуется найти все мосты в нём.
Формат входных данных
Первая строка входного файла содержит два натуральных числа n и m — количества вершин и рёбер графа соответственно (1 ≤ n ≤ 20000, 1 ≤ m ≤ 200000).

Следующие m строк содержат описание рёбер по одному на строке. Ребро номер i описывается двумя натуральными числами b_i, e_i — номерами концов ребра (1 ≤ b_i,e_i ≤ n).
Формат результата
Первая строка выходного файла должна содержать одно натуральное число b — количество мостов в заданном графе. На следующих b строках выведите b целых чисел — номера рёбер, которые являются мостами, в возрастающем порядке. Рёбра нумеруются с единицы в том порядке, в котором они заданы во входном файле.

 Входные данные:
6 7
1 2
2 3
3 4
1 3
4 5
4 6
5 6

Результат работы:
1
3
*/

vector<bool> used;
vector<int> fup, tin;
int timer;
void DFS(int v, vector<vector<pair<int, int> > > &G, vector<int> & result, int from = -1){
    used[v] = true;
    fup[v] = tin[v] = timer++;
    for(int i = 0; i < G[v].size(); ++i){
        int to = G[v][i].first;
        int index = G[v][i].second;
        if(index == from)
            continue;
        else if(used[to])
            fup[v] = min(fup[v], tin[to]);
        else{
            DFS(to, G, result, index);
            fup[v] = min(fup[v], fup[to]);
            if(fup[to] > tin[v])
                result.push_back(index);
        }
    }
}

vector<int> FindBridges(vector<vector<pair<int, int > > > &G){
    int n = G.size();
    timer = 0;
    used.assign(n, false);
    fup.resize(n);
    tin.resize(n);
    vector<int> result;
    for(int i = 0; i < n; ++i){
        if(!used[i])
            DFS(i, G, result);
    }
    return result;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int> > > G(n);
    int number = 1;
    for(int i = 0; i < m; ++i){
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        G[l].push_back(make_pair(r, number));
        G[r].push_back(make_pair(l, number));
        ++number;
    }
    vector<int> result = FindBridges(G);
    cout << result.size() << endl;
    sort(result.begin(), result.end());
    for(int i = 0; i < result.size(); ++i){
        cout << result[i] << endl;
    }

}
