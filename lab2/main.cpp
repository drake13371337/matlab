#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void reverse_matr(double **Ai, int n, double **res){
    double **A = new double*[n];
    double **B = new double*[n];
    double temp;

    for(int i=0; i<n; i++){
        A[i] = new double[n];
        for(int j=0; j<n; j++) A[i][j]=Ai[i][j];
    }
    for(int i=0; i<n; i++){
        B[i] = new double[n];
        for(int j=0; j<n; j++){
            B[i][j]=0;
            if(i==j) B[i][j]=1;
        }
    }
    for(int k=0; k<n; k++){
        temp = A[k][k];
        for(int j=0; j<n; j++){
            A[k][j]/=temp;
            B[k][j]/=temp;
        }
        for(int i=k+1; i<n; i++){
            temp = A[i][k];
            for(int j=0; j<n; j++){
                A[i][j]-=A[k][j]*temp;
                B[i][j]-=B[k][j]*temp;
            }
        }
    }
    for(int k=n-1; k>0; k--){
        for(int i=k-1; i>=0; i--){
            temp = A[i][k];
            for (int j=0; j<n; j++){
                A[i][j]-=A[k][j]*temp;
                B[i][j]-=B[k][j]*temp;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            res[i][j]=B[i][j];
        }
    }
    for(int i=0; i<n; i++){
        delete[] A[i];
        delete[] B[i];
    }
}

void mult(double **A, double *B, int n, double *res){
    for(int i=0; i<n; i++)
        for(int k=0; k<n; k++)
            res[i]=res[i]+A[i][k]*B[k];
}

double norm(double *A, int n){
    double max = 0;
    for(int i=0; i<n; i++){
        if(abs(A[i])>max) max=abs(A[i]);
    }
    return max;
}

double scal(double* A, double *B, int n){
    double res=0;
    for(int i=0; i<n; i++)
        res=res+A[i]*B[i];
    return res;
}

void divm(double *A, int n, double d, double *res){
    for(int i=0; i<n; i++)
        res[i]=A[i]/d;
}


class sys{
    double **A;
    double **A_;
    double *x0;
    double *r;
    double l = 0;
    int n = 0;

public:
    sys(string filename){

        string buff;
        ifstream file(filename, ios_base::out);
        while(!file.eof()){
            getline(file, buff);
            if(buff.size()>0)
                n++;
        }
        n--;
        file.close();

        ifstream fmatrix(filename, ios_base::out);

        A = new double*[n];
        A_ = new double*[n];
        x0 = new double[n];
        r = new double[n];

        for(int i=0; i<n; i++){
            A[i] = new double[n];
            A_[i] = new double[n];
            for(int j=0; j<n; j++) fmatrix>>A[i][j];
        }
        reverse_matr(A, n, A_);
        for(int i=0; i<n; i++) fmatrix>>x0[i];
        fmatrix.close();
    }

    ~sys(){
        for(int i=0; i<n; i++)
            delete[] A[i];
        delete[] x0;
        delete[] r;
    }

    void show(){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout<<A[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        for(int i=0; i<n; i++){
            cout<<x0[i]<<" ";
        }
        cout<<endl<<endl;;
    }

    void power(double e){
        l=0;
        double l0 = -1;
        int iter_count = 0;
        double* r1 = new double[n];
        double* ark = new double[n];
        double* x = new double[n];
        for(int i=0; i<n; i++)
            x[i]=x0[i];

        while(abs(l0-l)>=e){
            l0=l;
            for(int i=0; i<n; i++)
                r1[i]=0;
            mult(A, x, n, r1);
            l=scal(x, r1, n)/scal(x, x, n);
            for(int i=0; i<n; i++)
                x[i]=r1[i];
            iter_count++;
        }

        cout<<"Power Method(eps="<<e<<"): Lambda = "<<l<<"; Iter count = "<<iter_count<<endl;
        delete[] r1;
        delete[] x;
        delete[] ark;
    }

    void reverse_power(double e){
        l=0;
        double l0 = -1;
        int iter_count = 0;
        double *r1 = new double[n];
        double *ark = new double[n];
        double *x = new double[n];
        for(int i=0; i<n; i++)
            x[i]=x0[i];
        while(abs(l0-l)>=e){
            l0=l;
            for(int i=0; i<n; i++)
                r1[i]=0;
            mult(A_, x, n, r1);
            l=scal(x, x, n)/scal(r1, x, n);
            for(int i=0; i<n; i++)
                x[i]=r1[i];
            iter_count++;
        }
        cout<<"Reverse Power Method(eps="<<e<<"): Lambda = "<<l<<"; Iter count = "<<iter_count<<endl;
        delete[] r1;
        delete[] ark;
        delete[] x;
    }

    void border(int mode, double ab, double bb){
        double a, b, c, d;
        a=A[0][0];
        b=A[0][1];
        c=A[n-1][n-2];
        d=A[n-1][n-1];
        switch(mode){
            case 0:{
                A[0][0]=a;
                A[0][1]=b;
                A[n-1][n-2]=c;
                A[n-1][n-1]=d;
                break;
            }
            case 1:{
                A[0][0]=1;
                A[0][1]=0;
                A[n-1][n-2]=0;
                A[n-1][n-1]=1;
                break;
            }
            case 2:{
                A[0][0]=-1;
                A[n-1][n-2]=1;
                A[n-1][n-1]=-1;
                break;
            }
            case 3:{
                double h=(bb-ab)/n;
                A[0][0]=h-ab;
                A[0][1]=ab;
                A[n-1][n-2]=ab*(-1);
                A[n-1][n-1]=h+ab;
                break;
            }
        }
    }
};

int main(){
    sys st("matrix.txt");
    st.border(3, 0, 5);
    st.show();
    st.power(0.01);
    st.reverse_power(0.01);

    return 0;
}
