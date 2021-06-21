#include "../utilities/template.h"

//#include "../../content/strings/kmp.h"

template<typename T> struct kmp_t {
    vector<T> word; vector<int> failure;
	template<typename I> kmp_t(I begin, I end) { 
		for (I iter = begin; iter != end; ++iter) word.push_back(*iter);
        int n = int(size(word));
        failure.resize(n+1, 0);
        for (int s = 2; s <= n; ++s) {
            failure[s] = failure[s-1];
            while (failure[s] > 0 && word[failure[s]] != word[s-1])
                failure[s] = failure[failure[s]];
            if (word[failure[s]] == word[s-1]) failure[s] += 1;
        }
    }
    vector<int> matches_in(const vector<T> &text) {
        vector<int> result; int s = 0;
        for (int i = 0; i < int(size(text)); ++i) {
            while (s > 0 && word[s] != text[i]) s = failure[s];
            if (word[s] == text[i]) s += 1;
            if (s == (int)word.size()) {
                result.push_back(i-int(size(word))+1);
                s = failure[s];
            }
        }
        return result;
    }
	template<int K = 26, char offset = 'a'>
	auto build_automaton() {
	    word.push_back(offset + K);
	    vector<array<int, K>> table(size(word));
	    for (int a = 0; a < int(size(word)); ++a) {
		for (int b = 0; b < K; ++b) {
		    if (a > 0 && offset + b != word[a]) 
			table[a][b] = table[failure[a]][b];
		    else {
			table[a][b] = a + (offset + b == word[a]);
		    }
		}
	    }
	    return table;
	}
};

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		rep(i,0,alpha) {
			s[at] = (char)('a' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	kmp_t<char> kmp(begin(s), end(s));
	rep(i,0,sz(s)) {
		int maxlen = -1;
		rep(len,0,i+1) {
			rep(j,0,len) {
				if (s[j] != s[i+1 - len + j]) goto fail;
			}
			maxlen = len;
fail:;
		}
		assert(maxlen == kmp.failure[i+1]);
	}
}


int main() {
	// string str; cin >> str; for(auto &x: pi(str)) cout << x; cout << endl;
	// test ~3^12 strings
	rep(n,0,13) {
		string s(n, 'x');
		gen(s, 0, 3, [&]() {
			test(s);
		});
	}
	// then ~4^10 strings
	rep(n,0,11) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	
	//string S; 
	//while (cin >> S) {
	    //if (S[0] == '0') exit(0);
	    //kmp_t<char> kmp(begin(S), end(S));
	    //auto as = kmp.build_automaton();

	    //for (int i = 0; i < size(as); ++i) {
		    //cout << i << ' ';
		    //for (int j = 0; j < 26; ++j) {
			    //cout << as[i][j] << ' ';
		    //}
		    //cout << '\n';
	    //}

	//}
    
    cout<<"Tests passed!"<<endl;
}
