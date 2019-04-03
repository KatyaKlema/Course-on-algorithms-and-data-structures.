#include <iostream>
#include<vector>
#include<queue>
using namespace std;
/*
 У Васи есть N свинок-копилок, свинки занумерованы числами от 1 до N. Каждая копилка может быть открыта единственным соответствующим ей ключом или разбита.

Вася положил ключи в некоторые из копилок (он помнит, какой ключ лежит в какой из копилок). Теперь Вася собрался купить машину, а для этого ему нужно достать деньги из всех копилок. При этом он хочет разбить как можно меньшее количество копилок (ведь ему еще нужно копить деньги на квартиру, дачу, вертолет…). Помогите Васе определить, какое минимальное количество копилок нужно разбить.
Формат входных данных
В первой строке содержится число N — количество свинок-копилок (1 ≤ N ≤ 100). Далее идет N строк с описанием того, где лежит ключ от какой копилки: в i-ой из этих строк записан номер копилки, в которой находится ключ от i-ой копилки.
Формат результата
Выведите единственное число: минимальное количество копилок, которые необходимо разбить.

 Входные данные:
4
2
1
2
4
 Результат работы:
2
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
    int n;
    cin>>n;
    vector<vector<int> > G(n);
    for(int i = 0; i < n; ++i){
        int t_1;
        cin>>t_1;
        G[t_1 - 1].push_back(i);
        G[i].push_back(t_1 - 1);
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


    return 0;
}