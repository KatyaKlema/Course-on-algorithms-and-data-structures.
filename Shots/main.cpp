#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <queue>
#include<map>
#include<set>
#include<algorithm>
#include<stack>
using namespace std;
/*
 Третий день не встает Иван с печи. Все ему надоело: и балалайка, и водка. "Так больше нельзя!" - сказал себе Иван, взял револьвер, надел валенки и ушел, хлопнув дверью.

"Здравствуй, Ваня!" - сказал ручной медведь Миша, увидев перед собой хмурого Ивана, стоящего на пороге его берлоги - "С чем пожаловал?". "Я хочу сыграть с тобой в одну игру" - сказал Иван, достав револьвер из-за пазухи. Миша молча сел за стол. Иван приблизился к столу - "Вращай!" - сказал он и дал пистолет в лапы медведю.

Медведь увидел перед собой револьвер неизвестной модели с вращающимся барабаном. В некоторые пазы были вставлены пули. Все пазы видны, кроме одного - основного, из которого в ствол подается пуля. Медведь крутанул барабан.

- Что дальше? - спросил Миша.

- Стреляй. Либо в себя, либо в меня.

Медведь был очень предан своему хозяину, поэтому не мог его убить. Медведь снова глянул на барабан и захотел вычислить, будет ли сейчас произведен выстрел. Ведь от этого зависит его дальнейшая судьба...
Формат входных данных
Первая строка содержит целое число n (2 ≤ n ≤ 2*106) - количество пазов в барабане револьвера.

Во второй строке задана строка a, описывающая состояние барабана револьвера до вращения. Строка состоит из n - 1 символов, где ai = 0, если в i-м пазе по часовой стрелке, начиная от дула, нет пули, и ai = 1, если есть.

В третьей строке задана строка b, описывающая состояние барабана револьвера после вращения в таком же формате.

Гарантируется, что входные данные непротиворечивы.
Формат результата
Выведите Yes, если выстрел точно будет произведен, No, если выстрела точно не будет или Random, если нельзя точно установить, будет ли выстрел.
 Входные данные:
6
11111
01111
 Результат работы:
Yes
 Входные данные:
5
1100
0110
 Результат работы:
No
 Входные данные:
5
1001
1001
 Результат работы:
Random
 */
vector<int> PrefFun(string str) {
    vector<int> pref(str.size());
    pref[0] = 0;
    for (int i = 1; i < str.size(); ++i) {
        int tmp = pref[i - 1];
        while (tmp > 0 && str[tmp] != str[i]) {
            tmp = pref[tmp - 1];
        }
        pref[i] = str[i] == str[tmp] ? tmp + 1 : 0;
    }

    return pref;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string pre_shoot, after_shoot;
    cin >> n;
    cin >> pre_shoot >> after_shoot;
    bool shoot = 0, no_shoot = 0;
    vector<int> res = PrefFun(pre_shoot + '#' + after_shoot + '1' + after_shoot);
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] == pre_shoot.size()) {
            shoot = true;
        }
    }
    res = PrefFun(pre_shoot + '#' + after_shoot + '0' + after_shoot);
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] == pre_shoot.size()) {
            no_shoot = true;
        }
    }
    if (shoot && no_shoot) {
        cout << "Random";
    } else {
        if (shoot) {
            cout << "Yes";
        } else {
            cout << "No";
        }
    }
    return 0;
}