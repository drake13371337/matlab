#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

void print_mtrx(double **matr, int n, int step){
    for(int i=0; i<n; i++){
        for(int j=0; j<n+step; j++){
            cout<<matr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int col_max(double **matrix, int col, int n){
    double max = abs(matrix[col][col]);
    int maxPos = col;
    for(int i=col+1; i<n; ++i){
        double element = abs(matrix[i][col]);
        if(element>max){
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

int triangle(double **matrix, int n, int step){
    double buff;
    if (n == 0)
        return 0;
    for(int i=0; i<n-1; ++i){
        int imax = col_max(matrix, i, n);
        if (i != imax) {
            for(int j=0; j<n+step; j++){
                buff=matrix[i][j];
                matrix[i][j]=matrix[imax][j];
                matrix[imax][j]=buff;
            }
        }
        for (int j=i+1; j<n; ++j){
            double mul;
            if(matrix[i][i]==0) mul=0;
            if(matrix[i][i]!=0) mul = -matrix[j][i]/matrix[i][i];
            for (int k=i; k<n+step; ++k){
                matrix[j][k]+=matrix[i][k]*mul;
                if(abs(matrix[j][k])<0.0001) matrix[j][k]=0;
            }
        }
    }
}
int rank_matr(double **matr, int n, int step){
    int rank1 = n;
    int chk = 0;
    for(int i=1;i<n+1;i++){
        chk=0;
        for(int j=0;j<n+step;j++){
            if(matr[n-i][j]!=0)
                chk++;
        }
        if(chk==0) rank1--;
    }
    return rank1;
}
int gauss(double **matr, int rank, int n){
    double *x;
    x = new double[n];
    for(int i=0;i<n;i++) x[i]=0;
    int ranks = rank_matr(matr, n, 1);
    if(ranks==rank && ranks<n){
        cout<<"Endless solutions"<<endl;
        return 0;
    }
    if(rank==ranks){
        for(int i=1; i<=n; i++){
            x[n-i]=matr[n-i][n];
            for(int j=0;j<n;j++){
                if((n-i)!=j)
                    x[n-i]=x[n-i]-(matr[n-i][j]*x[j]);
            }

            x[n-i]=x[n-i]/matr[n-i][n-i];
            if(matr[n-i][n-i]==0) cout<<"x"<<n-i<<" = Endless solutions"<<endl;
            else cout<<"x"<<n-i<<" = "<<x[n-i]<<endl;
        }
        return 0;
    }
    cout<<"No solutions"<<endl;
    delete [] x;
    return 0;
}

int main()
{
    double **su, **tmp;
    int n = 0;
    string buff;

    ifstream file("matrix.txt", ios_base::out);
    while(!file.eof()){
        getline(file, buff);
        if(buff.size()>0)
            n++;
    }
    file.close();
    ifstream fmatrix("matrix.txt", ios_base::out);

    su = new double*[n];
    for(int i=0; i<n; i++){
        su[i] = new double[n+1];
        for(int j=0; j<n+1; j++){
           fmatrix>>su[i][j];
        }
    }
    tmp = new double*[n];
    for(int i=0; i<n; i++){
        tmp[i] = new double[n];
        for(int j=0; j<n; j++){
           tmp[i][j]=su[i][j];
        }
    }
    print_mtrx(su, n, 1);
    triangle(su, n, 1);
    triangle(tmp, n, 0);

    gauss(su, rank_matr(tmp, n, 0), n);

    for(int i=0; i<n; i++)
        delete [] su[i];
    fmatrix.close();
    return 0;
}
