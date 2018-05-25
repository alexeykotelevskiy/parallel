#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <cmath>
#include <omp.h>
#include<ctime>
#include <chrono>
using namespace std;


double *a;
double *sum;
int n, k;
double calcLast(int v, int leftBorder)
{
    int leftNode = 2 * v + 1;
    int rightNode = 2 * v + 2;
    double leftSum = 0;
    double rightSum = 0;
    if (leftNode < n)
    {
        if (leftNode >= leftBorder)
            leftSum = sum[ leftNode- leftBorder];
        else
            leftSum = calcLast(leftNode , leftBorder);
    }
    if (rightNode < n)
    {
        if (rightNode >= leftBorder)
            rightSum = sum[rightNode- leftBorder];
        else
            rightSum = calcLast(rightNode , leftBorder);
    }
     sum[v] = leftSum + rightSum + a[v];
    return sqrt(fabs(sin(leftSum) * sin(leftSum) + cos(rightSum) * cos(rightSum))) + a[v];
}

double calc(int v)
{
    int leftNode = (v * 2)+1;
    int rightNode = (v * 2)+2;
    double leftSum = 0;
    double rightSum = 0;
    if (leftNode < n)
    {
        leftSum = calc(leftNode);
    }
    if (rightNode < n)
    {
        rightSum = calc(rightNode);
    }

    sum[v] = leftSum + rightSum + a[v];
    return sqrt(fabs(sin(leftSum) * sin(leftSum) + cos(rightSum) * cos(rightSum))) + a[v];
}

void task(pair<int, int> attrs)
{
    sum[attrs.first] = calc(attrs.second);
}

int main(int argc, char **argv)
{
 if (argc < 2)
    {
        return 1;
    }
   ifstream in(argv[1]/*"tests\\input2.txt"*/);

    in>>n >> k;
    a = new double[n];
    sum = new double[n];
    int x;
    for (int i=0;i<n;i++)
    {
        in >> a[i];
        sum[i] = 0;
    }
    int level = round((double)log(k) / log(2));
    int currVertex = pow(2, level) - 1;
    auto begin = clock();
    omp_set_num_threads(k);

    #pragma omp parallel for
    for (int i = 0; i < k; i++){
        pair<int, int> *q = new pair<int,int >;
        q->first = i;
        q->second = currVertex + i;
        task(*q);
    }

    double summa =  calcLast(0, pow(2, level) - 1);
    auto end = clock();
    cout<<end-begin<< endl;
    return 0;
}
