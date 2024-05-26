#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bibliotheque.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterButton_clicked();
    void on_supprimerButton_clicked();
    void on_emprunterButton_clicked();
    void on_retournerButton_clicked();
    void on_rechercherButton_clicked();
    void on_trierButton_clicked();
    void updateTables();

private:
    Ui::MainWindow *ui;
    Bibliotheque bibliotheque;
};

#endif // MAINWINDOW_H
