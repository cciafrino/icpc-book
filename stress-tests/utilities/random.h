#pragma once
#include <cstdint>
#include <cassert>

static std::mt19937_64 twister(1337);

// returns random int in [0, hi), like Python's random.randrange
int randRange(int hi) {
    return rand() % hi;
}

bool randBool() {
	return !!(rand() & 128);
}

// returns random int in [lo, hi), like Python's random.randrange
int randRange(int lo, int hi) {
    return lo + randRange(hi - lo);
}

// returns random int in [0, 2^64)
uint64_t randU64() {
    uint64_t a = rand() & 0xffffff;
    uint64_t b = rand() & 0xffffff;
    uint64_t c = rand() & 0xffff;
    return a << 40 | b << 16 | c;
}

uint64_t randRange(uint64_t hi) {
    return randU64() % hi;
}

uint64_t randRange(uint64_t lo, uint64_t hi) {
    return lo + randRange(hi - lo);
}

int64_t randRange(int64_t hi) {
    assert(hi > 0);
    return (int64_t) randRange((uint64_t) hi);
}

int64_t randRange(int64_t lo, int64_t hi) {
    return lo + randRange(hi - lo);
}

// returns random int in [0, hi], like Python's random.randint
int randIncl(int hi) {
    return randRange(hi + 1);
}

// returns random int in [lo, hi], like Python's random.randint
int randIncl(int lo, int hi) {
    return randRange(lo, hi + 1);
}

int64_t randIncl(int64_t hi) {
    return randRange(hi + 1);
}

int64_t randIncl(int64_t lo, int64_t hi) {
    return randRange(lo, hi + 1);
}

// returns uniformly random double in [lo, hi)
double randDouble(double lo, double hi) {
    static mt19937_64 rng(time(0));
    std::uniform_real_distribution<> dis(lo, hi);
    return dis(rng);
}

// int -> double based on IEEE 754 bitpattern
double bitPatternToDouble(uint64_t x) {
    union {
        double d;
        uint64_t i;
    } u;
    u.i = x;
    return u.d;
}

// double -> int based on IEEE 754 bitpattern
uint64_t doubleToBitPattern(double x) {
    union {
        double d;
        uint64_t i;
    } u;
    u.d = x;
    return u.i;
}

// random double
double randDoubleUniformBitPattern() {
    return bitPatternToDouble(randU64());
}

// random double in [lo, hi), with any bit pattern being equally likely
double randDoubleUniformBitPattern(double lo, double hi) {
    return bitPatternToDouble(randRange(doubleToBitPattern(lo), doubleToBitPattern(hi)));
}

// add ~y ulps (units of last precision) to x, similar to calling next_after y times
double addUlps(double x, int64_t y) {
    if (x == 0 && y < 0) {
        return -addUlps(-x, -y);
    }
    return bitPatternToDouble(doubleToBitPattern(x) + y);
}

// random int in [-lim, lim], perturbed by a few ulps
double randNearIntUlps(int lim, int64_t ulps = 5) {
    return addUlps(randIncl(-lim, lim), randIncl(-ulps, ulps));
}

// random int in [-lim, lim], perturbed by a random double in [-eps, eps]
double randNearIntEps(int lim, double eps) {
    return randIncl(-lim, lim) + randDouble(-eps, eps);
}

// like random_shuffle but uses rand() as RNG source
template<class T>
void shuffle_vec(T& vec) {
    random_shuffle(begin(vec), end(vec), [](int lim) { return rand() % lim; });
}
// Random integer between l and r (inclusive).
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> randRange(T l, T r) {
    assert(l <= r);
    std::uniform_int_distribution<T> uniformRand(l, r);
    return uniformRand(twister);
}

// Random real number between l and r (inclusive).
template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> randRange(T l, T r) {
    assert(l <= r);
    std::uniform_real_distribution<T> uniformRand(l, r);
    return uniformRand(twister);
}

// Returns `true` with probability p, `false` with probability 1-p.
inline bool randBool(double p) {
    std::bernoulli_distribution dist(p);
    return dist(twister);
}

// Random number from gamma distribution.
inline double randGamma(double alpha = 1, double beta = 1) {
    std::gamma_distribution<> dist(alpha, beta);
    return dist(twister);
}

// Random number from beta distribution. Can be used to generate biased values.
// For example, k-th smallest value of n samples from Uniform[0,1] has distribution Beta[k,n+1-k].
inline double randBeta(double alpha, double beta) {
    double x = randGamma(alpha);
    double y = randGamma(beta);
    return x / (x + y);
}

