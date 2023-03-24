/*************************************************
* ADS Praktikum 2.1
* main.cpp
* 
*************************************************/
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <string>
#include "Ring.h"
#include "catch.h"

using namespace std;


int main()
{
	int result = Catch::Session().run();
	// Ihr Code hier:
	string eingabe , desc ;
	int wahl = 0;
	Ring Backup;
	
	do {
		cout << "========================================\n"
			<< "SuperBackUp-Organizer over 9000, by. Son Goku\n"
			<< "========================================\n"
			<< "0) Exit\n"
			<< "1) Backup anlegen\n"
			<< "2) Backup suchen\n"
			<< "3) Alle Backups ausgeben\n\n"
			<< "?>";
		
		cin >> wahl;
		if (wahl == 1) {
			cout << "+Neuen Datensatz anlegen\n";
			cout << "Beschreibung ?> ";
			cin.ignore();
			getline(cin, desc);
			cout << "Daten ?> ";
			getline(cin, eingabe);
			Backup.addNewNode(desc, eingabe);
			cout << "+Ihr Datensatz wurde hinzugefuegt.\n";
		}
		else if (wahl == 2) {
			cout << "+Nach welchen Daten soll gesucht werden?\n";
			cout << "?> ";
			cin.ignore();
			getline(cin, eingabe);
			Backup.search(eingabe);
		}
		else if (wahl == 3) {
			Backup.print();
			cout << endl;
		}
		else if(wahl<0||wahl>3){
			cout << "falsche Eingabe\n";
		}
	} while (wahl);
	


	//
	///////////////////////////////////////
	system("Pause");
	return 0;
}
