/**
 * Author: Chris
 * Description: Stars and Bars technique. How many ways can one distribute $k$ indistinguishable objects into $n$ bins. ${{n+k-1} \choose k}$
 */
 
int get_nway_distribute(int many, int npile) {
  if (many == 0)
    return npile == 0;
  many -= npile;
  return ncr(many + npile - 1, npile - 1);
}
