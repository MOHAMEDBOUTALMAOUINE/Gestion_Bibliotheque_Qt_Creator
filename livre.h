#ifndef LIVRE_H
#define LIVRE_H

#include <string>

class Livre {
public:
    Livre(int id, const std::string& titre, const std::string& auteur);

    int getId() const;
    std::string getTitre() const;
    std::string getAuteur() const;
    bool isDisponible() const;

    void emprunter();
    void retourner();

private:
    int id;
    std::string titre;
    std::string auteur;
    bool disponible;
};

#endif // LIVRE_H
