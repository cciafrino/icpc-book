/**
 * Author: Chris
 * Source: saketh
 * Description:
 * Status: tested
 */

template<int MIN_CHAR, int SIGMA> struct Aho {
    struct node {
        int depth;
        array<int, SIGMA> child_links; // trie links + failure links
        int dict_index = -1; // index of this node's word in the dict
        int suffix_link = 0;  // link to longest proper suffix that exists in the trie
        int dict_suffix_link = 0; // link to longest suffix that exists in dict
        int count_suffixes_in_dict = 0; // number of suffixes that are words in dict
        node(int depth_) : depth(depth_) { child_links.fill(0); }
        // maybe add some other stuff here?
    };
    
	vector<node> data;
    vector<int> dictionary_word_links;

    int& child_link(int loc, int c) { return data[loc].child_links[c - MIN_CHAR]; }
    int child_link(int loc, int c) const { return data[loc].child_links[c - MIN_CHAR]; }

    int dict_proper_suffix_link(int loc) const {
        return data[data[loc].suffix_link].dict_suffix_link;
    }

    Aho() : data(1, node(0)) {}
    template<typename I>
    Aho(I begin, I end) : data(1, node(0)) {
        for (I iter = begin; iter != end; ++iter) add(*iter);
        build();
    }

    template<typename S>
    void add(const S& s) {
        int loc = 0;
        for (auto c_ : s) {
            int c = c_;
            assert(MIN_CHAR <= c && c < MIN_CHAR + SIGMA);
            if (!child_link(loc, c)) {
                child_link(loc, c) = int(data.size());
                data.push_back(node(data[loc].depth + 1));
            }
            loc = child_link(loc, c);
        }
        if (data[loc].count_suffixes_in_dict == 0) {
            data[loc].dict_suffix_link = loc;
            data[loc].dict_index = int(dictionary_word_links.size());
        }
        data[loc].count_suffixes_in_dict++;
        dictionary_word_links.push_back(loc);
    }

    vector<vector<int>> children;
    vector<pair<int, int>> dfs_ranges;
    void build() {
        children.resize(int(data.size()));

        vector<int> bfs;
        for (int nxt : data[0].child_links) if (nxt) bfs.push_back(nxt);
        for (int v = 0; v < int(bfs.size()); ++v) {
            int loc = bfs[v];
            int parent = data[loc].suffix_link;

            children[parent].push_back(loc);
            if (data[loc].dict_suffix_link == 0)
                data[loc].dict_suffix_link = data[parent].dict_suffix_link;
            data[loc].count_suffixes_in_dict += data[parent].count_suffixes_in_dict;

            for (int c = MIN_CHAR; c < MIN_CHAR + SIGMA; ++c) {
                int& trie_child = child_link(loc, c);
                if (trie_child) {
                    bfs.push_back(trie_child);
                    data[trie_child].suffix_link = child_link(parent, c);
                } else trie_child = child_link(parent, c);
            }
        }

        dfs_ranges.resize(data.size());

        int visited = 0;
        auto dfs = [&](auto self, int loc) -> void {
            dfs_ranges[loc].first = visited++;
            for (int nxt : children[loc])
                self(self, nxt);
            dfs_ranges[loc].second = visited;
        };
        dfs(dfs, 0);
    }

    template<typename V>
    void copy_results_for_duplicate_dictionary_entries(vector<V> &results) const {
        for (int dict_index = 0; dict_index < int(dictionary_word_links.size()); dict_index++) {
            int loc = dictionary_word_links[dict_index];
            if (data[loc].dict_index != dict_index) {
                results[dict_index] = results[data[loc].dict_index];
            }
        }
    }

    /* Returns the number of matches of each dictionary word.
     * Linear in text length and number of dictionary words.
     */
    template<typename S>
    vector<int> count_matches(const S& text) const {
        vector<int> count(dictionary_word_links.size());
        vector<vector<int>> found_with_length;

        auto record_match = [&](int loc, int quantity) {
            int dict_index = data[loc].dict_index;
            if (dict_index == -1) return;

            if (count[dict_index] == 0) {
                if (data[loc].depth >= found_with_length.size())
                    found_with_length.resize(data[loc].depth + 1);
                found_with_length[data[loc].depth].push_back(loc);
            }
            count[dict_index] += quantity;
        };

        int loc = 0;
        for (auto c_ : text) {
            int c = c_;
            assert(MIN_CHAR <= c && c < MIN_CHAR + SIGMA);
            loc = child_link(loc, c);
            record_match(data[loc].dict_suffix_link, 1);
        }
        for (int match_length = int(found_with_length.size()) - 1; match_length > 0; match_length--) {
            for (int loc : found_with_length[match_length])
                record_match(dict_proper_suffix_link(loc), count[data[loc].dict_index]);
        }

        copy_results_for_duplicate_dictionary_entries(count);
        return count;
    }

    /* Returns the starting index of every match of each dictionary word.
     * Linear in the text length, number of dictionary words, and total number of matches.
     */
    template<typename S>
    vector<vector<int>> indices_of_matches(const S& text) const {
        vector<vector<int>> indices(dictionary_word_links.size());

        int loc = 0;
        for (int a = 0; a < int(text.size()); ++a) {
            int c = text[a];
            assert(MIN_CHAR <= c && c < MIN_CHAR + SIGMA);
            loc = child_link(loc, c);
            for (int par = data[loc].dict_suffix_link; par != 0; par = dict_proper_suffix_link(par)) {
                indices[data[par].dict_index].push_back(a + 1 - data[par].depth);
            }
        }

        /* Notable fact: before duplication, the total number of matches is at most
         * (text length) * (number of distinct dictionary word lengths), which is
         * O(text length * sqrt(sum of dictionary word lengths)).
         */
        copy_results_for_duplicate_dictionary_entries(indices);
        return indices;
    }

    /* Returns the total number of matches over all dictionary words.
     * Duplicate dictionary entries each contribute to the total match count.
     * Linear in the text length.
     */
    template<typename S>
    int64_t count_total_matches(const S& text) const {
        int64_t count = 0;

        int loc = 0;
        for (int a = 0; a < int(text.size()); ++a) {
            int c = text[a];
            assert(MIN_CHAR <= c && c < MIN_CHAR + SIGMA);
            loc = child_link(loc, c);
            count += data[loc].count_suffixes_in_dict;
        }

        return count;
    }
};