// Random integer between l and r (inclusive) rounded from beta distribution.
// Can be used to generate biased values.
// For example, k-th smallest value of n samples from Uniform[0,1] has distribution Beta[k,n+1-k].
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> randBeta(T l, T r, double alpha, double beta) {
    assert(l <= r);
    double x = randBeta(alpha, beta) * double(r - l);
    return std::clamp(l + (T)llround(x), l, r);
}

// Random element from given collection.
template<typename CollectionT>
typename CollectionT::value_type randElement(const CollectionT& c) {
    assert(!c.empty());
    return c[randIncl(0, int(c.size()) - 1)];
}

// Random element from initializer list.
// Example usage: randElement({"aa", "bb", "cc"}).
template<typename T>
T randElement(const std::initializer_list<T>& c) {
    return randElement(std::vector<T>(c.begin(), c.end()));
}

// Permutes elements in given collection randomly.
template<typename CollectionT>
void randShuffle(CollectionT& c) {
    std::shuffle(c.begin(), c.end(), twister);
}

// Returns random permutation of {mn, ..., mx}.
template<typename T>
std::vector<T> randPermutation(T mn, T mx) {
    assert(mx-mn+1 >= 0);
    std::vector<T> vec(mx - mn + 1);
    std::iota(vec.begin(), vec.end(), mn);
    randShuffle(vec);
    return vec;
}

// Fills with K random values (with repetitions) from a range [mn, mx].
template<typename It, typename T>
void randWithRepetitions(It begin, It end, T mn, T mx) {
    assert(begin <= end && mn <= mx);
    std::generate(begin, end, std::bind(randRange<T>, mn, mx));
}

// Returns K random values (with repetitions) from a range [mn, mx].
template<typename T>
std::vector<T> randWithRepetitions(T mn, T mx, int k) {
    assert(k >= 0);
    std::vector<T> values(k);
    randWithRepetitions(values.begin(), values.end(), mn, mx);
    return values;
}

// Returns K random values (with repetitions) from a range [mn, mx].
// Can be used in structured bindings: auto [a, b, c] = randWithRepetitions<3>(1, 10);
template<size_t k, typename T>
std::array<T, k> randWithRepetitions(T mn, T mx) {
    std::array<T, k> values;
    randWithRepetitions(values.begin(), values.end(), mn, mx);
    return values;
}

// Returns random string with characters from range [mn, mx].
std::string randString(char mn, char mx, int k) {
    assert(k >= 0);
    std::string str(k, '.');
    randWithRepetitions(str.begin(), str.end(), mn, mx);
    return str;
}

// Fills with K random values (without repetitions) from a range [mn, mx].
template<typename It, typename T>
std::enable_if_t<std::is_integral_v<T>> randDistinct(It begin, It end, T mn, T mx) {
    // Adapted from testlib.h
    assert(begin <= end && mn <= mx);
    int64_t size = int64_t(end - begin);
    int64_t range = int64_t(mx - mn + 1);
    assert(range >= size);

    if (size <= 8) {
        // Faster O(n^2) for very small collections.
        for (It it = begin; it < end; it++) {
            do {
                *it = randRange(mn, mx);
            } while (std::find(begin, it, *it) != it);
        }
    } else if (size*20 < range) {
        std::set<T> vals;
        while (begin < end) {
            T x = randRange(mn, mx);
            if (vals.insert(x).second) {
                *begin++ = x;
            }
        }
    } else {
        assert(range < int(1e9));
        auto p = randPermutation(mn, mx);
        copy(p.begin(), p.begin()+size, begin);
    }
}

// Returns K random values (without repetitions) from a range [mn, mx].
template<typename T>
std::vector<T> randDistinct(T mn, T mx, int k) {
    std::vector<T> values(k);
    randDistinct(values.begin(), values.end(), mn, mx);
    return values;
}

// Returns K random values (without repetitions) from a range [mn, mx].
// Can be used in structured bindings: auto [a, b, c] = randDistinct<3>(1, 10);
template<size_t k, typename T>
std::array<T, k> randDistinct(T mn, T mx) {
    std::array<T, k> values;
    randDistinct(values.begin(), values.end(), mn, mx);
    return values;
}

// Returns K random values (without repetitions) out of a specified collection.
template<typename CollectionT>
CollectionT randDistinct(const CollectionT& values, int k) {
    assert(k >= 0 && k <= int(values.size()));
    CollectionT samples;
    for (int i : randDistinct(0, int(values.size())-1, k)) {
        samples.push_back(values[i]);
    }
    return samples;
}