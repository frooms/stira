#ifndef SVD_H
#define SVD_H

// code from Numerical Recipes, verified with example found on
// https://www.ling.ohio-state.edu/~kbaker/pubs/Singular_Value_Decomposition_Tutorial.pdf
class SVD
{
public:
    SVD(double** u, int m, int n);

    //Given the matrix A stored in u[0..m-1][0..n-1], this routine computes its singular value
    //decomposition, A = U  W  Vt and stores the results in the matrices u and v, and the vector w
    void decompose();

    //Given the output of decompose, this routine sorts the singular values, and corresponding columns
    //of u and v, by decreasing magnitude. Also, signs of corresponding columns are flipped so as to
    //maximize the number of positive elements.
    void reorder();

    //Computes .a 2 C b 2 / 1=2 without destructive underflow or overflow.
    double pythag(const double a, const double b);
    void PrintSingularValues();
    void PrintMatrixU();
    void PrintMatrixV();

private:
    int n, m, maxMN;
    double **u, **v, *w;
    double eps;
};

#endif // SVD_H
