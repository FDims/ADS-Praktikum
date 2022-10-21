/*************************************************
 * ADS Praktikum 2.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:



/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV" 
 
Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/
void mainscreen_addTreeCSV(Tree*& ref)
{
    char j;
    cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
            "importieren(j / n) ? >";
    cin >> j;
    if (j == 'j')
    {
        ifstream csvread;
        csvread.open("ExportZielanalyse.csv", ios::in);
        if (!csvread.is_open())
            cerr << "Fehler beim Lesen!" << endl;
        else
        {
            string name, age, postcode, income;

            while (!csvread.eof())
            {
                getline(csvread, name, ';');
                getline(csvread, age, ';');
                getline(csvread, income, ';');
                getline(csvread, postcode, '\n');
                ref->addNode(name, stoi(age), stod(income), stoi(postcode));
            }
            csvread.close();
        }
        cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
    }
}
//
///////////////////////////////////////
int main()
{

    int result = Catch::Session().run();

    ///////////////////////////////////////
    // Ihr Code hier:
    Tree* Tr = new Tree();
    int wahl, Alter, plz, ID, Niv;
    char ant;
    string Name;
    double Income;
    do {
        cout << "========================================\n";
        cout << " ADS Praktikum.3, by Fachrial Dimas\n";
        cout << "========================================\n";
        cout << "1) Datensatz einfuegen, manuell\n"
            << "2) Datensatz einfuegen, CSV Datei\n"
            << "3) Suchen\n"
            << "4) Ausgabe in Preorder\n"
            << "5) Ausgabe in Levelorder\n"
            << "6) Ausgabe in Levelorder (mit Niveauauswahl)\n"
            << "7) Beenden\n"
            << "?> ";
        cin >> wahl;
        if (wahl == 1) {
            cin.ignore();
            cout << "+ Bitte geben Sie die den Datensatz ein:\n"
                << "Name ?> ";
            getline(cin, Name);
            cout << "Alter ?>";
            cin >> Alter;
            cout << "Einkommen ?>";
            cin >> Income;
            cout << "PLZ ? >";
            cin >> plz;
            Tr->addNode(Name, Alter, Income, plz);
            cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
        }
        else if (wahl == 2) {
            mainscreen_addTreeCSV(Tr);
        }
        else if (wahl == 3) {
            cin.ignore();
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << " Name ?> ";
            getline(cin, Name);
            Tr->searchNode(Name);
        }
        else if (wahl == 4) {
            Tr->printAll();
        }
        else if (wahl == 5) {
            cout << "Ausgabe in Levelorder als binärer Suchbaum :\n\n";
            Tr->printLvlOrder();
            cout << "Ausgabe in Level order als 234-Baum:\n";
            Tr->printLevelOrder();
        }
        else if (wahl == 6) {
            cin.ignore();
            cout << "+ Bitte geben Sie das auszudrückende Niveau an" << endl;
            cout << " Nieau ?>";
            cin >> Niv;
            Tr->printLevelOrder(Niv);
        }
            
    } while (wahl != 7);

    //
    ///////////////////////////////////////
    system("PAUSE");

    return 0;
}
