//
// Created by etudiant on 23-11-08.
//

#ifndef TP2_LEIDUF_ARBREAVL_H
#define TP2_LEIDUF_ARBREAVL_H

#include "File.h"

struct Personne {
    string cle{};
    File element{};
};

struct Noeud {
    Personne personne{};
    Noeud* gauche{};
    Noeud* droite{};
    int hauteur{-1};
};

int max(int a, int b);

int hauteur(Noeud* noeud);

void ajusterHauteur(Noeud* noeud);

Noeud *RotationGauche(Noeud* noeud);

Noeud *RotationDroite(Noeud* noeud);

Noeud *DoubleRotationGauche(Noeud* noeud);

Noeud *DoubleRotationDroite(Noeud* noeud);

Noeud *BalancerNoeud(Noeud *noeud);

Noeud *Ajouter(Noeud* noeud, const string& cle, const string& element);

Noeud *Recherche(Noeud* noeud, const string& cle);

void Afficher(Noeud *noeud, const string &cle);

void Supprimer(Noeud* noeud);

#endif //TP2_LEIDUF_ARBREAVL_H
