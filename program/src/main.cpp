#include <iostream>
#include "typedefs.h"
#include "model/ClientType.h"
#include "model/Client.h"
#include "model/TyreRepair.h"
#include "model/Service.h"
#include "managers/ClientManager.h"
#include "managers/ServiceManager.h"
#include "repositories/ServiceRepository.h"
#include "repositories/ClientRepository.h"
#include "model/TimingChainRepair.h"
#include "model/OilChange.h"
#include <fstream>

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

using namespace std;

void readFileAndPrint(const std::string& filePath) {
    std::ifstream inputFile(filePath);

    if (!inputFile) {
        std::cerr << "Nie mozna otworzyc pliku: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }

    inputFile.close();
}

void clearFile(const std::string& filePath) {
    std::ofstream outputFile(filePath, std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Nie mozna otworzyc pliku: " << filePath << std::endl;
    }
    outputFile.close();
}

int main()
{
    clearFile("../../dysk/clients");
    clearFile("../../dysk/clients_archive");
    clearFile("../../dysk/services");
    clearFile("../../dysk/services_archive");

   char wybor_postaci;
   char pracownik_akcja;
   char klient_akcja;
   ClientManager manager;
   ServiceManager manager_naprawy;
   ClientTypePtr test1 = std::make_shared<Default>();
   cout << "Witaj w warsztacie samochodowym!" << endl;
   do {
       cout << "Kim jestes? - wybuerz odpowiedni numer" << endl << "1 - pracownik warsztatu" << endl << "2 - klient"
            << endl << "3 -Zakoncz program" << endl;
       cin >> wybor_postaci;

       switch (wybor_postaci) {
           case '1': {
               do {
                   cout << "Wybierz co chcesz zrobic:" << endl << "1 - wczytaj dane z aktualnej bazy klientow" << endl
                        << "2 - wczytaj dane z archiwum klientow" << endl << "3 - wczytaj dane z aktualnej bazy uslug"
                        << endl << "4 - wczytaj dane z arciwum uslug" << endl << "5 - zmien komus typ klienta " << endl
                        << "6 - powrot" << endl;
                   cin >> pracownik_akcja;
                   switch (pracownik_akcja) {
                       case '1':
                           readFileAndPrint("../../dysk/clients");
                           break;
                       case '2':
                           readFileAndPrint("../../dysk/clients_archive");
                           break;
                       case '3':
                           readFileAndPrint("../../dysk/services");
                           break;
                       case '4':
                           readFileAndPrint("../../dysk/services_archive");
                           break;
                       case '5': {
                           int identyfikator;
                           cout << "Podaj id klienta: ";
                           cin >> identyfikator;
                           ClientPtr zmiana = manager.getClient(identyfikator);
                           char typek;
                           cout << "Wybierz jaki typ klienta chcesz ustawic: " << endl << "1 - default" << "2 - silver"
                                << "3 - gold" << "4 - platinum" << endl;
                           cin >> typek;
                           switch (typek) {
                               case '1': {
                                   ClientTypePtr typ1 = std::make_shared<Default>();
                                   zmiana->setClientType(typ1);
                               }
                                   break;
                               case '2': {
                                   ClientTypePtr typ2 = std::make_shared<Silver>();
                                   zmiana->setClientType(typ2);
                               }
                                   break;
                               case '3': {
                                   ClientTypePtr typ3 = std::make_shared<Gold>();
                                   zmiana->setClientType(typ3);
                               }
                               case '4': {
                                   ClientTypePtr typ4 = std::make_shared<Platinum>();
                                   zmiana->setClientType(typ4);
                               }
                               default: {
                                   cout << endl;
                               }
                                   break;
                           }
                       }
                           break;
                       default:
                           cout << endl;
                           break;
                   }
               } while (pracownik_akcja != '6');
           }
               break;

           case '2': {

               do {
                   cout << "Wybierz co chcesz zrobic:" << endl << "1 - zarejestruj sie w naszym warsztacie" << endl
                        << "2 - wyrejestruj sie z naszego warsztatu" << endl << "3 - oddaj auto do naprawy" << endl
                        << "4 - powrot" << endl;
                   cin >> klient_akcja;
                   switch (klient_akcja) {
                       case '1': {
                           string imie, nazwisko;
                           int identyfikator;
                           cout << "Podaj swoje dane:" << endl;
                           cout << "Imie: ";
                           cin >> imie;
                           cout << "Nazwisko: ";
                           cin >> nazwisko;
                           cout << "Podaj swoje id (nr telefonu): ";
                           cin >> identyfikator;
                           ClientPtr nowy = manager.registerClient(imie, nazwisko, identyfikator, test1);
                       }
                           break;

                       case '2': {

                           int identyfikatorek;
                           cout << "Podaj swoje id (nr telefonu)" << endl;
                           cin >> identyfikatorek;
                           manager.unregisterClient(manager.getClient(identyfikatorek));
                           cout << "Dziekujemy za skorzystanie z uslug naszego warsztatu" << endl;
                       }
                           break;

                       case '3': {
                           int idd;
                           cout << "Podaj swoje id (nr telefonu)" << endl;
                           cin >> idd;
                           char naprawa;
                           cout << "Co chcesz naprawic?" << endl << "1 - zmiana opon" << endl << "2 - wymiana oleju"
                                << endl << "3 - wymiana paska rozrzadu" << endl;
                           cin >> naprawa;
                           switch (naprawa) {
                               case '1': {
                                   int rozmiar;
                                   cout << "Podaj rozmiar opon: ";
                                   cin >> rozmiar;
                                   RepairPtr oponki = std::make_shared<TyreRepair>(100.0, "zmiana_opon", 1, rozmiar);
                                   ServicePtr naprawa1 = manager_naprawy.registerService(idd,
                                                                                         pt::second_clock::local_time(),
                                                                                         manager.getClient(idd),
                                                                                         oponki);
                                   cout << "inofrmacje o twojej naprawie :" << naprawa1->getInfo();
                               }
                                   break;

                               case '2': {
                                   int wiek;
                                   cout << "Podaj rocznik samochodu: ";
                                   cin >> wiek;
                                   int olej;
                                   cout << "Podaj typ oleju: (wpisz: 1 - mineral, 2 - blended, 3 - synthetic) ";
                                   cin >> olej;
                                   auto olejEnum = static_cast<OilType>(olej);
                                   RepairPtr olejek = std::make_shared<OilChange>(100.0, "zmiana_oleju", 2, wiek,
                                                                                  olejEnum);
                                   ServicePtr naprawa2 = manager_naprawy.registerService(idd,
                                                                                         pt::second_clock::local_time(),
                                                                                         manager.getClient(idd),
                                                                                         olejek);
                                   cout << "inofrmacje o twojej naprawie :" << naprawa2->getInfo();
                               }
                                   break;

                               case '3': {
                                   int wiek;
                                   cout << "Podaj rocznik samochodu: ";
                                   cin >> wiek;
                                   RepairPtr pasek = std::make_shared<TimingChainRepair>(100.0, "zmiana_paska", 3,
                                                                                         wiek);

                                   ServicePtr naprawa3 = manager_naprawy.registerService(idd,
                                                                                         pt::second_clock::local_time(),
                                                                                         manager.getClient(idd), pasek);
                                   cout << "inofrmacje o twojej naprawie :" << naprawa3->getInfo();
                               }
                                   break;
                               default: {
                                   cout <<  endl;
                               }
                                   break;
                           }

                       }
                           break;

                       default: {
                           cout << endl;
                       }
                   }
               } while (klient_akcja != '4');
           }
               break;
           default: {
               cout << "Zegnaj! " << endl;
           }
       }
   }while (wybor_postaci!='3');
    return 0;
}