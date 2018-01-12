#pragma once

#include "cptstd.hpp"
#include "matrix.hpp"

// Solve a linear system of equations of the form Ax = b
void solveMultigrid(cpt::Matrix<double, 2> & laplacian, cpt::Matrix<double, 2> & dstIm);
