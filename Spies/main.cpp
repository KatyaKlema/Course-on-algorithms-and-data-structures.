#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>

using namespace std;
/*Вы - глава агенства, в котором работает N сотрудников - шпионы с кодовыми номерами от 1 до N. Шпионы были посланы в различные страны и получили кусочки важной информации. Ваша задача состоит в следующем:

1. Организовать встречи между некоторыми шпионами. На каждой такой встрече ровно два шпиона оказываются в одном месте и обмениваются всей информацией, которую получили сами или узнали от других шпионов на предыдущих встречах. Каждую из возможных встреч сложно и затратно организовать, поэтому вам известны все стоимости.

2. После того, как все встречи состоялись, выбирается группа шпионов, и они посылаются на задание по спасению мира. Для каждого шпиона известно, сколько денег он изведет, если его включить в эту группу. Задание должно быть выполнено, поэтому очень важно, чтобы выбранные шпионы все вместе обладали всей информацией, полученной агенством.

Найдите минимальную цену, за которую можно спасти мир.
Формат входных данных
Первая строка содержит натуральное число N - количество шпионов (2 ≤ N ≤ 1000). Каждая из следующих строк содержит N натуральных чисел, не превосходящих 106. Число в k-ой строке и m-ом столбце обозначает стоимость встречи между шпионами k и m и совпадает с числом в m-ой строке и k-ом столбце (если k=m, то соответствующее число будет равно 0). Следующая строка содержит n чисел, i-ое из них равно стоимости послать i-го шпиона на задание. Все стоимости являются положительными целыми числами.
Формат результата
Выведите одно число - минимальную стоимость спасения мира.
 Входные данные:
3
0 6 9
6 0 4
9 4 0
7 7 7
 Результат работы:
17
 Входные данные:
3
0 17 20
17 0 10
20 10 0
15 9 12
 Результат работы
34
 Входные данные:
5
0 3 12 15 11
3 0 14 3 20
12 14 0 11 7
15 3 11 0 15
11 20 7 15 0
5 10 10 10 10
 Результат работы:
28
 */

class DisjointSets {
private:
    vector<size_t> parents;
    vector<size_t> ranks;

public:
    DisjointSets (const size_t &size) {
        parents = vector<size_t>(size);
        ranks = vector<size_t>(size, 0);

        for (size_t i = 0; i < size; i ++)
            parents[i] = i;
    }

    size_t find (const size_t &element) {
        size_t root = element;

        while (parents[root] != root)
            root = parents[root];

        size_t current = element, previous;

        while (parents[current] != root) {
            size_t previous = current;
            current = parents[current];
            parents[previous] = root;
        }

        return root;
    }

    bool unite (size_t element1, size_t element2) {
        element1 = find(element1);
        element2 = find(element2);

        if (element1 != element2) {
            if (ranks[element1] < ranks[element2])
                swap(element1, element2);

            else if (ranks[element1] == ranks[element2])
                ranks[element1] += 1;

            parents[element2] = element1;

            return true;
        }

        return false;
    }
};


inline bool compareEdges (const tuple<int, int, int> &first, const tuple<int, int, int> &second) {
    if (get<2>(first) == get<2>(second))  {
        if (get<0>(first) == get<0>(second))
            return get<1>(first) > get<1>(second);

        return get<0>(first) > get<0>(second);
    }

    return get<2>(first) > get<2>(second);
}


unsigned long long kruskal (const vector<list<tuple<int, int, int> > > &graph) {
DisjointSets components(graph.size());
int weight = 0;

vector<tuple<int, int, int> > edgesList;

for (int vertex = 0; vertex < graph.size(); vertex ++)
for (const tuple<int, int, int> &edge: graph[vertex])
edgesList.push_back(edge);

sort(edgesList.begin(), edgesList.end(), compareEdges);

while (!edgesList.empty()) {
tuple<int, int, int> edge = edgesList.back();
edgesList.pop_back();

if (components.unite(get<0>(edge), get<1>(edge)))
weight += get<2>(edge);
}

return weight;
}

int main () {
    int verticesCount;
    cin >> verticesCount;
    vector<list<tuple<int, int, int> > > graph(verticesCount + 1);

    for (int from = 0; from < verticesCount; from ++) {
        for (int to = 0; to < verticesCount; to ++) {
            int weight;
            cin >> weight;

            if (from == to)
                continue;

            graph[from].push_back(make_tuple(from, to, weight));
            graph[to].push_back(make_tuple(to, from, weight));
        }
    }

    for (int from = 0; from < verticesCount; from ++) {
        int weight;
        cin >> weight;
        graph[from].push_back(make_tuple(verticesCount, from, weight));
        graph[verticesCount].push_back(make_tuple(from, verticesCount, weight));
    }

    cout << kruskal(graph) << endl;
    return 0;
}