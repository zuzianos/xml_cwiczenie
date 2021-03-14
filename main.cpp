#include <iostream>
#include <ctime>
#include <cstdio>
#include <clocale>
#include "Markup.h"

using namespace std;

string getDateFromUser();
string todaysDate();
string writeDate();
int getItem();

int main() {
    int userId = 1; // roboczo
    CMarkup xml;

    bool fileExists = xml.Load( "incomes.xml" );

    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("incomes");
    }
    int kowtaPrzychodu = 0;
    cout<<"podaj kwote przychodu:";
    cin>> kowtaPrzychodu;
    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("Income");
    xml.IntoElem();
    xml.AddElem("userId", userId);
    xml.AddElem("date", getDateFromUser());
    xml.AddElem("item", getItem());
    xml.AddElem("amount", kowtaPrzychodu);

    xml.Save("incomes.xml");


    return 0;
}

string getDateFromUser() {
    string date;
    char choice;

    system("cls");
    cout << "Wybierz date przychodu" << endl;
    cout << "---------------------------" << endl;
    cout << "1. dzisiaj" << endl;
    cout << "2. Wprowadz date recznie" << endl;

    cin>>choice;

    if(choice=='1') {
        date= todaysDate();
        cout<< "wprowadzono dzisiejsza date:"<< date;
        return date;
    } else if( choice=='2') {
        date= writeDate();
        return date;
    } else {
        cout << endl << "Nie ma takiej opcji w menu." << endl << endl;
        system("pause");
    }
}

string todaysDate() {
    char bufor[ 64 ];
    time_t czas;
    time(&czas);
    tm czasTM = *localtime(&czas);
    strftime( bufor, sizeof( bufor ), "%Y-%m-%d", & czasTM );
    return bufor;
}

string writeDate() {
    string date;
    cout<<"wprowadz Date rrrr-mm-dd:";
    cin>>date;
    return date;
}

int getItem() {
    int item= 0;
    CMarkup xml;
    bool fileExists = xml.Load( "incomes.xml" );
    if (!fileExists) {
        item=1;
    } else {
        xml.FindElem();
        xml.IntoElem();
        while ( xml.FindElem("Income") ) {
            xml.IntoElem();
            xml.FindElem("item");
            item = atoi( MCD_2PCSZ (xml.GetData() ) );
            xml.OutOfElem();
        }
    }
    return item+1;
}
