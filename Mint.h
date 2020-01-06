#ifndef MINT_H
#define MINT_H

#include <iostream>
using namespace std;


class Mint
{
    public:
        Mint(int);
        Mint(char*);
        Mint(const Mint&);

        friend Mint operator+(Mint, Mint);
        friend Mint operator+(Mint, int);
        friend Mint operator*(Mint, Mint);
        friend Mint operator*(Mint, int);
        Mint& operator+=(Mint);
        Mint& operator+=(int);
        Mint& operator*=(Mint);
        Mint& operator*=(int);
        Mint& operator++();
        Mint operator++(int);

        friend bool operator<(Mint, Mint);
        friend bool operator>(Mint, Mint);
        friend bool operator<=(Mint, Mint);
        friend bool operator>=(Mint, Mint);
        unsigned int toUnsignedInt();
        float toFloat();

        void afficher();

    private:
        int* mint;
        int taille_effective;
};

#endif // MINT_H
