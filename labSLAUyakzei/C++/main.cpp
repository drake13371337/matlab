#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void gz(double **a, double *f, double *x, int n, double e){
    double *buff = new double[n];
    int counter=0;
    double nr;
    double sum;
    for(int i=0; i<n; i++) x[i]=0;
    do{
        for(int i=0; i<n; i++) buff[i]=x[i];
        for(int i=0; i<n; i++){
            sum = 0;
            for(int j=0; j<i; j++)
                sum+=(a[i][j]*x[j]);
            for(int j=i+1; j<n; j++)
                sum+=(a[i][j]*buff[j]);
            x[i]=(f[i]-sum)/a[i][i];
        }
        nr=fabs(buff[0]-x[0]);
        for(int k=0; k<n; k++){
            if (fabs(buff[k]-x[k])>nr){
                nr=fabs(buff[k]-x[k]);
                buff[k]=x[k];
            }
        }
        counter++;
    } while(nr>e);
    for(int i=0;i<n;i++) cout<<"x"<<i<<" = "<<x[i]<<endl;
    cout<<"(n="<<counter<<")"<<endl;
    delete[] buff;
}

void jacobi(double **a, double *f, double *x, int n, double e){
    double *buff = new double[n];
    double nr;
    int counter=0;
    for(int i=0; i<n; i++) x[i]=0;
    do{
        for(int i=0; i<n; i++){
            buff[i]=f[i];
            for(int j=0; j<n; j++){
                if(i!=j) buff[i]-=a[i][j]*x[j];
            }
            buff[i]/=a[i][i];
        }
        nr=fabs(x[0]-buff[0]);
        for(int i=0; i<n; i++){
            if(fabs(x[i]-buff[i])>nr) nr=fabs(x[i]-buff[i]);
            x[i]=buff[i];
        }
        counter++;
    } while(nr>e);
    for(int i=0;i<n;i++) cout<<"x"<<i<<" = "<<x[i]<<endl;
    cout<<"(n="<<counter<<")"<<endl;
    delete[] buff;
}

int main()
{
    double **A;
    double *F;
    double *X;

    string buff;
    int n=0;
    double e=0.0001;

    ifstream file("matrix.txt", ios_base::out);
    while(!file.eof()){
        getline(file, buff);
        if(buff.size()>0)
            n++;
    }
    file.close();
    ifstream fmatrix("matrix.txt", ios_base::out);

    A = new double*[n];
    F = new double[n];
    X = new double[n];

    for(int i=0; i<n; i++){
        A[i] = new double[n+1];
        for(int j=0; j<n; j++){
           fmatrix>>A[i][j];
        }
        fmatrix>>F[i];
    }
    fmatrix.close();

    cout<<"Jacobi(eps="<<e<<"):"<<endl;
    jacobi(A, F, X, n, e);

    cout<<endl;

    cout<<"Gauss-Zeidel(eps="<<e<<"):"<<endl;
    gz(A, F, X, n, e);

    for(int i=0; i<n; i++)
        delete[] A[i];
    delete[] F;
    delete[] X;
    delete[] X1;

    return 0;
}
