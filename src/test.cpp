#include <iostream>
using namespace std;
bool printa(int a,float b){
    cout<<"a"<<endl;
}
bool printb(int a,float b){
    cout<<"b"<<endl;
}
bool printc(int a,float b){
    cout<<"c"<<endl;
}
bool printd(int a,float b){
    cout<<"d"<<endl;
}
typedef bool (*func_ptr)(int a,float b);
int main()
{
    auto ptr = printb;
    ptr(1,1.5);
    return 0;
}