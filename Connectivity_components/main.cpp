#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/*Дан неориентированный невзвешенный граф. Необходимо посчитать количество его компонент связности и вывести их.
Input format
Во входном файле записано два числа N и M (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000). В следующих M строках записаны по два числа i и j (1 ≤ i, j ≤ N), которые означают, что вершины i и j соединены ребром.
Output format
В первой строчке выходного файла выведите количество компонент связности. Далее выведите сами компоненты связности в следующем формате: в первой строке количество вершин в компоненте, во второй — сами вершины в произвольном порядке.
 Входные данные:
 6 4
 3 1
 1 2
 5 4
 2 3
 Выходные данные:
 3
 3
 1 2 3
 2
 4 5
 1
 6
 */

vector<bool> visited;
vector<int> component;
void dfs (vector<vector<int>> &G, int &v) {
    visited[v] = true;
    component.push_back (v);
    for (int i = 0; i < G[v].size(); ++i) {
        int to = G[v][i];
        if (!visited[to])
            dfs(G, to);
    }
}

int main() {
    int n, m;
    cin>>n>>m;
    vector<vector<int> > G(n);
    for(int i = 0; i < m; ++i){
        int t_1, t_2;
        cin>>t_1>>t_2;
        G[t_1 - 1].push_back(t_2 - 1);
        G[t_2 - 1].push_back(t_1 - 1);
    }


    visited.resize(n);
    for(int i = 0; i < n; ++i)
        visited[i] = false;

    vector<pair<int, vector<int> > > ans;

    int num_of_comp = 0;
    for(int i = 0; i < n; ++i){
        if(!visited[i]) {
            num_of_comp++;
            component.clear();
            dfs(G, i);
            pair<int, vector<int>> temp;
            int size_t = component.size();
            temp.first = size_t;
            for(int j = 0; j < size_t; ++j){
                temp.second.push_back(component[j] + 1);
            }
            ans.push_back(temp);
        }

    }

    cout<<num_of_comp<<endl;

    for(int i = 0; i < ans.size(); ++i){
        cout<<ans[i].first<<endl;
        int s = ans[i].second.size();
        for(int j = 0; j < s; ++j)
            cout<<ans[i].second[j]<<" ";
        cout<<endl;
    }
    return 0;
}