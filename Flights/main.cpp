#include <iostream>
#include <vector>

using namespace std;
/*Профессору Форду необходимо попасть на международную конференцию. Он хочет потратить на дорогу наименьшее количество денег, поэтому решил, что будет путешествовать исключительно ночными авиарейсами (чтобы не тратиться на ночевку в отелях), а днем будет осматривать достопримечательности тех городов, через которые он будет проезжать транзитом. Он внимательно изучил расписание авиаперелетов и составил набор подходящих авиарейсов, выяснив, что перелеты на выбранных направлениях совершаются каждую ночь и за одну ночь он не сможет совершить два перелета.

Теперь профессор хочет найти путь наименьшей стоимости, учитывая что до конференции осталось K ночей (то есть профессор может совершить не более K перелетов).
Формат входных данных
В первой строке находятся числа N (количество городов), M (количество авиарейсов), K (количество оставшихся ночей), S (номер города, в котором живет профессор), F (номер города, в котором проводится конференция).

Ограничения: 2 ≤ N ≤ 100, 1 ≤ M ≤ 10^5, 1 ≤ K ≤ 100, 1 ≤ S ≤ N, 1 ≤ F ≤ N.

Далее идет M строк, задающих расписание авиарейсов. i-я строка содержит три натуральных числа: S_i, F_i и P_i, где S_i - номер города, из которого вылетает i-й рейс, F_i - номер города, в который прилетает i-й рейс, P_i - стоимость перелета i-м рейсом. 1 ≤ S_i ≤ N, 1 ≤ F_i ≤ N, 1 ≤ P_i ≤ 10^6.
Формат результата
Выведите одно число - минимальную стоимость пути, подходящего для профессора. Если профессор не сможет за K ночей добраться до конференции, выведите число -1.
 Входные данные:
4 5 2 1 4
1 2 1
2 3 1
3 4 1
1 3 3
1 4 5
 Результат работы:
4
 */
struct Edge {
    int start, finish, w;
    Edge(int start, int finish, int w) : start(start), finish(finish), w(w) {}
};
struct Graph {
    int  size = 0;
    vector<vector<Edge>> edges;

    Graph(int size) :
            size(size),
            edges(size) {}
};

vector<int> FordBellman(Graph &G, int steps, int startPoint = 0) {
    vector<int> d(G.size, 1e9),
            distance(G.size, 1e9);
    d[startPoint] = 0;
    for (int i = 0; i < steps; ++i) {
        bool flag = false;
        for (int j = 0; j < G.size; ++j) {
            if(distance[j] > d[j]){
                distance[j] = d[j];
            }
            if (d[j] == 1e9) {
                continue;
            }
            for (auto edge : G.edges[j]) {
                if (edge.w + d[j] < d[edge.finish]) {
                    distance[edge.finish] = edge.w + d[j];
                    flag = true;
                }
            }
        }
        swap(d, distance);
        if (!flag) {
            break;
        }
    }
    return d;
}

int main() {
    int city, flight, night, loc, to;
    cin >> city >> flight >> night >> loc >> to;
    Graph G(city);
    for (int i = 0; i < flight; ++i) {
        int t_1, t_2, p;
        cin >> t_1 >> t_2 >> p;
        G.edges[t_1 - 1].emplace_back(t_1 - 1, t_2 - 1, p);
    }
    vector<int> d = move(FordBellman(G, night, loc - 1));
    if (d[to - 1] == 1e9) {
        cout << -1;
    }
    else {
        cout << d[to - 1];
    }
}