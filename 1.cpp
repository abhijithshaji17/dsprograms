// Template program 1
#include<iostream>
using namespace std;
template <typename T>
T large(T n1, T n2){
    return (n1>n2)?n1:n2;
}
int main(){
    cout<<large<int>(3,4)<<endl;
    cout<<large<float>(4.5,3.2)<<endl;
    cout<<large<string>("Hai","Ciao")<<endl;
    return 0;
}
