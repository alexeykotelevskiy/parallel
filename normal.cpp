#include<fstream>
#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include <chrono>
using namespace std;

double *a,*sum;
int n,k;
double calc(int v){
    int leftNode = 2 * v + 1;
    int rightNode = 2* v + 2;
    double leftSum = 0;
    double rightSum = 0;
    if (leftNode < n)
        leftSum = calc(leftNode);
    if (rightNode < n)
        rightSum = calc(rightNode);
    sum[v] =  sqrt(fabs(sin(leftSum) * sin(leftSum) + cos(rightSum) * cos(rightSum))) + a[v];
    return sum[v];
}


int main(int argc, char **argv){
    if (argc < 2) return 1;
     ifstream in(argv[1]);
    in >> n >> k;
    a = new double[n];
    sum = new double[n];
    for (int i=0; i < n; i++)
    {
        in >> a[i];
        sum[i] = 0;
    }
    in.close();

    auto begin = clock();
    calc(0);
    auto end = clock();
    cout<<end-begin<< endl;
    return 0;
}
