#include<iostream>
#include<stdio.h>

using namespace std;

main() {

int a[5];
    int temp=0;
    cout<<"Enter Values"<<endl;
    for(int i=0;i<5;i++)
    {
        cin>>a[i];
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    for(int i=0;i<5;i++)
    {
        cout<<endl;
        cout<<a[i]<<endl;
    }
}
