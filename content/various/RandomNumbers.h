/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: An example on the usage of generator and distribution.
 */
 
mt19937_64 mt (time (0));
uniform_int_distribution <int> uid (1, 100);
uniform_real_distribution <double> urd (1, 100);
cout << uid (mt) << " " << urd (mt) << "\n";
