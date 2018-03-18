#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
//#include <gmpxx.h>


struct Elliptic_Curve
{
mpz_t a;
mpz_t b;
mpz_t p;
};
struct Point
{
mpz_t x;
mpz_t y;
};
struct Elliptic_Curve EC;

struct Point cipher1_fn(struct Point P , mpz_t r){
  struct Point A,B,C;
  mpz_init(A.x); mpz_init(A.y);
  mpz_init(B.x); mpz_init(B.y);
    mpz_init(C.x); mpz_init(C.y);
//  mpz_t i;
  //mpz_init(i);
  mpz_set (B.x,P.x);
  mpz_set (B.y,P.y);
  mpz_set (A.x,P.x);
  mpz_set (A.y,P.y);
  mpz_set (C.x,P.x);
  mpz_set (C.y,P.y);

  mpz_t i;
  mpz_init(i);
  mpz_set_str(i, "1", 10);

  for (; mpz_cmp(i,r)< 0; mpz_add_ui(i, i, 1)) {
/*mpz_class a;

for(a=0;a<3;a++)
cout<<"Hello world!"<<endl;
*/ // for(i='0';i<r;i++){
    mpz_t lamda;
    mpz_init(lamda);
    mpz_t temp1;
    mpz_init(temp1);
    mpz_t temp2;
    mpz_init(temp2);
    mpz_t temp4;
    mpz_init(temp4);
    mpz_add (temp4,B.y, P.y);
    mpz_t temp5;
    mpz_init(temp5);
    mpz_set_str(temp5, "0", 10);


    gmp_printf("\nBefore if else\nB.x: %Zd\tB.y: %Zd\n",B.x,B.y);
    gmp_printf("\nP.x: %Zd\tP.y: %Zd\n",P.x,P.y);

  //  if(P.x == B.x && P.y == B.y){
  if(mpz_cmp (P.x,B.x) == 0 && mpz_cmp (P.y,B.y) == 0){
        mpz_pow_ui (A.x, A.x, 2);
        mpz_mul_ui (A.x, A.x, 3);      //x1= 3(x1^2)      // p must be defined globally Zp*
        mpz_add (A.x, A.x, EC.a);         //x1 = 3(x1^2) + a
        mpz_mul_ui (A.y, A.y, 2);      // y1 = 2y1

        //mpz_invert (mpz_t rop, const mpz_t op1, const mpz_t op2)
        mpz_invert (A.y, A.y, EC.p);
        mpz_mul (A.x, A.x, A.y);
        //mpz_mod (mpz_t r, const mpz_t n, const mpz_t d)
        mpz_mod (lamda, A.x, EC.p);   // x1 = (3(x1^2) +a )/2(y1) mod p

        mpz_pow_ui (B.x, lamda, 2);
      //  mpz_mul_ui (temp2, B.x, 2);

        //mpz_submul (mpz_t rop, const mpz_t op1, const mpz_t op2)
        mpz_t temp3;
        mpz_init(temp3);
        mpz_set_str(temp3, "2", 10);
        mpz_submul (B.x, temp3, P.x);
        mpz_mod (B.x, B.x, EC.p);

        //mpz_sub (mpz_t rop, const mpz_t op1, const mpz_t op2)
        mpz_sub (B.y, P.x, B.x);  // x1-x3
        //mpz_mul (mpz_t rop, const mpz_t op1, const mpz_t op2)
        mpz_mul (B.y, lamda,B.y);
        mpz_sub (B.y, B.y , P.y);
        mpz_mod (B.y, B.y, EC.p);

          gmp_printf("\n In if stmt \nC1x:: %Zd\tC1y: %Zd\n",B.x,B.y);
    }

    else if (mpz_cmp (P.x,B.x) == 0 && mpz_cmp (temp4,temp5) == 0){
      mpz_set (B.x,0);
      mpz_set (B.y,0);
      gmp_printf("\n In else if stmt \nC1x:: %Zd\tC1y: %Zd\n",B.x,B.y);
    }

    else  {
    //  mpz_set (A.x,P.x);
      // mpz_set (A.y,P.y);
      //gmp_printf("\nr:: %Zd\n",r);
      //printf("\nk : %d\n",k);
    //  gmp_printf("\nB.x: %Zd\nB.y: %Zd\n",B.x,B.y);
      //gmp_printf("\nP.x: %Zd\nP.y: %Zd\n",P.x,P.y);
      mpz_sub (A.y, P.y , B.y);
      mpz_sub (A.x, P.x , B.x);
      mpz_invert (A.x, A.x, EC.p);
      mpz_mul (A.x, A.y, A.x);
      mpz_mod (lamda, A.x, EC.p);

    //  mpz_pow_ui (mpz_t rop, const mpz_t base, unsigned long int exp)
      mpz_pow_ui (temp1, lamda, 2);
      mpz_sub (B.x, temp1 , B.x);
      mpz_sub (B.x, B.x , P.x);
      mpz_mod (B.x, B.x, EC.p);

      mpz_sub (B.y, P.x, B.x);
      mpz_mul (B.y, lamda,B.y);
      mpz_sub (B.y, B.y , P.y);
      mpz_mod (B.y, B.y, EC.p);
      gmp_printf("\nIn else  stmt \nC1x:: %Zd\tC1y: %Zd\n",B.x,B.y);
    }
  }
//  gmp_printf("\nC1x:: %Zd\n C1y: %Zd\n",B.x,B.y);
  return B;
}

