//
// Created by etudiant on 23-11-10.
//

#ifndef TP2_LEIDUF_FILE_H
#define TP2_LEIDUF_FILE_H

#include <iostream>

using namespace std;

struct NoeudFile
{
    string element{};
    NoeudFile* suivant{};
};

struct File
{
    NoeudFile* tete{};
    NoeudFile* queue{};
    int tailleFile{};
};

void Enfiler(File& Sequence, const string& element);

void SupprimerFile(File& Sequence);

#endif //TP2_LEIDUF_FILE_H
