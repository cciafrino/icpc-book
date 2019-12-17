/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: me
 * Description: 
 * Status: tested
 */
template <typename T>
T mabs(T v) {
  return v < 0 ? -v : v;
}
 
template <typename T>
T mceil(T v) {
  T x = ceil((long double)v) - 1.0;
  while (x < v) x += 1.0;
  return x;
}
 
template <typename T>
T mfloor(T v) {
  T x = floor((long double)v) + 1.0;
  while (x > v) x -= 1.0;
  return x;
}