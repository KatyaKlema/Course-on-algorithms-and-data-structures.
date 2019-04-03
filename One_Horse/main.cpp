#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
/*На шахматной доске NxN в клетке (x1, y1) стоит голодный шахматный конь. Он хочет попасть в клетку (x2, y2), где растет вкусная шахматная трава. Какое наименьшее количество ходов он должен для этого сделать?
Формат входных данных
На вход программы поступает пять чисел: N, x1, y1, x2, y2 (5 ≤ N ≤ 20, 1 ≤ x1, y1, x2, y2 ≤ N). Левая верхняя клетка доски имеет координаты (1, 1), правая нижняя — (N, N).
Формат результата
В первой строке выведите единственное число K — наименьшее необходимое число ходов коня. В каждой из следующих K+1 строк должно быть записано 2 числа — координаты очередной клетки в пути коня.
 Входные данные:
5
3 3
5 1
 Результат работы:
4
3 3
2 1
1 3
3 2
5 1
*/

vector<bool> used;
vector<int> d;
vector<int> p;
map<int, pair<int, int> >  temp_mas;


void BFS (int &v, vector<vector<int> > &G){
    queue<int> q;
    q.push(v);

    int size = G.size();
    d.resize(size);
    p.resize(size);
    used.assign(size, false);
    d.assign(size, 1e9);

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

        cout<<path.size() - 1<<endl;
        if((path.size() - 1) == 0)
            return;
        for(int i = 0; i < path.size(); ++i)
            cout << temp_mas.find(path[i])->second.first + 1<<" "<<temp_mas.find(path[i])->second.second + 1<<endl;
    }
}

int main(){
    int N;
    cin>>N;

    int x_1, y_1, x_2, y_2;

    cin >> x_1 >> y_1;
    cin >> x_2 >> y_2;

    int ch = 0;
    vector<vector<int> > mas(N);

    for(int i = 0; i < N; ++i)
        mas[i].resize(N);



    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j) {
            temp_mas[ch] = make_pair(i, j);
            mas[i][j] = ch++;
        }
    }

    vector<vector<int> > G(N * N);

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            if(i - 2 >= 0 && j - 1 >= 0)
                G[mas[i][j]].push_back(mas[i - 2][j - 1]);

            if(i - 2 >= 0 && j + 1 < N)
                G[mas[i][j]].push_back(mas[i-2][j+1]);

            if(i - 1 >= 0 && j - 2 >= 0)
                G[mas[i][j]].push_back(mas[i-1][j-2]);

            if(i - 1 >= 0 && j + 2 < N)
                G[mas[i][j]].push_back(mas[i-1][j+2]);

            if(i + 2 < N && j - 1 >= 0)
                G[mas[i][j]].push_back(mas[i+2][j-1]);

            if(i + 2 < N && j + 1 < N)
                G[mas[i][j]].push_back(mas[i+2][j+1]);

            if(i + 1 < N && j - 2 >= 0)
                G[mas[i][j]].push_back(mas[i+1][j-2]);

            if(i + 1 < N && j + 2 < N)
                G[mas[i][j]].push_back(mas[i+1][j+2]);

        }
    }


    int start = mas[x_1 - 1][y_1 - 1];
    int finish = mas[x_2 - 1 ][y_2 - 1];


    BFS(start, G);

    get_way(G, finish);

}