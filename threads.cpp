#include <iostream>
#include <fstream>
#include <pthread.h>
#include <vector>
#include <cmath>
#include<ctime>
#include<cstdlib>
#include <chrono>
using namespace std;


double *a,*sum;
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
     sum[v] = sqrt(fabs(sin(leftSum) * sin(leftSum) + cos(rightSum) * cos(rightSum))) + a[v];
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

    return sqrt(fabs(sin(leftSum) * sin(leftSum) + cos(rightSum) * cos(rightSum))) + a[v];
}

void *task(void *x)
{
    pair<int, int> *attrs = ((pair<int, int>*)x);
    sum[attrs->first] = calc(attrs->second);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 1;
    }
   ifstream in(argv[1]/*"tests\\input1.txt"*/);


    in>>n >> k;
    a = new double[n];
    sum = new double[n];
    int x;
    for (int i=0;i<n;i++)
    {
        in >> a[i];
        sum[i] = 0;
    }
    pthread_t *threads = new pthread_t[k];
    int level = round((double)log(k) / (double)log(2));
    int currVertex = pow(2, level) - 1;
   auto begin = clock();
    for (int i = 0; i < k; i++){
        pair<int, int> *q = new pair<int,int >;
        q->first = i;
        q->second = currVertex;
        currVertex++;
        pthread_create(&threads[i], NULL, task, (void*)(q));
    }
for (int i=0;i<k;i++){
    pthread_join(threads[i], NULL);
}

calcLast(0, pow(2, level) - 1);
auto end = clock();
cout<<end-begin<< endl;

return 0;
}
