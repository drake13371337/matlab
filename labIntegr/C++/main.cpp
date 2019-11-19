#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double rectangle(double a, double b, double e);
double trapeze(double a, double b, double e);
double simpson(double a, double b, double e);
double func(double x);

int main(){
    double a, b;
    a=0.6;
    b=1.724;
    double e = 0.0001;

    trapeze(a, b, e);
    rectangle(a, b, e);
    simpson(a, b, e);

    return 0;
}

double func(double x){
    double y = sqrt(x+pow(x, 3));
    return y;
}

double trapeze(double a, double b, double e){
    double res, h, buff, h1;
    int n=1;
    res=0;
    buff=0;
    while(true){
        h=(b-a)/n;
        h1=h/2;
        for(int i=1; i<n-1; i++)
            res=res+func(a+h*i);
        for(int i=1; i<n*2-1; i++)
            buff=buff+func(a+h1*i);
        res=(res*2+func(a)+func(b))*h/2;
        buff=(buff*2+func(a)+func(b))*h1/2;
        if(abs(buff-res)<=(e*3)){
            cout<<"Trapeze: res = "<<setprecision(8)<<res<<", n = "<<n<<endl;
            return 0;
        }
        res=0;
        buff=0;
        n++;
    }
    return 0;
}

double rectangle(double a, double b, double e){
    double res, h, buff, h1;
    int n=1;
    int trg = 1;
    while(trg){
        h=(b-a)/n;
        h1=h/2;

        for(int i=0; i<n-1; i++)
            res=res+func(a+h*i);
        for(int i=0; i<n*2-1; i++)
            buff=buff+func(a+h1*i);

        res=res*h;
        buff=buff*h1;

        if(abs(buff-res)<=(e*3)){
            cout<<"Rectangle(left): res = "<<setprecision(8)<<res<<", n = "<<n<<endl;
            n=1;
            trg=0;
        } else n++;
        res=0;
        buff=0;
    }
    trg=1;
    while(trg){
        h=(b-a)/n;
        h1=h/2;

        for(int i=1; i<n; i++)
            res=res+func(a+h*i);
        for(int i=1; i<n*2; i++)
            buff=buff+func(a+h1*i);

        res=res*h;
        buff=buff*h1;

        if(abs(buff-res)<=(e*3)){
            cout<<"Rectangle(right): res = "<<setprecision(8)<<res<<", n = "<<n<<endl;
            trg=0;
        } else n++;
        res=0;
        buff=0;
    }
    return 0;
}

double simpson(double a, double b, double e){
    double res, res1, h, buff, buff1, h1;
    int n=2;
    res=0;
    buff=0;
    res1=0;
    buff1=0;
    while(true){
        h=(b-a)/n;
        h1=h/2;

        for(int i=1; i<n/2; i++)
            res=res+func(a+h*(2*i-1));
        res=res*4;
        for(int i=1; i<n/2-1; i++)
            res1=res1+func(a+h*2*i);
        res1=res1*2;
        res=res+res1;

        for(int i=1; i<n; i++)
            buff=buff+func(a+h1*(2*i-1));
        buff=buff*4;
        for(int i=1; i<n-1; i++)
            buff1=buff1+func(a+h1*2*i);
        buff1=buff1*2;
        buff=buff+buff1;

        res=(res+func(a)+func(b))*h/3;
        buff=(buff+func(a)+func(b))*h1/3;

        if(abs(buff-res)<=(e*15)){
            cout<<"Simpson: res = "<<setprecision(8)<<res<<", n = "<<n<<endl;
            return 0;
        }
        res=0;
        buff=0;
        res1=0;
        buff1=0;
        n=n+2;
    }
    return 0;
}