/////////////////////////////////////////////////////////////////////

struct Point cipher2_fn(struct Point Q , struct Point M , mpz_t r){
  struct Point Ra ,A ,B;
  mpz_init(A.x); mpz_init(A.y);
  mpz_init(B.x); mpz_init(B.y);



  mpz_init(Ra.x); mpz_init(Ra.y);
  Ra = cipher1_fn(Q,r);

  mpz_set (B.x,Ra.x);
  mpz_set (B.y,Ra.y);
  mpz_set (A.x,Ra.x);
  mpz_set (A.y,Ra.y);
  mpz_t temp1;
  mpz_init(temp1);
  mpz_t lamda;
  mpz_init(lamda);
  mpz_t temp2;
  mpz_init(temp2);
  mpz_sub (temp2,Ra.y, M.y);
  mpz_t temp3;
  mpz_init(temp3);
  mpz_set_str(temp3, "0", 10);

  //if(Ra.x == M.x && Ra.y == M.y){
  if(mpz_cmp (Ra.x,M.x) == 0 && mpz_cmp (Ra.y,M.y) == 0){
      //mpz_set (A.x,B.x);
      //mpz_set (A.y,B.y);
      mpz_pow_ui (A.x, A.x, 2);
      mpz_mul_ui (A.x, A.x, 3);      //x1= 3(x1^2)      // p must be defined globally Zp*
      mpz_add (A.x, A.x, EC.a);         //x1 = 3(x1^2) + a
      mpz_mul_ui (A.y, A.y, 2);      // y1 = 2y1

      //mpz_invert (mpz_t rop, const mpz_t op1, const mpz_t op2)
      mpz_invert (A.y, A.y, EC.p);
      mpz_mul (A.x, A.x, A.y);
      //mpz_mod (mpz_t r, const mpz_t n, const mpz_t d)
      mpz_mod (lamda, A.x, EC.p);   // x1 = (3(x1^2) +a )/2(y1) mod p

      mpz_pow_ui (B.x, lamda, 2);
    //  mpz_mul_ui (temp2, B.x, 2);

      //mpz_submul (mpz_t rop, const mpz_t op1, const mpz_t op2)
      mpz_t temp3;
      mpz_init(temp3);
      mpz_set_str(temp3, "2", 10);
      mpz_submul (B.x, temp3, M.x);
      mpz_mod (B.x, B.x, EC.p);
      //mpz_sub (mpz_t rop, const mpz_t op1, const mpz_t op2)
      mpz_sub (B.y, Ra.x, B.x);
      //mpz_mul (mpz_t rop, const mpz_t op1, const mpz_t op2)
      mpz_mul (B.y, lamda,B.y);
      mpz_sub (B.y, B.y , Ra.y);
      mpz_mod (B.y, B.y, EC.p);
  }
  else if (mpz_cmp (Ra.x,M.x) != 0 || (mpz_cmp (temp2,temp3)!=0)) {//(B.y != M.y && (B.y + M.y != 0))) {
    //mpz_set (A.x,M.x);
    //mpz_set (A.y,M.y);

    mpz_sub (A.y, M.y , Ra.y);
    mpz_sub (A.x, M.x , Ra.x);
    mpz_invert (A.x, A.x, EC.p);
    mpz_mul (A.x, A.y, A.x);
    mpz_mod (lamda, A.x, EC.p);

    mpz_pow_ui (temp1, lamda, 2);
    mpz_sub (B.x, temp1 , Ra.x);
    mpz_sub (B.x, B.x , M.x);
    mpz_mod (B.x, B.x, EC.p);

    mpz_sub (B.y, Ra.x , B.x);
    mpz_mul (B.y, lamda ,B.y);
    mpz_sub (B.y, B.y , Ra.y);
    mpz_mod (B.y, B.y, EC.p);

  }
  else if (mpz_cmp (Ra.x,M.x) == 0 && (mpz_cmp (temp2,temp3)==0)) {
    mpz_set (B.x,0);
    mpz_set (B.y,0);
  }
  else;


  gmp_printf("\nC2x:: %Zd\tC2y: %Zd\n",B.x,B.y);
  return B;
}

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
  //mpz_init(n);
  //mpz_urandomm (r,x,EC.p);
    mpz_set_str(r, "2", 10);
    gmp_printf("\nr:: %Zd\n",r);
    //gmp_printf("\nP.x: %Zd\nP.y: %Zd\n",P.x,P.y);
  mpz_init(C1.x); mpz_init(C1.y);
  mpz_init(C2.x); mpz_init(C2.y);
  C1 = cipher1_fn(P,r);
  C2 = cipher2_fn(Q,M,r);

return 0;
}
