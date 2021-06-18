/**
 * Author: Chris
 * Description: failure[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a pattern in a text.
 * Time: O(n)
 */
// TODO: combine with KMP Automaton 
template<typename T> struct kmp_t {
    vector<T> word; vector<int> failure;
    kmp_t(const vector<T> &_word): word(_word) { 
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
};
