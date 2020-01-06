#include "Mint.h"
#include <stdlib.h>
#include <string.h>

Mint::Mint(int nbr)
{
    int taille = 0;
    int new_nbr = nbr;

    while(new_nbr){
        taille++;
        new_nbr = new_nbr / 10;
    }

    taille_effective = taille;
    mint = new int[4];

    for(int i = taille - 1; i>= 0; i--){
        mint[i] = nbr % 10;
        nbr = nbr / 10;
    }
}

Mint::Mint(char* nbr)
{
    int taille = 0;
    while(nbr[++taille]){
    }

    bool found_error = false;
    /*for(int i = 0; i < taille; i++){
        if(nbr[i] - '0' < 0 || nbr[i] - '0' > 9){
            cout<<"Error !!"<<endl;
            found_error = true;
            break;
        }
    }*/

    if(!found_error){
        taille_effective = taille;
        mint = new int[taille];

        for(int i = 0; i < taille_effective; i++){
            mint[i] = nbr[i] - '0';
        }
    }else {
        taille_effective = 0;
        mint = new int[1];
    }
}

Mint::Mint(const Mint& cpy){
    taille_effective = cpy.taille_effective;
    mint = new int[taille_effective];
    for(int i=0; i<taille_effective; i++){
        mint[i] = cpy.mint[i];
    }
    /*cout<<"\nMint copied : "<<endl;
    afficher();*/
}

void Mint::afficher(){
    cout<<endl;
    for(int i = 0; i < taille_effective; i++){
        cout<<mint[i];
    }
}


Mint operator+(Mint m1, Mint m2){
    int taille = m1.taille_effective > m2.taille_effective ? m1.taille_effective : m2.taille_effective;
    int petite_taille = m1.taille_effective > m2.taille_effective ? m2.taille_effective : m1.taille_effective;

    Mint used_mint = "";

    used_mint.mint = new int[taille];
    used_mint.taille_effective = taille;

    int retenue = 0;
    for(int i = taille - 1, j = petite_taille - 1 ; i >= taille - petite_taille; i--){
        if(m1.taille_effective > m2.taille_effective){
            if((m1.mint[i] + m2.mint[j]) + retenue >= 10){
                used_mint.mint[i] = (m1.mint[i] + m2.mint[j] + retenue) % 10;
                retenue = (m1.mint[i] + m2.mint[j] + retenue) / 10;
            }else {
                used_mint.mint[i] = m1.mint[i] + m2.mint[j] + retenue;
                retenue = 0;
            }
        }else{
            if((m1.mint[j] + m2.mint[i]) + retenue >= 10){
                used_mint.mint[i] = (m1.mint[j] + m2.mint[i] + retenue) % 10;
                retenue = (m1.mint[j] + m2.mint[i] + retenue) / 10;
            }else {
                used_mint.mint[i] = m1.mint[j] + m2.mint[i] + retenue;
                retenue = 0;
            }
        }

        j--;
    }

    if(petite_taille > 0 && petite_taille < taille){
        for(int i = taille - petite_taille - 1; i >= 0 ; i--){
            if(m1.taille_effective > m2.taille_effective){
                if((m1.mint[i] + retenue) >= 10){
                    used_mint.mint[i] = (m1.mint[i] + retenue) % 10;
                    retenue = (m1.mint[i] + retenue) / 10;
                }else{
                    used_mint.mint[i] = m1.mint[i] + retenue;
                    retenue = 0;
                }
            }else if(m1.taille_effective < m2.taille_effective){
                if((m2.mint[i] + retenue) >= 10){
                    used_mint.mint[i] = (m2.mint[i] + retenue) % 10;
                    retenue = (m2.mint[i] + retenue) / 10;
                }else{
                    used_mint.mint[i] = m2.mint[i] + retenue;
                    retenue = 0;
                }
            }

        }
    }
    if(retenue != 0){
        taille++;
        Mint last_mint = "";
        last_mint.mint = new int[taille];
        last_mint.taille_effective = taille;

        for(int i=0,j=0; i <taille; i++){
            if(i == 0)
                last_mint.mint[i] = retenue;
            else{
                last_mint.mint[i] = used_mint.mint[j];
                j++;
            }
        }

        return last_mint;
    }

    return used_mint;
}

