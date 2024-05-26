#include "bibliotheque.h"
#include <algorithm>

void Bibliotheque::ajouterLivre(int id, const std::string& titre, const std::string& auteur) {
    livres.emplace_back(id, titre, auteur);
}

void Bibliotheque::supprimerLivre(int id) {
    livres.erase(std::remove_if(livres.begin(), livres.end(), [id](const Livre& livre) {
                     return livre.getId() == id;
                 }), livres.end());
}

void Bibliotheque::emprunterLivre(int id) {
    for (Livre& livre : livres) {
        if (livre.getId() == id && livre.isDisponible()) {
            livre.emprunter();
            break;
        }
    }
}

void Bibliotheque::retournerLivre(int id) {
    for (Livre& livre : livres) {
        if (livre.getId() == id && !livre.isDisponible()) {
            livre.retourner();
            break;
        }
    }
}

Livre* Bibliotheque::rechercherLivreParId(int id) {
    for (Livre& livre : livres) {
        if (livre.getId() == id) {
            return &livre;
        }
    }
    return nullptr;
}

std::vector<Livre*> Bibliotheque::rechercherLivreParTitre(const std::string& titre) {
    std::vector<Livre*> result;
    for (Livre& livre : livres) {
        if (livre.getTitre() == titre) {
            result.push_back(&livre);
        }
    }
    return result;
}

std::vector<Livre*> Bibliotheque::rechercherLivreParAuteur(const std::string& auteur) {
    std::vector<Livre*> result;
    for (Livre& livre : livres) {
        if (livre.getAuteur() == auteur) {
            result.push_back(&livre);
        }
    }
    return result;
}

std::vector<Livre> Bibliotheque::getLivres() const {
    return livres;
}

void Bibliotheque::trierParId() {
    std::sort(livres.begin(), livres.end(), [](const Livre& a, const Livre& b) {
        return a.getId() < b.getId();
    });
}

void Bibliotheque::trierParTitre() {
    std::sort(livres.begin(), livres.end(), [](const Livre& a, const Livre& b) {
        return a.getTitre() < b.getTitre();
    });
}

void Bibliotheque::trierParAuteur() {
    std::sort(livres.begin(), livres.end(), [](const Livre& a, const Livre& b) {
        return a.getAuteur() < b.getAuteur();
    });
}
