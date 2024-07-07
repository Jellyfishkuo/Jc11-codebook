#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
/* 核心: 最大點獨立集 = |V| - |最大匹配數|，用匈牙利演算法找出最大匹配數 */
struct Student {
    int height;
    char sex;
    string musicStyle;
    string sport;
    bool canMatch(const Student& other) {
        return ((abs(this->height - other.height) <= 40) && (this->musicStyle == other.musicStyle)
            && (this->sport != other.sport));
    }
    friend istream& operator >> (istream& input, Student& student);
};
vector<Student> boys;
vector<Student> girls;
vector<vector<int>> G;
bool used[505];
int p[505]; //pair of boys and girls -> p[j] = i 代表i男生連到j女生
istream& operator >> (istream& input, Student& student) {
    input >> student.height >> student.sex >> student.musicStyle >> student.sport;
    return input;
}
bool match(int i) {
    for (int j: G[i]) {
        if (!used[j]) {
            used[j] = true;
            if (p[j] == -1 || match(p[j])) {
                p[j] = i;
                return true;
            }
        }
    }
    return false;
}
void maxMatch(int n) {
    memset(p, -1, sizeof(p));
    int res = 0;
    for (int i = 0; i < boys.size(); ++i) {
        memset(used, false, sizeof(used));
        if (match(i))
            ++res;
    }
    cout << n - res << '\n';
}
int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        boys.clear();
        girls.clear();
        G.assign(n + 5, vector<int>());
        Student student;
        for (int i = 0; i < n; ++i) {
            cin >> student;
            if (student.sex == 'M')
                boys.emplace_back(student);
            else
                girls.emplace_back(student);
        }
        for (int i = 0; i < boys.size(); ++i) {
            for (int j = 0; j < girls.size(); ++j) {
                if (boys[i].canMatch(girls[j])) {
                    G[i].emplace_back(j);
                }
            }
        }
        maxMatch(n);
    }
    return 0;
}