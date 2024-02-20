//
// Created by etudiant on 23-11-08.
//

#include "ArbreAVL.h"

int max(int a, int b)
{
    return a > b ? a : b;
}

int hauteur(Noeud *noeud) {
    if(noeud==nullptr)
    {
        return -1;
    }
    return noeud->hauteur;
}

void ajusterHauteur(Noeud* noeud) {
    noeud->hauteur = max(hauteur(noeud->gauche), hauteur(noeud->droite)) + 1;
}

Noeud *RotationGauche(Noeud *noeud) {
    if(noeud==nullptr)
    {
        return nullptr;
    }
    Noeud* nouveauNoeud = noeud->droite;
    noeud->droite = nouveauNoeud->gauche;
    nouveauNoeud->gauche = noeud;

    ajusterHauteur(noeud);
    ajusterHauteur(nouveauNoeud);
    return nouveauNoeud;
}

Noeud *RotationDroite(Noeud *noeud) {
    if(noeud==nullptr)
    {
        return nullptr;
    }
    Noeud* nouveauNoeud = noeud->gauche;
    noeud->gauche = nouveauNoeud->droite;
    nouveauNoeud->droite = noeud;

    ajusterHauteur(noeud);
    ajusterHauteur(nouveauNoeud);
    return nouveauNoeud;
}

Noeud *DoubleRotationGauche(Noeud *noeud) {
    if(noeud==nullptr)
    {
        return nullptr;
    }
    noeud->droite = RotationDroite(noeud->droite);
    return RotationGauche(noeud);
}

Noeud *DoubleRotationDroite(Noeud *noeud) {
    if(noeud==nullptr)
    {
        return nullptr;
    }
    noeud->gauche = RotationGauche(noeud->gauche);
    return RotationDroite(noeud);
}

Noeud *BalancerNoeud(Noeud *noeud) {
    int balance{hauteur(noeud->gauche) - hauteur(noeud->droite)};

    if(balance > 1) //+2
    {
        int balanceEnfant{hauteur(noeud->gauche->gauche) - hauteur(noeud->gauche->droite)};
        if (balanceEnfant == 1)
        {
            // gauche gauche
            noeud = RotationDroite(noeud);
        }
        else
        {
            //gauche droite
            noeud = DoubleRotationDroite(noeud);
        }
    }
    else if(balance < -1) // -2
    {
        int balanceEnfant{hauteur(noeud->droite->gauche) - hauteur(noeud->droite->droite)};

        if (balanceEnfant == -1)
        {
            //droite droite
            noeud = RotationGauche(noeud);
        }
        else
        {
            //droite gauche
            noeud = DoubleRotationGauche(noeud);
        }
    }
    return noeud;
}

Noeud *Ajouter(Noeud* noeud, const string& cle, const string& element)
{
    if(noeud==nullptr) {
        NoeudFile* nouvelElement{new NoeudFile{element, nullptr}};
        return new Noeud{cle, nouvelElement, nouvelElement, 1, nullptr, nullptr, 0};
    }
    if (cle < noeud->personne.cle) {
        //faire ajout à gauche
        noeud->gauche = Ajouter(noeud->gauche, cle, element);
    }
    else if (cle > noeud->personne.cle) {
        //Ajout côté droit
        noeud->droite = Ajouter(noeud->droite, cle, element);
    }
    else //doublon
    {
        Enfiler(noeud->personne.element, element);
    }
    ajusterHauteur(noeud);

    return BalancerNoeud(noeud);
}

Noeud* Recherche(Noeud *noeud, const string &cle) {
    while(noeud != nullptr && cle != noeud->personne.cle )
    {
        if(cle < noeud->personne.cle)
        {
            return Recherche(noeud->gauche, cle);
        }
        else
        {
            return Recherche(noeud->droite, cle);
        }
    }
    return noeud;
}
void Afficher(Noeud* noeud, const string &cle) {
    Noeud* noeudAfficher{Recherche(noeud, cle)};

    if(noeudAfficher == nullptr)
    {
        cout << "Element introuvable" << endl;
    }
    else
    {
        cout << noeudAfficher->personne.cle << endl;
        NoeudFile* courant{noeudAfficher->personne.element.tete};

        cout << courant->element << endl;
        while(courant->suivant != nullptr)
        {
            courant = courant->suivant;
            cout << courant->element << endl;
        }
    }
}

void Supprimer(Noeud* noeud) {
    if(noeud == nullptr)
    {
        return;
    }

    Supprimer(noeud->gauche);
    Supprimer(noeud->droite);

    SupprimerFile(noeud->personne.element);
    delete noeud;
}