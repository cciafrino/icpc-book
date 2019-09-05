/**
 * Author: BenQ
 * Description: get function find prefixes of a in b
 */

vector<int> z(string str) { /// start-hash
    int n = str.size(); str += '#';
    vector<int> result(n); result[0] = n;
    while(str[result[1]+1] == str[result[1]])
        ++result[1];
    int lx = 1, rx = result[1];
    for(int i = 2; i < n; ++i) {
        if (i <= rx) result[i] = min(rx-i+1, result[i-lx]);
        while(str[i+result[i]] == str[result[i]]) ++result[i];
        if (i+result[i]-1 > rx) lx = i, rx = i+result[i]-1;
    }
    return result;
} /// end-hash
vector<int> get_prefix(string a, string b) { /// start-hash
    string str = a + '@' + b;
    vector<int> k = z(str);
    return vector<int>(k.begin()+a.size()+1, k.end());
} /// end-hash
