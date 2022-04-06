
#ifdef _WIN32
#include <Windows.h>
#endif

#include <math.h>
#include <pari.h>

#define PRECISION 5

static GEN half = NULL;

/* y - imaginary part of the critical line input coordinate for zeta */
void computeZeta(double y, double* zetaRe, double* zetaIm) {
    pari_sp av = avma;

    GEN cresult = gzeta(mkcomplex(half, dbltor(y)), PRECISION);

    *zetaRe = gtodouble(greal(cresult));
    *zetaIm = gtodouble(gimag(cresult));

    avma = av;
}


int main(int argc, char* argv[]) {
    pari_init(1000000, 2);

    half = ginv(gen_2);

    double zetaRe, zetaIm, inputIm = 0.0;
    // test first zero
    computeZeta(14.134725, &zetaRe, &zetaIm);
    if (fabs(zetaRe) > 1e-5) return 1;
    if (fabs(zetaIm) > 1e-5) return 1;

    pari_close();

    return 0;
}
