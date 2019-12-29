/**
 * Author: Neal Wu
 * Description: Provides two operations on an array A (the same as a Fenwick tree):
 * 1. Add x to A[i]. Runs in O(1).
 * 2. Query the sum of A[left] through A[right - 1].
 * Time: O(\sqrt(n))
 */
template<typename T>
struct sqrt_sums {
    int n, bucket_size, n_buckets;
    vector<T> values, bucket_sums;
    sqrt_sums(int _n = 0) : n(_n), bucket_size(1.2*sqrt(n)+1), 
        n_buckets((n+bucket_size-1)/bucket_size), values(n), 
        bucket_sums(n_buckets) {}
    sqrt_sums(const vector<T> &other) : n(other.size()), 
        bucket_size(1.2*sqrt(n)+1), n_buckets((n+bucket_size-1)/bucket_size), 
        values(other), bucket_sums(n_buckets) {
            for (int b = 0; b < n_buckets; b++) {
                int left = get_bucket_left(b);
                int right = get_bucket_right(b);
                for (int i = left; i < right; i++)
                    bucket_sums[b] += values[i];
            }
    }
    int which_bucket(int index) const { return index < n ? index / bucket_size : n_buckets; }
    int get_bucket_left(int b) const { return bucket_size * b; }
    int get_bucket_right(int b) const { return min(bucket_size * (b + 1), n);}
    void update(int index, T change) {
        assert(0 <= index && index < n);
        values[index] += change;
        bucket_sums[which_bucket(index)] += change;
    }
    T query(int left, int right) const {
        assert(0 <= left && left <= right && right <= n);
        T sum = 0;
        int left_b = which_bucket(left), right_b = which_bucket(right);
        int bucket_left = get_bucket_left(left_b);
        int bucket_right = get_bucket_right(left_b);
        if (left - bucket_left < bucket_right - left) 
            while (left > bucket_left)
                sum -= values[--left];
        else while (left < bucket_right)
                sum += values[left++];
        bucket_left = get_bucket_left(right_b);
        bucket_right = get_bucket_right(right_b);
        if (right - bucket_left < bucket_right - right) 
            while (right > bucket_left)
                sum += values[--right];
        else 
            while (right < bucket_right)
                sum -= values[right++];
        left_b = which_bucket(left);
        right_b = which_bucket(right);
        for (int b = left_b; b < right_b; b++)
            sum += bucket_sums[b];
        return sum;
    }
};