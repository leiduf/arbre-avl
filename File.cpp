//
// Created by etudiant on 23-11-10.
//

#include "File.h"

void Enfiler(File& Sequence, const string& element)
{
    NoeudFile *nouveau{new NoeudFile{element, nullptr}};
    if(Sequence.tete == nullptr) //File vide
    {
        Sequence.tete = nouveau;
    }
    else //fin
    {
        Sequence.queue->suivant = nouveau;
    }
    Sequence.queue = nouveau;
    nouveau = nullptr;

    Sequence.tailleFile++;
}

void SupprimerFile(File &Sequence) {
    for(int i{0}; i < Sequence.tailleFile; i++)
    {
        NoeudFile *courant = Sequence.tete;
        Sequence.tete = Sequence.tete->suivant;
        courant->suivant = nullptr;
        delete courant;
    }
}
