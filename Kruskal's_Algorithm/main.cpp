#include <iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
/*
 От вас требуется определить вес минимального остовного дерева для неориентированного взвешенного связного графа.
 
 Входные данные
 В первой строке входных данных находятся числа N и M (1 <= N <= 100; 1 <= M <= 6000), где N – количество вершин в графе, а M – количество рёбер. В каждой из последующих M строк записано по тройке чисел A, B, C, где A и B – номера вершин, соединённых ребром, а C – вес ребра (натуральное число, не превышающее 30000)
 
 Выходные данные
 Вывести одно число – искомый вес.
 Входные данные:
 3 3
 1 2 1
 2 3 2
 3 1 3
 Результат работы:
 3
 */

vector<bool> visited;
vector<int> component;

vector<int> p;
vector<int> w;

void make_set(int x){
    p[x] = x;
    w[x] = 1;
}

int find_set(int x){
    if(p[x] == x)
        return x;
    return p[x]= find_set(p[x]);
}

void make_union(int x, int y){
    x = find_set(x);
    y = find_set(y);
    
    if(x != y){
        if(w[x] < w[y])
            swap(x, y);
        p[y] = x;
        w[x] += w[y];
    }
}

int Kruskal(set<pair<int, pair<int, int> > > &G){
    int ans_weight = 0;
    while(!G.empty()){
        pair<int, pair<int, int> >  temp = *G.begin();
        G.erase(G.begin());
        pair <int, int> edge = temp.second;
        int current_weight = temp.first;
        if(find_set(edge.first) != find_set(edge.second)) {
            ans_weight += current_weight;
            make_union(edge.first, edge.second);
        }
    }
    return ans_weight;
}

int main(){
    int n, m;
    cin >> n >> m;
    p.resize(n);
    w.resize(n);
    set<pair<int, pair<int, int> > >G;
    for(int i = 0; i < n; ++i)
        make_set(i);
    
    for(int i = 0; i < m; ++i){
        int l, r, w;
        cin >> l >> r >> w;
        l--; r--;
        pair<int, pair<int, int> > temp = make_pair(w, make_pair(l, r));
        G.insert(temp);
    }
    
    cout << Kruskal(G) << endl;
}

