#include <iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
/*Во время контрольной работы профессор Флойд заметил, что некоторые студенты обмениваются записками. Сначала он хотел поставить им всем двойки, но в тот день профессор был добрым, а потому решил разделить студентов на две группы: списывающих и дающих списывать, и поставить двойки только первым.

У профессора записаны все пары студентов, обменявшихся записками. Требуется определить, сможет ли он разделить студентов на две группы так, чтобы любой обмен записками осуществлялся от студента одной группы студенту другой группы.
Input format
В первой строке находятся два числа N и M — количество студентов и количество пар студентов, обменивающихся записками (1 ≤ N ≤ 100, 0 ≤ M ≤ N*(N−1)/2). Далее в M строках расположены описания пар студентов: два числа, соответствующие номерам студентов, обменивающихся записками (нумерация студентов идёт с 1). Каждая пара студентов перечислена не более одного раза.
Output format
Необходимо вывести ответ на задачу профессора Флойда. Если возможно разделить студентов на две группы — выведите «YES»; иначе выведите «NO».
 Входные данные:
3 2
1 2
2 3
 Выходные данные:
YES

Входные данные:
3 3
1 2
2 3
1 3
 Выходные данные:
NO
 */

vector<bool> used;
vector<string> color;
vector<int> parent;
bool DFS(int v, vector<vector<int>>& graph) {
    used[v] = true;
    color[v] = "GRAY";
    for (int i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if (color[to] == "WHITE") {
            parent[to] = v;
            if (DFS(to, graph))
                return true;
        }
        else if (color[to] == "GRAY") {
            return true;
        }
    }
    color[v] = "BLACK";
    return false;
}

bool isContainsCicle(vector<vector<int> > &G){
    int n = G.size();
    for(int i = 0; i < n; ++i){
        if(!used[i]){
            if(DFS(i, G))
                return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > G(n);
    for (int i = 0; i < m; ++i) {
        int t_1, t_2;
        cin >> t_1 >> t_2;
        G[t_1 - 1].push_back(t_2 - 1);
        G[t_2 - 1].push_back(t_1 - 1);
    }

    vector<char> part(n, -1);
    bool ok = true;
    vector<int> q(n);
    for (int st = 0; st < n; ++st) {
        if (part[st] == -1) {
            int h = 0, t = 0;
            q[t++] = st;
            part[st] = 0;
            while (h < t) {
                int v = q[h++];
                for (int i = 0; i < G[v].size(); ++i) {
                    int to = G[v][i];
                    if (part[to] == -1)
                        part[to] = !part[v], q[t++] = to;
                    else
                        ok &= part[to] != part[v];
                }
            }
        }
    }

    if (ok)
        cout << "YES";
    else
        cout << "NO";
}