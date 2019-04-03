#include <iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<map>
using namespace std;
/*Витя хочет придумать новую игру с числами. В этой игре от игроков требуется преобразовывать четырехзначные числа не содержащие нулей при помощи следующего разрешенного набора действий:
 
 1. Можно увеличить первую цифру числа на 1, если она не равна 9.
 
 2. Можно уменьшить последнюю цифру на 1, если она не равна 1.
 
 3. Можно циклически сдвинуть все цифры на одну вправо.
 
 4. Можно циклически сдвинуть все цифры на одну влево.
 
 Например, применяя эти правила к числу 1234 можно получить числа 2234, 1233, 4123 и 2341 соответственно. Точные правила игры Витя пока не придумал, но пока его интересует вопрос, как получить из одного числа другое за минимальное количество операций.
 Формат входных данных
 Во входном файле содержится два различных четырехзначных числа, каждое из которых не содержит нулей.
 Формат результата
 Программа должна вывести последовательность четырехзначных чисел, не содержащих нулей. Последовательность должна начинаться первым из данных чисел и заканчиваться вторым из данных чисел, каждое последующее число в последовательности должно быть получено из предыдущего числа применением одного из правил. Количество чисел в последовательности должно быть минимально возможным.
 Входные данные:
 1234
 4321
 Результат работы:
 1234
 2234
 3234
 4323
 4322
 4321
 */

vector<int> operation_1(vector<int> s){
    if(s[0] != 9)
        s[0]++;
    return s;
}

vector<int> operation_2(vector<int> s){
    if(s[3] != 1)
        s[3]--;
    return s;
}

vector<int> operation_3(vector<int> s){
    vector<int> temp = s;
    for(int i = 1; i < 4; ++i){
        s[i] = temp[i-1];
    }
    s[0] = temp[3];
    return s;
}

vector<int> operation_4(vector<int> s){
    vector<int> tmp = s;
    for(int i = 0; i < 3; ++i){
        s[i] = tmp[i + 1];
    }
    s[3] = tmp[0];
    return s;
}


void DFS(vector<int> &s, vector<int> &g){
    queue<vector<int>> q;
    map<vector<int>, int> d;
    set<vector<int> > visited;
    map<vector<int>, vector<int> > parent;

    int distance = 0;
    q.push(s);
    visited.insert(s);
    d[s] = 0;

    vector<int> end;
    vector<int> front = q.front();

    while(!q.empty()){
        vector<int> tmp = q.front();
        if (tmp == g){
            distance = d[tmp];
            end = g;
            break;
        }
        q.pop();

        vector<int> t_1 = operation_1(tmp), t_2 = operation_2(tmp), t_3 = operation_3(tmp), t_4 = operation_4(tmp);

        if(visited.find(t_1) == visited.end()){
            q.push(t_1);
            d[t_1] = d[tmp] + 1;
            parent[t_1] = tmp;
            visited.insert(t_1);
        }

        if(visited.find(t_2) == visited.end()){
            q.push(t_2);
            d[t_2] = d[tmp] + 1;
            parent[t_2] = tmp;
            visited.insert(t_2);
        }

        if(visited.find(t_3) == visited.end()){
            q.push(t_3);
            d[t_3] = d[tmp] + 1;
            parent[t_3] = tmp;
            visited.insert(t_3);
        }

        if(visited.find(t_4) == visited.end()){
            q.push(t_4);
            d[t_4] = d[tmp] + 1;
            parent[t_4] = tmp;
            visited.insert(t_4);
        }
    }

    vector<vector<int> > ans;
    for(int i = distance - 1; i >= 0; --i){
        ans.push_back(parent[end]);
        end = parent[end];
    }

    for(int i = distance - 1; i >= 0; --i){
        cout << ans[i][0] << ans[i][1] << ans[i][2] << ans[i][3] << endl;
    }
    cout << g[0] << g[1] << g[2] << g[3] << endl;
}

int main(){
    vector<int> s(4), g(4);

    int a, b;
    cin >> a >> b;

    s[0] = (a / 1000);
    s[1] = (a / 100) % 10;
    s[2] = (a / 10) % 10;
    s[3] = (a % 10);

    g[0] = (b / 1000);
    g[1] = (b / 100) % 10;
    g[2] = (b / 10) % 10;
    g[3] = (b % 10);

    DFS(s, g);
}
