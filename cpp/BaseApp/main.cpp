#include <iostream>
#include <cstring>
using namespace std;

int fact(int num)
{
    if(num == 1 || num == 0)
    {
        return 1;
    }
    int factRes = num*fact(num-1);
    return factRes;
}

int main()
{
    int num;
    num = 5;
    int res = fact(num);
    cout<<"Factorial is : "<<res<<endl;
}























// int add(int a, int b)
// {
//     int res = a+b;
//     return res;
// }

// int sub(int a, int b)
// {
//     int res = a+b;
//     return res;
// }

// int prod(int a, int b)
// {
//     int res = a+b;
//     return res;
// }

// int main()
// {
//     int a, b;
//     cin>>a>>b;
//     int resAdd = add(a, b);
//     int resSub = sub(a, b);
//     int resProd = prod(a, b);

//     cout<<resAdd<<endl;
//     cout<<resSub<<endl;
//     cout<<resProd<<endl;
// }
























// int main()
// {
//     int n1, n2, n3;
//     n1=1; n2=2; n3=3;
//     int sum, avg;
//     sum = n1+n2+n3;
//     avg = sum/3;
//     cout<<"Sum : "<<sum<<endl;
//     cout<<"Avg : "<<avg<<endl;

//     return 0;
// }
