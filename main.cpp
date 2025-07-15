#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
// Estimateur Nadaraya-Watson
template<typename Kernel>
double mhat_NW0_fast(
    double x,
    const vector<double>& X,
    const vector<double>& Y,
    Kernel K,
    double bnop
) {
    const size_t n = X.size();
    double Num = 0.0;
    double Den = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double u = (x - X[i]) / bnop;
        double k_val = K(u);
        Num += k_val * Y[i];
        Den += k_val;
    }

    return (Den == 0.0) ? 0.0 : (Num / Den);
}


// Noyau gaussien

double gaussian_kernel(double u) {
    return exp(-0.5 * u * u) / sqrt(2 * M_PI);
}

// la fonction main pour tester avec des donnees 

int main() {
    vector<double> X = {1, 2, 3, 4, 5};
    vector<double> Y = {2, 4, 6, 8, 10};
    double bnop = 1.0;
    double x = 2.5;

    double estimation = mhat_NW0_fast(x, X, Y, gaussian_kernel, bnop);

    cout << "Estimation en x = " << x << " : " << estimation << endl;

    return 0;
}
