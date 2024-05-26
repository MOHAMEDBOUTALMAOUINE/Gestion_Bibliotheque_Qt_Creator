#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouterButton_clicked()
{
    int id = ui->idLineEdit->text().toInt();
    QString titre = ui->titreLineEdit->text();
    QString auteur = ui->auteurLineEdit->text();

    if (titre.isEmpty() || auteur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer tous les champs.");
        return;
    }

    bibliotheque.ajouterLivre(id, titre.toStdString(), auteur.toStdString());
    updateTables();
}

void MainWindow::on_supprimerButton_clicked()
{
    int id = ui->idLineEdit->text().toInt();
    if (ui->idLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID du livre à supprimer.");
        return;
    }
    bibliotheque.supprimerLivre(id);
    updateTables();
}

void MainWindow::on_emprunterButton_clicked()
{
    int id = ui->idLineEdit->text().toInt();
    bibliotheque.emprunterLivre(id);
    updateTables();
}

void MainWindow::on_retournerButton_clicked()
{
    int id = ui->idLineEdit->text().toInt();
    bibliotheque.retournerLivre(id);
    updateTables();
}

void MainWindow::on_rechercherButton_clicked()
{
    QString recherche = ui->rechercheLineEdit->text();
    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un critère de recherche.");
        return;
    }

    std::string rechercheStr = recherche.toStdString();
    bool trouve = false;
    ui->resultatListWidget->clear();

    // Recherche par ID
    if (recherche.toInt() != 0) {
        Livre* livre = bibliotheque.rechercherLivreParId(recherche.toInt());
        if (livre) {
            ui->resultatListWidget->addItem(QString::fromStdString("ID: " + std::to_string(livre->getId()) +
                                                                   ", Titre: " + livre->getTitre() + ", Auteur: " + livre->getAuteur()));
            trouve = true;
        }
    }

    // Recherche par Titre
    std::vector<Livre*> livresTitre = bibliotheque.rechercherLivreParTitre(rechercheStr);
    for (Livre* livre : livresTitre) {
        ui->resultatListWidget->addItem(QString::fromStdString("ID: " + std::to_string(livre->getId()) +
                                                               ", Titre: " + livre->getTitre() + ", Auteur: " + livre->getAuteur()));
        trouve = true;
    }

    // Recherche par Auteur
    std::vector<Livre*> livresAuteur = bibliotheque.rechercherLivreParAuteur(rechercheStr);
    for (Livre* livre : livresAuteur) {
        ui->resultatListWidget->addItem(QString::fromStdString("ID: " + std::to_string(livre->getId()) +
                                                               ", Titre: " + livre->getTitre() + ", Auteur: " + livre->getAuteur()));
        trouve = true;
    }

    if (!trouve) {
        ui->resultatListWidget->addItem("Aucun résultat trouvé.");
    }
}

void MainWindow::on_trierButton_clicked()
{
    if (ui->triIdRadioButton->isChecked()) {
        bibliotheque.trierParId();
    } else if (ui->triTitreRadioButton->isChecked()) {
        bibliotheque.trierParTitre();
    } else if (ui->triAuteurRadioButton->isChecked()) {
        bibliotheque.trierParAuteur();
    }
    updateTables();
}

void MainWindow::updateTables()
{
    ui->disponiblesTableWidget->setRowCount(0);
    ui->empruntesTableWidget->setRowCount(0);

    for (const Livre& livre : bibliotheque.getLivres()) {
        int row = ui->disponiblesTableWidget->rowCount();
        if (livre.isDisponible()) {
            ui->disponiblesTableWidget->insertRow(row);
            ui->disponiblesTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(livre.getId())));
            ui->disponiblesTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(livre.getTitre())));
            ui->disponiblesTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(livre.getAuteur())));
        } else {
            row = ui->empruntesTableWidget->rowCount();
            ui->empruntesTableWidget->insertRow(row);
            ui->empruntesTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(livre.getId())));
            ui->empruntesTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(livre.getTitre())));
            ui->empruntesTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(livre.getAuteur())));
        }
    }
}
