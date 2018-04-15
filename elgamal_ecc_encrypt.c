#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include"elgamal_function.c"


int main(){
  printf("\n Enter Elliptic Curve Parameters i.e. a,b and p\n");
  gmp_scanf("%Zd",&EC.a);
  gmp_scanf("%Zd",&EC.b);
  gmp_scanf("%Zd",&EC.p);

  struct Point P,Q,R,C1,C2,M;
  mpz_init(P.x); mpz_init(P.y);
  mpz_init(Q.x); mpz_init(Q.y);
//  mpz_init_set_ui(R.x,0); mpz_init_set_ui(R.y,0);
  printf("\n Enter Points P(x,y) and Q(x,y)\n");
  printf("P.x : ");
  gmp_scanf("%Zd",&P.x);
  gmp_scanf("%Zd",&P.y);

  gmp_scanf("%Zd",&Q.x);
  gmp_scanf("%Zd",&Q.y);


  mpz_init(M.x); mpz_init(M.y);
  printf("\n Enter Message Point M(x,y)\n");
  gmp_scanf("%Zd",&M.x);
  gmp_scanf("%Zd",&M.y);

  gmp_randstate_t x;
  gmp_randinit_mt (x);
  mpz_t r;
  mpz_init(r);          //choosing r between 0 and n
  //mpz_t n;
  //mpz_init(n);    // unmcomment when debugging is over
  //mpz_urandomm (r,x,EC.p);
    mpz_set_str(r, "2", 10);   // setting r to 2 comment this when debugging is over
    gmp_printf("\nr:: %Zd\n",r);
    //gmp_printf("\nP.x: %Zd\nP.y: %Zd\n",P.x,P.y);
  mpz_init(C1.x); mpz_init(C1.y);
  mpz_init(C2.x); mpz_init(C2.y);
  C1 = cipher1_fn(P,r);
  C2 = cipher2_fn(Q,M,r);

return 0;
}
