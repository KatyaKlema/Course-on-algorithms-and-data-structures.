#include <iostream>
#include <vector>
using namespace std;
/*
 В неориентированный взвешанный граф добавляют ребра. Напишите программу, которая в некоторые моменты находит сумму весов ребер в компоненте связности.
 Формат входных данных
 В первой строке записано два числа n и m (1 ≤ n,m ≤ 10^6) - количество вершин в графе и количество производимых добавлений и запросов. Далее следует m строк с описанием добавления или запроса. Каждая строка состоит из двух или четырех чисел. Первое из чисел обозначает код операции. Если первое число 1, то за ним следует еще три числа x, y, w. Это означает, что в граф добавляется ребро из вершины x в вершину y веса w. (1 ≤ x < y ≤ n, 1 ≤ w ≤ 1000). Кратные ребра допустимы. Если первое число 2, то за ним следует ровно одно число x. Это означает, что необходимо ответить на вопрос, какова сумма ребер в компоненте связности, которой принадлежит вершина x (1 ≤ x ≤ n).
 Формат результата
 Для каждой операции с кодом 2 выведите ответ на поставленную задачу. Ответ на каждый запрос выводите на отдельной строке.
 Входные данные:
 6 10
 2 1
 1 1 2 1
 2 1
 1 2 4 2
 2 1
 1 1 4 3
 2 1
 1 3 5 3
 2 5
 2 6
 Результат работы:
 0
 1
 3
 6
 3
 0
 */
vector<int> p;
vector<int> w;
void make_set(int x){
    p[x] = x;
    w[x] = 1;
}

int find_set(int x){
    if(x == p[x])
        return x;
    return p[x] = find_set(p[x]);
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
int main() {
    int n, m;
    cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    cin >> n >> m;
    p.resize(n);
    w.resize(n);
    for(int i = 0; i < n; ++i){
        make_set(i);
    }
    vector<int> weight(n, 0);
    for (int i = 0; i < m; ++i) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int x, y, w;
            cin >> x >> y >> w;
            x--; y--;
            int comp_1 = find_set(x);
            int comp_2 = find_set(y);
            weight[comp_1] += w;
            if (comp_2 != comp_1){
                weight[comp_1] += weight[comp_2];
                weight[comp_2] = weight[comp_1];
                make_union(x, y);
            }
        }
        else if (cmd == 2)
        {
            int x;
            cin >> x;
            x--;
            cout << weight[find_set(x)] << endl;
        }
    }
}