Mint operator* (Mint m1, Mint m2){
    int taille = m1.taille_effective > m2.taille_effective ? m1.taille_effective : m2.taille_effective;
    int petite_taille = m1.taille_effective > m2.taille_effective ? m2.taille_effective : m1.taille_effective;

    Mint used_mint("0");

    used_mint.mint = new int[taille];
    used_mint.taille_effective = taille;

    Mint total_multiplication("0");

    int retenue = 0;
    int multiplicator = 0;

    for(int i = petite_taille - 1; i >= 0; i--){
        for(int j = taille - 1; j >= 0; j--){
            if(m1.taille_effective > m2.taille_effective){
                if((m1.mint[j] * m2.mint[i] + retenue) >= 10){
                    used_mint.mint[j] = (m1.mint[j] * m2.mint[i] + retenue) % 10;
                    retenue = (m1.mint[j] * m2.mint[i] + retenue) / 10;
                }else {
                    used_mint.mint[j] = m1.mint[j] * m2.mint[i] + retenue;
                    retenue = 0;
                }
            }
            else {
                if((m1.mint[i] * m2.mint[j] + retenue) >= 10){
                    used_mint.mint[j] = (m1.mint[i] * m2.mint[j] + retenue) % 10;
                    retenue = (m1.mint[i] * m2.mint[j] + retenue) / 10;
                }else {
                    used_mint.mint[j] = m1.mint[i] * m2.mint[j] + retenue;
                    retenue = 0;
                }
            }
        }

        Mint mint_retenue ("0");
        mint_retenue += used_mint;

        if(retenue != 0){
            mint_retenue.mint = new int[used_mint.taille_effective + 1];
            mint_retenue.taille_effective = used_mint.taille_effective + 1;

            for(int k = 0; k < mint_retenue.taille_effective; k++){
                if(k == 0){
                    mint_retenue.mint[k] = retenue;
                    retenue = 0;
                }
                else {
                    mint_retenue.mint[k] = used_mint.mint[k-1];
                }
            }
        }

        cout<<"\nMint Retenue : ";
        mint_retenue.afficher();

        Mint final_mint("0");
        final_mint += mint_retenue;

                    cout<<"\nMint Retenue : ";
        mint_retenue.afficher();

        if(multiplicator > 0){
                cout<<"\n";
            final_mint.taille_effective += multiplicator;
            for(int mul = 0; mul < final_mint.taille_effective; mul++){
                if(mul <= mint_retenue.taille_effective - 1){
                    final_mint.mint[mul] = mint_retenue.mint[mul];
                    cout<<"\ntaille mint retenue : "<<mint_retenue.taille_effective;
                    mint_retenue.afficher();
                    cout<<"\nfinal_mint["<<mul<<"] = "<<final_mint.mint[mul]<<"\tmint_retenue["<<mul<<"] = "<<mint_retenue.mint[mul];
                }
                else
                    final_mint.mint[mul] = 0;

            }
        }

        //cout<<"\ntaille : "<<final_mint.taille_effective;
        /*cout<<"\nfinal mint :";
            final_mint.afficher();*/

        /*cout<<"\nTotal multiplication :";
        total_multiplication.afficher();*/

        //cout<<"\nTaille total multiplication avant ajout :"<<total_multiplication.taille_effective;
        final_mint.afficher();
        /*cout<<"\n+";
        total_multiplication.afficher();*/
        total_multiplication += final_mint;

        /*out<<"\nNouveau Total multiplication :";
        total_multiplication.afficher();*/
        //cout<<"\nTaille total multiplication :"<<total_multiplication.taille_effective;
        multiplicator++;
    }

    return total_multiplication;
}

Mint& Mint::operator+=(Mint m2){
    *this = *this + m2;

    return *this;
}

Mint operator+(Mint m1, int nbr){
    Mint q = Mint(nbr);
    Mint d = "";
    d = m1 + q;
    return d;
}

Mint& Mint::operator+=(int nbr){
    Mint q = Mint(nbr);
    Mint d = "";
    *this = *this + q;

    return *this;
}

bool operator<(Mint m1, Mint m2){
    if(m1.taille_effective < m2.taille_effective)
        return true;

    if(m1.taille_effective > m2.taille_effective)
        return false;

    for(int i = 0 ; i < m1.taille_effective; i++){
        if(m1.mint[i] > m2.mint[i] || m1.mint[i] == m2.mint[i])
            return false;
    }

    return true;
}

bool operator>(Mint m1, Mint m2){
    if(m1.taille_effective > m2.taille_effective)
        return true;

    if(m1.taille_effective < m2.taille_effective)
        return false;

    for(int i = 0 ; i < m1.taille_effective; i++){
        if(m1.mint[i] < m2.mint[i] || m1.mint[i] == m2.mint[i])
            return false;
    }

    return true;
}

bool operator<=(Mint m1, Mint m2){
    if(m1.taille_effective < m2.taille_effective)
        return true;

    if(m1.taille_effective > m2.taille_effective)
        return false;

    for(int i = 0 ; i < m1.taille_effective; i++){
        if(m1.mint[i] > m2.mint[i])
            return false;
    }

    return true;
}

bool operator>=(Mint m1, Mint m2){
    if(m1<=m2)
        return false;
    else
        return true;
}

unsigned int Mint::toUnsignedInt(){
    unsigned int nbr_converti = 0;
    int nbr_multiplication = 1;

    for(int i = taille_effective - 1; i >= 0; i--){
        nbr_converti += mint[i] * nbr_multiplication;
        nbr_multiplication *= 10;
    }

    return nbr_converti;
}

float Mint::toFloat(){
    float nbr_converti = 0;
    int nbr_multiplication = 1;

    for(int i = taille_effective - 1; i >= 0; i--){
        nbr_converti += mint[i] * nbr_multiplication;
        nbr_multiplication *= 10;
    }

    return nbr_converti;
}
