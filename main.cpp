#include <iostream>
#include "Mint.h"

using namespace std;

//fonction qui permet de stocker la factorielle d'un nombre dans un mint
Mint factorielle(int n) {
    Mint total("1");
    for(int i = 1; i <= n; i++){
        total = total * i;
    }

    return total;
}

int main()
{
    Mint a("1259755");
    a.afficher();

    Mint b("11949585285");
    b.afficher();

    Mint c = a * b;
    cout<<"\nTotal multiplication : ";
    c.afficher();


    Mint d = ++b;
    d.afficher();

    Mint q = factorielle(60);
    cout<<"\n60 factorielle est :";
    q.afficher();

    if(a <= b)
        printf("\na est inferieur ou egal b");
    else
        printf("\na est superieur b");

    return 0;
}
