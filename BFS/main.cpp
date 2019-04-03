#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
/*
 Вам дан неориентированный граф. Найдите кратчайший путь от вершины a до вершины b.
Формат входных данных
В первой строке входного файла идут целые числа n и m (1 ≤ n ≤ 50000, 1 ≤ m ≤ 100000) количества вершин и рёбер соответственно. Во второй строке идут целые числа a и b - стартовая и конечная вершины соответственно. Далее идут m строк, описывающих рёбра.
Формат результата
Если пути между a и b нет, выведите единственное число -1. Иначе выведите в первой строке число l - длину кратчайшего пути между этими двумя вершинами в рёбрах, а во второй строке выведите l + 1 число - вершины этого пути.
 Входные данные:
4 5
1 4
1 3
3 2
2 4
2 1
2 3
 Результат работы:
2
1 2 4
 Входные данные:
4 4
2 3
2 1
2 4
4 3
1 3
 Результат работы:
2
2 1 3
 */
vector<bool> used;
vector<int> d;
vector<int> p;

void BFS (int &v, vector<vector<int> > &G){
    queue<int> q;
    q.push(v);

    int size = G.size();
    d.resize(size);
    p.resize(size);
    used.resize(size);

    d.assign(size, 1e9);
    used.assign(size, false);

    used[v] = true;
    p[v] = -1;
    d[v] = 0;

    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        int temp_size = G[tmp].size();
        for(int i = 0; i < temp_size; ++i){
            int to = G[tmp][i];
            if(!used[to]){
                used[to] = true;
                q.push(to);
                d[to] = d[tmp] + 1;
                p[to] = tmp;
            }
        }
    }
}

void get_way(vector<vector<int> > &G, int &to){
    if(!used[to]) {
        cout << -1;
    }
    else{
        vector<int> path;
        for(int v = to; v != -1; v = p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());

        cout << path.size() - 1 << endl;
        for(int i = 0; i < path.size(); ++i)
            cout << path[i] + 1 << " ";
    }
}


int main(){
    int n, m;
    cin >> n >> m;
    int s_0, to_0;
    cin >> s_0 >> to_0;
    vector<vector<int> > G(n);
    for(int i = 0; i < m; ++i){
        int t_1, t_2;
        cin >> t_1 >> t_2;
        G[t_1 - 1].push_back(t_2 - 1);
        G[t_2 - 1].push_back(t_1 - 1);
    }
    int s = s_0 - 1, to = to_0 - 1;
    BFS(s, G);

    get_way(G, to);
}