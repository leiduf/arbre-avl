#include "ArbreAVL.h"
#include <fstream>
#include <string>

enum class TypeRecherche
{
    ParNom,
    ParNoTel,
    Inconnue,
};

bool ChargerFichier(const string& nomFichier, Noeud* &racineNomPrenom, Noeud* &racineNoTel)
{
    ifstream fichier{nomFichier};

    if(!fichier)
    {
        return false;
    }

    while(!fichier.eof())
    {
        string chaine{};
        string nomPrenom{};
        fichier >> nomPrenom >> chaine;
        nomPrenom += ' ' + chaine;

        string noTel{};
        fichier >> noTel;

        racineNomPrenom = Ajouter(racineNomPrenom, nomPrenom, noTel);
        racineNoTel = Ajouter(racineNoTel, noTel, nomPrenom);
    }
    return true;
}

TypeRecherche DeterminerTypeRecherche() {
    cout << "Quel genre de recherche voulez-vous exécuter ?" << endl
         << "1. Trouver un numéro avec un nom" << endl
         << "2. Trouver un nom avec un numéro" << endl;
    int choix{};
    cin >> choix;

    //si choix pas dans l'intervalle [1,2] return inconnue, sinon type de recherche correspondant
    return choix < 1 || choix > 2 ? TypeRecherche::Inconnue : TypeRecherche(choix - 1);
}

bool faireChoixYN(const string& instruction)
{
    cout << instruction << " (Y/N)" << endl;

    char choix{};
    cin >> choix;

    return choix == 'y' || choix == 'Y';
}

int main() {
    cout << "Entrer le nom du fichier: ";
    string nomFichier{};
    cin >> nomFichier;
    Noeud* racineNoTel{};
    Noeud* racineNomPrenom{};

    if (!ChargerFichier(nomFichier, racineNomPrenom, racineNoTel)) {
        cout << "Fichier invalide." << endl;
        return -1;
    }

    bool refaireRecherche{false};
    do {
        TypeRecherche type{DeterminerTypeRecherche()};

        if(type == TypeRecherche::Inconnue)
        {
            cout << "Option invalide." << endl;
            return -2;
        }
        else
        {
            cout << "Entrez un élément à rechercher: ";
            string element{};
            cin.ignore();
            getline(cin, element);

            if (type == TypeRecherche::ParNom)
            {
                Afficher(racineNomPrenom, element);
            }
            else //ParNoTel
            {
                Afficher(racineNoTel, element);
            }
        }

        refaireRecherche = faireChoixYN("Refaire une recherche ?");

        cout << "---------------------------------------------------------------------------" << endl;
    } while(refaireRecherche);

    Supprimer(racineNomPrenom);
    Supprimer(racineNoTel);

    return 0;
}
