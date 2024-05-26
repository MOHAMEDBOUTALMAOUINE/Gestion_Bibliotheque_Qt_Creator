#include "livre.h"

Livre::Livre(int id, const std::string& titre, const std::string& auteur)
    : id(id), titre(titre), auteur(auteur), disponible(true) {}

int Livre::getId() const {
    return id;
}

std::string Livre::getTitre() const {
    return titre;
}

std::string Livre::getAuteur() const {
    return auteur;
}

bool Livre::isDisponible() const {
    return disponible;
}

void Livre::emprunter() {
    if (disponible) {
        disponible = false;
    }
}

void Livre::retourner() {
    if (!disponible) {
        disponible = true;
    }
}
