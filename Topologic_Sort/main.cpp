#include <iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
/*Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.
Формат входных данных
В первой строке входного файла даны два целых числа N и M (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000) - количества вершин и рёбер в графе соответственно. Далее в M строках перечислены рёбра графа. Каждое ребро задаётся парой чисел - номерами начальной и конечной вершин соответственно.
Формат результата
Вывести любую топологическую сортировку графа в виде последовательности номеров вершин. Если граф невозможно топологически отсортировать, вывести -1.
 Входные данные:
6 6
1 2
3 2
4 2
2 5
6 5
4 6
 Результат работы:
4 6 3 1 2 5
*/
set<pair<int, int> > end_time;
vector<int> visited;
void dfs_visit(int v, vector<vector<int> >& G, int& time, bool& is_cycle) {
    visited[v] = 1;
    time++;
    for (int i = 0; i < G[v].size(); ++i)
    {
        int u = G[v][i];
        if (!visited[u])
        {
            dfs_visit(u, G, time, is_cycle);
        }
        else if (visited[u] == 1)
        {
            is_cycle =  true;
        }
    }
    visited[v] = 2;
    time++;
    end_time.insert(make_pair(time, v));
}

bool dfs(vector<vector<int> > &G) {
    int time = 0;
    visited.assign(G.size(), 0);
    end_time.clear();

    for (int u = 0; u < G.size(); ++u)
    {
        if (!visited[u])
        {
            bool is_cycle = false;
            dfs_visit(u, G, time, is_cycle);
            if (is_cycle)
            {
                return true;
            }
        }
    }
    return false;
}
int main() {
    int n, m;
    cin>>n>>m;
    vector<vector<int> > G(n);
    for(int i = 0; i < m; ++i){
        int t_1, t_2;
        cin>>t_1>>t_2;
        G[t_1 - 1].push_back(t_2 - 1);

    }


    bool is_cycle = dfs(G);
    if(is_cycle == false){
        auto it = end_time.rbegin();
        while(it != end_time.rend())
            cout<<it++->second + 1<<" ";
    }
    else {
        cout<<-1<<endl;

    }



    return 0;
}