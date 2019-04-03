#include <iostream>
#include <vector>

using namespace std;
/*
 Дан ориентированный граф, рёбрам которого приписаны некоторые неотрицательные веса (длины). Найти длину кратчайшего пути из вершины s в вершину t.
Формат входных данных
В первой строке заданы три числа: число вершин в графе N ≤ 50, номера вершин s и t. Далее идёт матрица смежности графа, то есть N строк, в каждой из которых записано N чисел. j-ое число в i-ой строке матрицы смежности задает длину ребра, ведущего из i-й вершину в j-ую. Длины могут принимать любые значения от 0 до 1000000, число -1 означает отсутствие соответствующего ребра. Гарантируется, что на главной диагонали матрицы стоят нули.
Формат результата
Выведите одно число – минимальную длину пути. Если пути не существует, выведите -1.
 Входные данные:
3 1 2
0 -1 3
7 0 1
2 215 0
 Результат работы:
218
 */
void Floyd(vector<vector<int> >& weight, int& start, int& finish){
    int n = weight.size();
    vector<vector<int> > a(n);

    for (int i = 0; i < n; ++i){
        a[i].resize(n);
        for (int j = 0; j < n; ++j){
            a[i][j] = weight[i][j];
        }
    }
    for (int k = 0; k < n; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                int tmp = a[i][k] + a[k][j];
                if ((tmp < a[i][j] || a[i][j] < 0) && a[i][k] >= 0 && a[k][j] >= 0 ){
                    a[i][j] = tmp;
                }
            }
        }
    }
    cout << a[start][finish] << endl;

}

int main(){
    int n, start, finish;
    cin >> n >> start >> finish;
    start--;
    finish--;
    vector<vector<int> > weight(n);
    for (auto& t : weight){
        t.resize(n);
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            cin >> weight[i][j];
        }
    }

    Floyd(weight, start, finish);
}
