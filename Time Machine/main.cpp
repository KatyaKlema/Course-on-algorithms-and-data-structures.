#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*
 Между N населенными пунктами совершаются пассажирские рейсы на машинах времени.

В момент времени 0 вы находитесь в пункте A. Вам дано расписание рейсов. Требуется оказаться в пункте B как можно раньше (то есть в наименьший возможный момент времени).

При этом разрешается делать пересадки с одного рейса на другой. Если вы прибываете в некоторый пункт в момент времени T, то вы можете уехать из него любым рейсом, который отправляется из этого пункта в момент времени T или позднее (но не раньше).
Формат входных данных
В первой строке вводится число N – количество населенных пунктов (1 ≤ N ≤ 1000). Вторая строка содержит два числа A и B – номера начального и конечного пунктов. В третьей строке задается K – количество рейсов (0 ≤ K ≤ 1000). Следующие K строк содержат описания рейсов, по одному на строке. Каждое описание представляет собой четверку целых чисел. Первое число каждой четверки задает номер пункта отправления, второе – время отправления, третье – пункт назначения, четвертое – время прибытия. Номера пунктов – натуральные числа из диапазона от 1 до N. Пункт назначения и пункт отправления могут совпадать. Время измеряется в некоторых абсолютных единицах и задается целым числом, по модулю не превышающим 10^9. Поскольку рейсы совершаются на машинах времени, то время прибытия может быть как больше времени отправления, так и меньше, или равным ему.

Гарантируется, что входные данные таковы, что добраться из пункта A в пункт B всегда можно.
Формат результата
Выведите минимальное время, когда вы сможете оказаться в пункте B.
 Входные данные:
2
1 1
2
1 1 2 10
1 10 1 9
 Результат работы:
0
 Входные данные:
1
1 1
3
1 3 1 -5
1 -5 1 -3
1 -4 1 -10
 Результат работы:
-10
 Входные данные:
5
1 2
6
1 0 3 10
4 2 2 -10
4 14 2 -7
3 10 2 10
2 0 4 2
3 10 4 12
 Результат работы:
-10
 */
struct Edge {
    int start, finish;
    Edge(int start, int finish) :
            start(start), finish(finish) {}

};
struct Graph {
    int size = 0;
    vector<std::vector<Edge>> edges;
public:

    Graph(int size) :
            size(size),
            edges(size) {}
};

vector<bool> bfs(Graph &G, int v) {
    queue<int> q;
    q.push(v);
    vector<bool> used(G.size, false);
    used[v] = true;
    while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (auto edge : G.edges[front]) {
            if (not used[edge.finish]) {
                used[edge.finish] = true;
                q.push(edge.finish);
            }
        }
    }
    return move(used);
}

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> cities(n);
    int from, to, k;
    cin >> from >> to >> k;
    --from;
    --to;
    Graph G(2 * k + 1);
    cities[from].emplace_back(make_pair(0, 0));
    vector<int> city(2 * k + 1);
    vector<int> time(2 * k + 1);
    city[0] = from;
    time[0] = 0;
    for (int i = 0; i < k; ++i) {
        int start_vertex = 2 * i + 1, finish_vertex = 2 * i + 2;
        int From, To, start_time, finish_time;
        cin >> From >> start_time >> To >> finish_time;
        cities[--From].emplace_back(make_pair(start_vertex, start_time));
        cities[--To].emplace_back(make_pair(finish_vertex, finish_time));
        city[start_vertex] = From;
        city[finish_vertex] = To;
        time[start_vertex] = start_time;
        time[finish_vertex] = finish_time;
        G.edges[start_vertex].emplace_back(Edge(start_vertex, finish_vertex));
    }
    for (auto &c : cities)
        for (auto &k_1 : c)
            for (auto &k_2 :c)
                if (k_1.second <= k_2.second)
                    G.edges[k_1.first].emplace_back(Edge(k_1.first, k_2.first));
    vector<bool> Times = bfs(G, 0);
    int MIN = 1e9;
    for(int i = 0; i < 2 * k + 1; ++i){
        if(city[i] == to && Times[i] == true && MIN > time[i]){
            MIN = time[i];
        }
    }
    cout << MIN;
}