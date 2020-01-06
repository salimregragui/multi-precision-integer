#include <iostream>
#include "Mint.h"

using namespace std;

/*int multiplication(int n) {
    int total = 0;
    for(int i = 1; i <= 700; i++){
        total += n;
    }

    return total;
}*/

int main()
{
    Mint a("2");
    a.afficher();

    Mint b("12345678912345678963214785");
    b.afficher();
	Mint c=a++;
	a.afficher();
	c.afficher();
  //  Mint c = a * b;
  //  c.afficher();

    //Mint q = a * b;
    //cout<<"\nTotal multiplication : ";
    //q.afficher();


    /*Mint c = "198598168945150";
    c.afficher();

    Mint d = b;
    d.afficher();*/


    /*Mint q = "1250";
    q = a + b;
    q.afficher();*/

    /*a += b;
    a.afficher();*/

    /*if(a > b)
        printf("\na est superieur b");
    else
        printf("\na est inferieur b");*/

    return 0;
}
