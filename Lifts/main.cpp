#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <set>
using namespace std;
/*
 Чтобы поднять в свой офис на N-м этаже небоскреба новый сейф, Вите опять пришлось прибегнуть к помощи грузчиков. Но за это время система оплаты изменилась. Теперь за подъем по лестнице на один этаж требуется заплатить U рублей, за спуск по лестнице на один этаж — D рублей, за внос в лифт — I рублей, за вынос из лифта — J рублей.

В офисе имеется L лифтов, каждый из которых останавливается лишь на определенных этажах.

Помогите Вите разработать маршрут подъема сейфа с первого этажа, стоимость которого наименьшая.
Формат входных данных
В первой строке входного файла записаны целые числа N, U, D, I, J, L. Каждая из следующих L строк описывает соответствующий лифт. Она начинается с числа K_i — количества этажей, на которых останавливается i-й лифт, за которым следует K_i натуральных чисел — этажи, на которых останавливается этот лифт (этажи для каждого лифта задаются в возрастающем порядке). 0 ≤ U ≤ 1000, 0 ≤ D ≤ 1000, 0 ≤ I ≤ 1000, 0 ≤ J ≤ 1000, 0 ≤ L ≤ 500, 1 ≤ N ≤ 1000000, 2 ≤ K_i ≤ 1000, K_1+K_2+…+K_L ≤ 100000. Количество этажей в небоскребе не превосходит 1000000.
Формат результата
В выходной файл выведите одно число — минимальную стоимость подъема сейфа.
 Входные данные:
10 1 1 1 1 1
2 3 7
 Результат работы:
7
 Входные данные:
10 1 1 3 2 1
2 3 7
 Результат работы:
 9
Входыне данные:
20 100 0 1 1 2
2 5 7
2 8 17
 Результат работы:
804
 */
struct Edge {
    int start, finish, w;
    Edge(int start, int finish, int w) : start(start), finish(finish), w(w)
    {}
};
struct Graph {
    int size = 0;
    vector<vector<Edge>> edges;
    Graph(int size) : size(size), edges(size) {}

    void addNewEdge(int start, int finish, int w) {
        edges[start].emplace_back(Edge(start, finish, w));
    }
};

vector<int> AlgorithmDijkstra(Graph &G, int v) {
    vector<bool> used(G.size, false);
    vector<int> d(G.size, 2009000999);
    set<pair<int, int>> MIN;
    d[v] = 0;
    MIN.insert({0, v});
    while (!MIN.empty()) {
        int minVertex = MIN.begin()->second;
        MIN.erase(MIN.begin());
        for (auto edge : G.edges[minVertex]) {
            if (d[edge.finish] > d[minVertex] + edge.w) {
                d[edge.finish] = d[minVertex] + edge.w;
                MIN.insert({d[edge.finish], edge.finish});
            }
        }
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, U, D, I, J, L;
    cin >> N >> U >> D >> J >> L >> I;
    Graph graph(1e6 + I);
    for (int i = 1; i < 1e6; ++i) {
        graph.addNewEdge(i - 1, i, U);
        graph.addNewEdge(i, i - 1, D);
    }
    for (int i = 1e6; i < 1e6 + I; ++i) {
        int floor;
        cin >> floor;
        vector<int> lift(floor);
        for (auto &floor : lift) {
            cin >> floor;
        }
        for (auto floor : lift) {
            graph.addNewEdge(floor - 1 , i, J);
            graph.addNewEdge(i, floor - 1, L);
        }
    }
    cout << AlgorithmDijkstra(graph, 0)[N - 1];
}