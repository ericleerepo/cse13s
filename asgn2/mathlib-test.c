#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int opt = 0;

    int natural_e = 0;
    int b = 0;
    int m = 0;
    int r = 0;
    int v = 0;
    int w = 0;
    int n = 0;
    int s = 0;
    int h = 0;

    double math_pi = M_PI;
    double math_e = M_E;

    while ((opt = getopt(argc, argv, "aebmrvwnsh")) != -1) {
        switch (opt) {
        case 'a':
            natural_e = 1;
            b = 1;
            m = 1;
            r = 1;
            v = 1;
            w = 1;
            n = 1;
        case 'e': natural_e = 1; break;
        case 'b': b = 1; break;
        case 'm': m = 1; break;
        case 'r': r = 1; break;
        case 'v': v = 1; break;
        case 'w': w = 1; break;
        case 'n': n = 1; break;
        case 's': s = 1; break;
        case 'h': h = 1; break;
        default: h = 1; break;
        }
    }
    if (s == 1 && natural_e == 0 && b == 0 && m == 0 && r == 0 && v == 0 && w == 0 && n == 0
        && h == 0) {
        h = 1;
    }
    if (h == 1 || argc == 1) {
        printf("Help Page:\n'-a' command prints all functions.\n'-e' command prints e "
               "approximation.\n'-b' command prints Bailey-Borwein-Plouffe pi approximation.\n'-m' "
               "command prints Madhava pi approximation.\n'-r' command prints Euler sequence pi "
               "approximation.\n'-v' command prints Viete pi apprxomation.\n'-w' command prints "
               "Wallis pi approxmation.\n'-n' comamnd prints square root of numbers between 0 and "
               "10 in 0.1 increments.\n'-s' command prints number of commuted terms and factors "
               "for all functions.\n");
        exit(0);
    }
    if (natural_e == 1) {
        double taylor = e();
        double diff = math_e - taylor;
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", taylor, math_e, diff);
        if (s == 1) {
            int termse = e_terms();
            printf("e() terms = %d\n", termse);
        }
    }
    if (b == 1) {
        double pi = pi_bbp();
        double diff = math_pi - pi;
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi, math_pi, diff);
        if (s == 1) {
            int termsbbp = pi_bbp_terms();
            printf("pi_bbp() terms = %d\n", termsbbp);
        }
    }
    if (m == 1) {
        double pi = pi_madhava();
        double diff = math_pi - pi;
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi, math_pi, diff);
        if (s == 1) {
            int termsm = pi_madhava_terms();
            printf("pi_madhava() terms = %d\n", termsm);
        }
    }
    if (r == 1) {
        double pi = pi_euler();
        double diff = math_pi - pi;
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi, math_pi, diff);
        if (s == 1) {
            int termsr = pi_euler_terms();
            printf("pi_euler() terms = %d\n", termsr);
        }
    }
    if (v == 1) {
        double pi = pi_viete();
        double diff = math_pi - pi;
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi, math_pi, diff);
        if (s == 1) {
            int termsv = pi_viete_factors();
            printf("pi_viete() terms = %d\n", termsv);
        }
    }
    if (w == 1) {
        double pi = pi_wallis();
        double diff = math_pi - pi;
        printf("pi_wallis() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi, math_pi, diff);
        if (s == 1) {
            int termsw = pi_wallis_factors();
            printf("pi_wallis() terms = %d\n", termsw);
        }
    }
    if (n == 1) {
        for (double i = 0.0; i < 9.95; i += 0.1) {
            double root = sqrt_newton(i);
            double math_root = sqrt(i);
            double diff = math_root - root;
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", i,
                root, i, math_root, diff);
            if (s == 1) {
                int termssqrt = sqrt_newton_iters();
                printf("sqrt_newton() terms = %d\n", termssqrt);
            }
        }
    }
    return 0;
}
