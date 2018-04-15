#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include"elgamal_function.c"


struct Point decrypt_elgamal (struct Point C1,struct Point C2,mpz_t alpha)
{

  struct Point M;
  mpz_init(M.x); mpz_init(M.y);
//  mpz_init(B.x); mpz_init(B.y);
  C1 = cipher1_fn(C1,alpha);

  mpz_t i;
  mpz_init(i);
  mpz_set_str(i, "1", 10);

  //mpz_neg (mpz_t rop, const mpz_t op)
  mpz_neg (C1.y, C1.y); //C1.y = -C1.y

  M = cipher2_fn(C2 , C1 , i);

  gmp_printf("\nFinal Decrypted Message \nM.x:: %Zd\tM.y: %Zd\n",M.x,M.y);
  return M;
}

int main(){
  mpz_t alpha;
  mpz_init(alpha);
  struct Point C1,C2,DM;
  mpz_init(C1.x); mpz_init(C1.y);
  mpz_init(C2.x); mpz_init(C2.y);
  mpz_init(DM.x); mpz_init(DM.y);

  printf("\n Enter Elliptic Curve Parameters i.e. a,b and p\n");
  gmp_scanf("%Zd",&EC.a);
  gmp_scanf("%Zd",&EC.b);
  gmp_scanf("%Zd",&EC.p);

  printf("\n Enter Points C1(x,y) and C2(x,y) recieved from sender \n");
  gmp_scanf("%Zd",&C1.x);
  gmp_scanf("%Zd",&C1.y);

  gmp_scanf("%Zd",&C2.x);
  gmp_scanf("%Zd",&C2.y);

  printf("\nEnter private key of reciever\n");
  gmp_scanf("%Zd",&alpha);

  DM = decrypt_elgamal(C1,C2,alpha);

  return 0;
}
