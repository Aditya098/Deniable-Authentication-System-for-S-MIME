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

struct Point cipher2_fn(struct Point Q , struct Point M , mpz_t r);

struct Point cipher1_fn(struct Point P , mpz_t r);
