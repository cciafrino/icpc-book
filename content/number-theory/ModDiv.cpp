/**
 * Author: Chris
 * Description: Modular division operation
 */
lint modDiv(lint a, lint b, lint m){
    return ((a%m) * modinv(b, m)) % m;
}
