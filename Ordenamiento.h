#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H
#include <iostream>
#include <sstream>

using namespace std;

void intercambio(int a[][2], int min,int i){
	int n=a[i][1],m=a[i][0];
	a[i][1]=a[min][1];
	a[i][0]=a[min][0];
	a[min][1]=n;
	a[min][0]=m;
	
	
}

void seleccion (int a[][2], int N){
	int i,j,min;
    for (i=0;i<N-1; i++){
    min = i;
        for (j=i+1;j<N; j++){
			if(a[j][1]<a[min][1]){
				min = j;
			}
		}
        intercambio(a, min, i);
    }    
}

void burbuja (int a[][2], int N){
	int i,j;
  	for (i=N; i>=0; i--){	  
     	for(j=1; j<i; j++){		 
           	if(a[j-1]> a[j]){
		    	intercambio(a,j-1,j);
			}
		}
	}
}

void insercion (int a[], int n){
	int i,j;
	int v;
  	for (i=1; i<n; i++){
	  	j=i; 
		v=a[j];
       	while(a[j-1]>v && j>0){
			a[j]=a[j-1];
           	j--;
        }
        a[j]= v;
    }
}



#endif   
