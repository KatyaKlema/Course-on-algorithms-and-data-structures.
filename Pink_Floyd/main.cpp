#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

/*
 Группа Pink Floyd собирается дать новый концертный тур по всему миру. По предыдущему опыту группа знает, что солист Роджер Уотерс постоянно нервничает при перелетах. На некоторых маршрутах он теряет вес от волнения, а на других — много ест и набирает вес.

Известно, что чем больше весит Роджер, тем лучше выступает группа, поэтому требуется спланировать перелеты так, чтобы вес Роджера на каждом концерте был максимально возможным. Группа должна посещать города в том же порядке, в котором она дает концерты. При этом между концертами группа может посещать промежуточные города.
Формат входных данных
Первая строка входного файла содержит три натуральных числа n, m и k — количество городов в мире, количество рейсов и количество концертов, которые должна дать группа соответственно (n ≤ 100, m ≤ 10^4, 2 ≤ k ≤ 10^4). Города пронумерованы числами от 1 до n. Следующие m строк содержат описание рейсов, по одному на строке. Рейс номер i описывается тремя числами b_i, e_i и w_i — номер начального и конечного города рейса и предполагаемое изменение веса Роджера в миллиграммах (1 ≤ b_i, e_i ≤ n, −10^5 ≤ w_i ≤ 10^5). Последняя строка содержит числа a_1, a_2, ..., a_k — номера городов, в которых проводятся концерты. В начале концертного тура группа находится в городе a_1. Гарантируется, что группа может дать все концерты.
Формат результата
Первая строка выходного файла должна содержать число s — количество рейсов, которые должна сделать группа. Вторая строка должна содержать s чисел — номера используемых рейсов. Если существует такая последовательность маршрутов между концертами, что Роджер будет набирать вес неограниченно, то первая строка выходного файла должна содержать строку “infinitely kind”.
 Входные данные:
4 8 5
1 2 -2
2 3 3
3 4 -5
4 1 3
1 3 2
3 1 -2
3 2 -3
2 4 -10
1 3 1 2 4
 Результат работы:
6
5 6 5 7 2 3

 Входные данные:
4 8 5
1 2 -2
2 3 3
3 4 -5
4 1 3
1 3 2
3 1 -2
3 2 -3
2 4 10
1 3 1 2 4
 Результат работы:
infinitely kind
 */
struct Edge {
    int start, finish, w;
    Edge(int start, int finish, int w) : start(start), finish(finish), w(w) {}
};
struct Graph {

    int size = 0;
    vector<vector<Edge>> edges;
    vector<vector<int> >  dist;
    vector<vector<int> >  next;

    Graph(int size) :
            size(size),
            edges(size) {
        next = vector<vector<int> >(size, vector<int>(size, -1));
    }

    void addNewEdge(int from, int to, int weight) {
        edges[from].emplace_back(Edge(from, to, weight));
        next[from][to] = to;
    }

    vector<vector<int>> Matrix() {
        vector<vector<int> > matrix(size, vector<int>(size, 1e9));
        for (auto v : edges) {
            for (auto edge : v) {
                matrix[edge.start][edge.finish] = edge.w;
            }
        }

        for (int i = 0; i < size; ++i) {
            matrix[i][i] = 0;
        }
        return move(matrix);
    }

};

void Floyd(Graph &G) {
    vector<vector<int> > &d = G.dist;
    d = move(G.Matrix());
    for (int k = 0; k < G.size; ++k)
        for (int i = 0; i < G.size; ++i)
            for (int j = 0; j < G.size; ++j)
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    G.next[i][j] = G.next[i][k];
                }
}

void pushWay(int start, int finish, vector<int> &way, Graph &G, bool &IsNotCycle, map<pair<int, int>, int> &flight) {
    if (G.dist[start][start] < 0) {
        IsNotCycle = true;
        return void();
    }
    while (start != finish) {
        way.emplace_back(flight[make_pair(start, G.next[start][finish])]);
        start = G.next[start][finish];
        if (G.dist[start][start] < 0) {
            IsNotCycle = true;
            return void();
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >>k;
    Graph G(n);
    map<std::pair<int, int>, int> flights;
    for (int i = 0; i < m; ++i) {
        int t_1, t_2, x;
        cin >> t_1 >> t_2 >> x;
        flights[make_pair(t_1 - 1, t_2 - 1)] = i + 1;
        G.addNewEdge(t_1 - 1, t_2 - 1, -x);
    }
    Floyd(G);
    bool flag = false;
    vector<int> lst(k), way;
    for (auto &i : lst) {
        cin >> i;
        --i;
    }
    for (int i = 1; i < k; ++i) {
        pushWay(lst[i - 1], lst[i], way, G, flag, flights);
        if (flag) {
            cout << "infinitely kind";
            return 0;
        }
    }
    cout << way.size() << endl;
    for (auto i : way) {
        cout << i << ' ';
    }
}