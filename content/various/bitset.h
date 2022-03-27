/**
 * Author: ?
 * License: CC0
 * Description: Some bitset functions
 * Status:
 * Time: 
 */

int main() {
    bitset<100> bt;
    cin >> bt;
    cout << bt[0] << "\n";
    cout << bt.count() << "\n"; // number of bits set
    cout << (~bt).none() << "\n"; // return true if has no bits set
    cout << (~bt).any() << "\n"; // return true if has any bit set
    cout << (~bt).all() << "\n"; // retun true if has all bits set
    cout << bt._Find_first() << "\n"; // return first set bit
    cout << bt._Find_next(10) << "\n";// returns first set bit after index i
    cout << bt.flip() << '\n'; // flip the bitset
    cout << bt.test(3) << '\n'; // test if the ith bit of bt is set
    cout << bt.reset(3) << '\n'; // reset the ith bit
    cout << bt.set() << '\n'; // turn all bits on
    cout << bt.set(4, 1) << '\n'; // set the 4th bit to value 1
    cout << bt << "\n";
}
