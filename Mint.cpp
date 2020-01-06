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
    while(nbr[++taille]){ //on calcule la taille de la chaine
    }

    taille_effective = taille;
    mint = new int[taille];

    for(int i = 0; i < taille_effective; i++){
        mint[i] = nbr[i] - '0'; //cette operation permet de transformer un nombre char en nombre int
    }

}

Mint::Mint(const Mint& cpy){
    taille_effective = cpy.taille_effective;
    mint = new int[taille_effective];
    for(int i=0; i<taille_effective; i++){
        mint[i] = cpy.mint[i];
    }
}

void Mint::afficher(){
    cout<<endl;
    for(int i = 0; i < taille_effective; i++){
        cout<<mint[i];
    }
}


Mint operator+(Mint m1, Mint m2){
    //On selectionne la taille du mint le plus grand et du plus petit.
    int taille = m1.taille_effective > m2.taille_effective ? m1.taille_effective : m2.taille_effective;
    int petite_taille = m1.taille_effective > m2.taille_effective ? m2.taille_effective : m1.taille_effective;

    Mint used_mint = ""; //ceci est le mint dans lequel on stock l'addition des 2 mints entrer
    used_mint.mint = new int[taille]; //sa taille sera celle du plus grand mint des 2
    used_mint.taille_effective = taille;

    int retenue = 0;

    //on execute une boucle qui par de la fin du grand mint jusqu'a la fin du petit mint
    for(int i = taille - 1, j = petite_taille - 1 ; i >= taille - petite_taille; i--){
        if(m1.taille_effective > m2.taille_effective){
            //si l'addition du nbr courant de m1 et de m2 + la retenue est superieur a 10
            if((m1.mint[i] + m2.mint[j]) + retenue >= 10){
                //on stock le reste de la division par 10 dans le nouveau mint et le quotient dans la retenue
                used_mint.mint[i] = (m1.mint[i] + m2.mint[j] + retenue) % 10;
                retenue = (m1.mint[i] + m2.mint[j] + retenue) / 10;
            }else {
                //sinon on stock tout dans le nouveau mint et la retenue devient 0
                used_mint.mint[i] = m1.mint[i] + m2.mint[j] + retenue;
                retenue = 0;
            }
        }else{
            //le meme traitement que le if sauf pour cette fois le cas de m2 >= m1
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

    //si on a un cas ou un mint est superieur a l'autre en taille (exp : 1500 + 10)
    if(petite_taille > 0 && petite_taille < taille){
        //on effectue une boucle qui stockera le reste des nbr du mint le plus grand dans le nouveau mint
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

    //si apres avoir effectuer l'addition des 2 mints bit par bit on se retrouve avec une retenue superieure a 0
    if(retenue != 0){
        taille++;
        Mint last_mint = ""; //on creer un nouveau mint qui stockera le mint de l'addition + le bit de la retenue
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
    //On selectionne la taille du mint le plus grand et du plus petit.
    int taille = m1.taille_effective > m2.taille_effective ? m1.taille_effective : m2.taille_effective;
    int petite_taille = m1.taille_effective > m2.taille_effective ? m2.taille_effective : m1.taille_effective;

    Mint used_mint("0"); //ceci est le mint dans lequel on stock la multiplication de 1 bit * tout l'autre mint
                        //exemple pour 150 * 15 ce mint stockera 5 * 150 puis 1 * 150

    used_mint.mint = new int[taille];
    used_mint.taille_effective = taille;

    Mint total_multiplication("0"); //ceci est le mint dans lequel on stock toute la multiplication

    int retenue = 0;
    int multiplicator = 0; //cette variable determine le nbr de 0 a ajouter a la fin d'une multiplication calculer
                           //exemple pour 150 * 15 dans le cas du 5 * 150 = 750
                           //mais 1 * 150 = 1500 car 1 est le 2eme nbr du mint.

    //on effectue une boucle qui parcours tous les nbrs du plus petit mint
    for(int i = petite_taille - 1; i >= 0; i--){
        //une deuxieme boucle qui parcours tous les nbrs du grand mint
        for(int j = taille - 1; j >= 0; j--){
            if(m1.taille_effective > m2.taille_effective){
                //si la multiplication du nbr courant de m1 et de m2 + la retenue est superieur a 10
                if((m1.mint[j] * m2.mint[i] + retenue) >= 10){
                    //on stock le reste de la division dans le nouveau mint et le quotient dans la retenue
                    used_mint.mint[j] = (m1.mint[j] * m2.mint[i] + retenue) % 10;
                    retenue = (m1.mint[j] * m2.mint[i] + retenue) / 10;
                }else {
                    used_mint.mint[j] = m1.mint[j] * m2.mint[i] + retenue;
                    retenue = 0;
                }
            }
            else {
                //meme traitement que le if pour le cas du m2 >= m1
                if((m1.mint[i] * m2.mint[j] + retenue) >= 10){
                    used_mint.mint[j] = (m1.mint[i] * m2.mint[j] + retenue) % 10;
                    retenue = (m1.mint[i] * m2.mint[j] + retenue) / 10;
                }else {
                    used_mint.mint[j] = m1.mint[i] * m2.mint[j] + retenue;
                    retenue = 0;
                }
            }
        }

        Mint mint_retenue ("0"); //ce nouveau mint stockera le mint calculer plus la retenue restante si elle existe
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

        //ce mint est le dernier que l'on va utiliser il stockera le mint_retenue plus les zeros a ajouter du multiplicateur
        Mint final_mint("0");
        final_mint += mint_retenue;

        if(multiplicator > 0){
            //si il existe des zeros a ajouter on augmente la taille du mint par ce nbrs de zeros
            final_mint.taille_effective += multiplicator;

            //ensuite on effectue une boucle qui stockera le mint_retenue et les zeros a ajouter dans final_mint
            for(int mul = 0; mul < final_mint.taille_effective; mul++){
                if(mul <= mint_retenue.taille_effective - 1)
                    final_mint.mint[mul] = mint_retenue.mint[mul];

                else
                    final_mint.mint[mul] = 0;

            }
        }

        //on ajoute le final_mint au total multiplication
        total_multiplication += final_mint; //donc pour reprendre notre exemple precedant de 150 * 15
                                            //on aura 5 * 150 = 750
                                            // est 1 * 150 = 1500
                                            //total_multiplication = 750 + 1500 = 2250

        //on incremente le multiplicateur car on passe a un nouveau nombre
        multiplicator++;
    }

    return total_multiplication;
}

Mint operator*(Mint m1, int nbr){
    Mint m2(nbr);
    Mint  result = m1 * m2;

    return result;
}

Mint& Mint::operator*=(Mint m2){
    *this = *this * m2;

    return *this;
}

Mint& Mint::operator*=(int nbr){
    Mint m2(nbr);

    *this = *this * m2;

    return *this;
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
    Mint q(nbr);
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

Mint& Mint::operator++()
{
	*this= *this+1;
	return *this;
}
Mint Mint::operator++(int)
{
	Mint result = *this;
	++(*this);

	return result;
}
