// Poisson_Multigrid.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cptstd.hpp"
#include "matrix.hpp"

#include <Windows.h>
using namespace cpt;

double accuracy = 0.001;        // desired relative accuracy in solution
int L = 64;                     // number of interior points in each dimension
int n_smooth = 5;               // number of pre and post smoothing iterations

Matrix<double,2> psi(L+2, L+2), // solution to be found
    psi_new(L+2, L+2),          // approximate solution after 1 iteration
    rho(L+2, L+2);              // given source function

double h = 1.0 / (L+1);         // step size
int steps;                      // number of iteration steps

void initialize()
{
    // check that L is a power of 2 as required by multigrid
    int power_of_2 = 1;
    while (power_of_2 < L)
        power_of_2 *= 2;
    if (power_of_2 != L) {
        L = power_of_2;
        cout << " Setting L = " << L << " (must be a power of 2)" << endl;
        OutputDebugStringA("L is not a power of 2!");
    }

    // create (L+2)x(L+2) matrices and zero them
   // psi = psi_new = rho = Matrix<double,2>(L+2, L+2);

    //h = 1 / double(L + 1);      // assume physical size in x and y = 1
    h = 1;
    double q = 10;              // point charge
    int i = L / 2;              // center of lattice
    
 //   rho[i][i] = 0;

    steps = 0;
}

void Gauss_Seidel(double h, Matrix<double,2>& u, const Matrix<double,2>& f)
{
    int L = u.dim1() - 2;

    // use checkerboard updating
    for (int color = 0; color < 2; color++)
        for (int i = 1; i <= L; i++)
            for (int j = 1; j <= L; j++)
                if ((i + j) % 2 == color)
                    u[i][j] = 0.25 * (u[i - 1][j] + u[i + 1][j] +
                                      u[i][j - 1] + u[i][j + 1] +
                                      h * h * f[i][j]);
}

void two_grid(double h, Matrix<double,2>& u, Matrix<double,2>& f)
{
    // solve exactly if there is only one interior point
    int L = u.dim1() - 2;
    if (L == 1) {
        u[1][1] = 0.25 * (u[0][1] + u[2][1] + u[1][0] + u[1][2] +
                          h * h * f[1][1]);
        return;
    }

    // do a few pre-smoothing Gauss-Seidel steps
    for (int i = 0; i < n_smooth; i++)
        Gauss_Seidel(h, u, f);

    // find the residual
    Matrix<double,2> r(L+2, L+2);
    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
            r[i][j] = f[i][j] +
                      ( u[i + 1][j] + u[i - 1][j] +
                        u[i][j + 1] + u[i][j - 1] - 4 * u[i][j]) / (h * h);

    // restrict residual to coarser grid
    int L2 = L / 2;
    Matrix<double,2> R(L2 + 2, L2 + 2);
    for (int I = 1; I <= L2; I++) {
        int i = 2 * I - 1;
        for (int J = 1; J <= L2; J++) {
            int j = 2 * J - 1;
            R[I][J] = 0.25 * ( r[i][j] + r[i + 1][j] + r[i][j + 1] +
                               r[i + 1][j + 1]);
        }
    }

    // initialize correction V on coarse grid to zero
    Matrix<double,2> V(L2 + 2, L2 + 2);

    // call twoGrid recursively
    double H = 2 * h;
    two_grid(H, V, R);

    // prolongate V to fine grid using simple injection
    Matrix<double,2> v(L + 2, L + 2);
    for (int I = 1; I <= L2; I++) {
        int i = 2 * I - 1;
        for (int J = 1; J <= L2; J++) {
            int j = 2 * J - 1;
            v[i][j] = v[i + 1][j] = v[i][j + 1] = v[i + 1][j + 1] = V[I][J];
        }
    }

    // correct u
    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++)
            u[i][j] += v[i][j];

    // do a few post-smoothing Gauss-Seidel steps
    for (int i = 0; i < n_smooth; i++)
        Gauss_Seidel(h, u, f);
}

double relative_error()
{
    double error = 0;           // average relative error per lattice point
    int n = 0;                  // number of non-zero differences

    for (int i = 1; i <= L; i++)
        for (int j = 1; j <= L; j++) {
            if (psi_new[i][j] != 0.0)
                if (psi_new[i][j] != psi[i][j]) {
                    error += abs(1 - psi[i][j] / psi_new[i][j]);
                    ++n;
                }
        }
    if (n != 0)
        error /= n;

    return error;
}

int main()
{
    cout << " Multigrid solution of Poisson's equation\n"
         << " ----------------------------------------\n";
    cout << " Enter number of interior points in x or y: ";
    cin >> L;
    cout << " Enter desired accuracy in the solution: ";
    cin >> accuracy;
    cout << " Enter number of smoothing iterations: ";
    cin >> n_smooth;

    initialize();
    clock_t t0 = clock();
    while (true) {
        for (int i = 0; i < L+2; i++)
            for (int j = 0; j < L+2; j++)
                psi_new[i][j] = psi[i][j];
        two_grid(h, psi, rho);
        ++steps;
        double error = relative_error();
        cout << " Step No. " << steps << "\tError = " << error << endl;
        if (steps > 1 && error < accuracy)
            break;
    }
    clock_t t1 = clock();
    cout << " CPU time = " << double(t1 - t0) / CLOCKS_PER_SEC
         << " sec" << endl;

    // write potential to file
    ofstream file("poisson_mg.data");
    for (int i = 0; i < L + 2; i++) {
        double x = i * h;
        for (int j = 0; j < L + 2; j++) {
            double y = j * h;
            file << x << '\t' << y << '\t' << psi[i][j] << '\n';
        }
        file << '\n';
    }
    file.close();
    cout << " Potential in file poisson_mg.data" << endl;
}


void solveMultigrid(cpt::Matrix<double, 2> & laplacian, cpt::Matrix<double, 2> & dstIm)
{
    // we will zero the interior of the dst image, 
    for (int i=1; i < (dstIm.dim2() - 1); i++)
    {
        for (int j =1; j < (dstIm.dim1() - 1); j++)
        {
            dstIm(j,i) = 0;
        }
    }

    // and zero the boundary points of the laplacian
    for (int i=0; i < dstIm.dim1(); i++)
    {
        laplacian(i,0) = 0;
        laplacian(0,i) = 0;
        laplacian(i, dstIm.dim1() - 1) = 0;
        laplacian(dstIm.dim1() - 1, i) = 0;
    }

    // psi and psi_new are intialized with the boundary conditions
    psi = dstIm;
    psi_new = dstIm;
    // rho is initialized with the interior points of the laplacian of the source image
    rho = laplacian;

    L = dstIm.dim1() - 2;
    accuracy = 1 * pow(10.0,-14.0);
    //accuracy = .1;
    n_smooth = 2;


    rho = laplacian;

    
    initialize();
    clock_t t0 = clock();
    // iterative process for finding the solution
    OutputDebugStringA("Starting optimization...\n");
    while (true) {
        for (int i = 0; i < L+2; i++)
            for (int j = 0; j < L+2; j++)
                psi_new[i][j] = psi[i][j];
        two_grid(h, psi, rho);
        ++steps;
        // error -- based on difference between last and current psi.
        double error = relative_error();
        std::ostringstream lineOut;

        lineOut << " Step No. " << steps << "\tError = " << error << endl;
        OutputDebugStringA(lineOut.str().c_str());
        if (steps > 1 && error < accuracy)
            break;
    }
    clock_t t1 = clock();
    cout << " CPU time = " << double(t1 - t0) / CLOCKS_PER_SEC
         << " sec" << endl;

    dstIm = psi;

}
