#include <iostream>
#include <vector>

using namespace std;

bool contains (const string& value, const vector<string>& v) {
    bool mut = false;
    int control_sum = 0;
    int sum = 0;
    for (int i = 0; i < value.length() / 2; i++) {
        sum += value[i] - '0';
        control_sum += i + 1;
    }
    if (sum != control_sum) {
        mut = true;
    }
    for (int i = 0; i < v.size(); i++) {
        if (value == v[i]) {
            mut = true;
            break;
        }
    }
    return mut;
}

string superMutation (int n) {
    vector <string> mutations;
    if (n == 1) {
        return "1";
    }
    else {
        string previous = superMutation(n - 1);
        string first;
        for (int i = 1; i < n; i ++) {
            first += to_string(i);
        }
        mutations.push_back(first + to_string(n) + first);
        for (int i = 0; i < previous.length() - (n - 2); i++) {
            string mut = previous.substr(i, n - 1);
            if (!contains(mut + to_string(n) + mut, mutations)) {
                mutations.push_back(mut + to_string(n) + mut);
            }
        }
        for (int i = 0; i < mutations.size() - 1; i++) {
            string right = mutations[i + 1];
            string left = mutations[i];
            if (left.length() > right.length()) {
                left = left.substr(left.length() - right.length());
            }
            else if (right.length() > left.length()){
                right = right.substr(0, right.length() - left.length());
            }
            string jnt;
            int len = left.length();
            for (int i = 0; i < len; i++) {
                if (left == right) {
                    jnt = left;
                    break;
                }
                left = left.substr(1, left.length());
                right = right.substr(0, right.length() - 1);
            }
            mutations[i] = mutations[i].substr(0, mutations[i].length() - jnt.length());
            mutations[i+1] = mutations[i+1].substr(jnt.length(), mutations[i+1].length());
            mutations[i + 1] = mutations[i] + jnt + mutations[i+1];
        }
        return mutations[mutations.size() - 1];
    }
}

int main() {
    int n = 5;
    for (int i = 1; i <= n; i++) {
        string mut = superMutation(i);
        cout << "super mutation for " <<i<<" episodes: " << mut <<endl;
        cout<<"length: "<<mut.length()<<endl;
    }
}
