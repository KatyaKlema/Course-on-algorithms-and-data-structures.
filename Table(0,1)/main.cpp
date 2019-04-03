#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
/*
 Дана таблица, состоящая из N строк и M столбцов. В каждой клетке таблицы записано одно из чисел: 0 или 1. Расстоянием между клетками (x1, y1) и (x2, y2) назовем сумму |x1-x2|+|y1-y2|. Вам необходимо построить таблицу, в клетке (i, j) которой будет записано минимальное расстояние между клеткой (i, j) начальной таблицы и клеткой, в которой записана 1. Гарантируется, что хотя бы одна 1 в таблице есть.
Формат входных данных
В первой строке вводятся два натуральных числа N и M, не превосходящих 100. Далее идут N строк по M чисел — элементы таблицы.
Формат результата
Требуется вывести N строк по M чисел — элементы искомой таблицы.
 Входные данные:
2 3
0 0 1
1 0 0
 Результат работы:
1 1 0
0 1 1
 */
enum colors{WHITE, GRAY};
vector<colors> color;
vector<int> d;
vector<int> p;

void BFS (vector<vector<int> > &G, int &s, queue<int> units){
    queue<int> q;

    int size = G.size();
    d.resize(size);
    p.resize(size);
    color.resize(size);

    for(int i = 0; i < size; ++i){
        color[i] = WHITE;
        d[i] = 1e9;
    }


    int temp_size = units.size();
    for(int  i = 0; i < temp_size; ++i){
        q.push(units.front());
        color[units.front()] = GRAY;
        d[units.front()] = 0;
        units.pop();
    }

    while(!q.empty()){
        int tmp = q.front();
        q.pop();
        int temp_size = G[tmp].size();
        for(int i = 0; i < temp_size; ++i){
            int to = G[tmp][i];
            if(color[to] == WHITE){
                color[to] = GRAY;
                q.push(to);
                d[to] = d[tmp] + 1;
                p[to] = tmp;
            }
        }
    }
}

int  get_way(vector<vector<int> > &G, int &to){
    vector<int> path;
    for (int v = to; v != -1; v = p[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    return path.size() - 1;

}

int main(){
    int N, M;
    cin>>N>>M;

    vector<vector<int>> matrix(N);

    for(int i = 0; i < N; ++i)
        matrix[i].resize(M);

    vector<vector<int> > G (N*M);
    vector<vector<int> > temp_matrix(N);

    for(int i = 0; i < N; ++i)
        temp_matrix[i].resize(M);

    int ch = 0;
    queue<int> units;
    queue<int> temp_queue;
    for(int i = 0; i < N; ++i){
        for(int  j = 0; j < M; ++j) {
            cin>>matrix[i][j];
            temp_matrix[i][j] = ch;
            ++ch;
            if(matrix[i][j] == 1)
                units.push(temp_matrix[i][j]);
        }
    }


    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            if(i - 1 >= 0)
                G[temp_matrix[i][j]].push_back(temp_matrix[i-1][j]);

            if(i + 1 < N)
                G[temp_matrix[i][j]].push_back(temp_matrix[i+1][j]);

            if(j - 1 >= 0)
                G[temp_matrix[i][j]].push_back(temp_matrix[i][j-1]);

            if(j + 1 < M)
                G[temp_matrix[i][j]].push_back(temp_matrix[i][j+1]);
        }
    }


    vector<vector<int> > ans(N);
    for(int i = 0; i < N; ++i)
        ans[i].resize(M);


    int i_0 = 0;
    BFS(G, i_0, units);


    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            ans[i][j] = d[temp_matrix[i][j]];
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }
}