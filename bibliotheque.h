#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include "livre.h"
#include <vector>
#include <algorithm>

class Bibliotheque {
public:
    void ajouterLivre(int id, const std::string& titre, const std::string& auteur);
    void supprimerLivre(int id);
    void emprunterLivre(int id);
    void retournerLivre(int id);
    Livre* rechercherLivreParId(int id);
    std::vector<Livre*> rechercherLivreParTitre(const std::string& titre);
    std::vector<Livre*> rechercherLivreParAuteur(const std::string& auteur);
    std::vector<Livre> getLivres() const;

    void trierParId();
    void trierParTitre();
    void trierParAuteur();

private:
    std::vector<Livre> livres;
};

#endif // BIBLIOTHEQUE_H
