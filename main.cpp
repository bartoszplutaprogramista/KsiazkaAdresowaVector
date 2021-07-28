#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <stdio.h>

using namespace std;

struct User {
    int id, userIDUser;
    string name, surname, phoneNumber, eMail, address;
};

struct LoginPassword {
    int userID;
    string  login, password;
};

int splitDataToCheckWhetherIDRecipientInTextFileEqualsEditedIdOfRecipient(string helpToSplitData);

vector <LoginPassword> splitDataUsersData(vector <string> helpToLoad);

vector <LoginPassword> loadUsersDataFromFile();

void saveUsersDataToATextFile (vector <LoginPassword> loginAndPasswordVec, int numberOfLoggedUser);

int signIn (vector <LoginPassword> &loginAndPasswordVec);

void changePassword(vector <LoginPassword> &loginAndPasswordVec, int i);

void signUpLoginPassword (vector <LoginPassword> &loginAndPasswordVec);

vector <User> splitData(vector <string> helpToLoad, int numberOfLoggedUser);

int splitDataToCheckWhetherUserIDEqualsLoggedUserId(string helpToSplitData);

vector <User> loadDataFromFile(int numberOfLoggedUser);

int calculateID();

int saveAllData(vector <User> &recipients, int numberOfLoggedUser);

void displayData(vector <User> recipients, int i);

int searchByName (vector <User> recipients);

int searchBySurname (vector <User> recipients);

void displayAll(vector <User> recipients, int numberOfLoggedUser);

void saveDataToATextFile(vector <User> recipients);

void renameTxtFile();

void rewriteEditedDataAndFillInDataInTextFile(vector <User> recipients, int IdToEdit);

void saveNameToATextFile (vector <User> &recipients, int i, int enteredID);

void saveSurnameToATextFile (vector <User> &recipients, int i, int enteredID);

void savePhoneNumberToATextFile (vector <User> &recipients, int i, int enteredID);

void saveeMailToATextFile (vector <User> &recipients, int i, int enteredID);

void saveAddressToATextFile (vector <User> &recipients, int i, int enteredID);

int editRecipient(vector <User> &recipients, int numberOfLoggedUser);

void rewriteFileAfterRemoving(int IdToEdit);

void rewriteDataAfterRemovingRecipient(vector <User> recipients, int IdToEdit);

int removeRecipient(vector <User> &recipients, int numberOfLoggedUser);

int main() {
    vector <LoginPassword> loginAndPasswordVec;
    vector <User> recipients;
    char choice;
    int enteredID = 0;

    loginAndPasswordVec = loadUsersDataFromFile();

    while(1) {
        system("cls");
        cout << "MENU GLOWNE" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin >> choice;

        if(choice == '1') {
            enteredID = signIn(loginAndPasswordVec);
        } else if (choice == '2') {
            signUpLoginPassword(loginAndPasswordVec);
        } else if (choice == '3') {
            exit(0);
        }
    }
    return 0;
}

int splitDataToCheckWhetherIDRecipientInTextFileEqualsEditedIdOfRecipient(string helpToSplitData) {
        int helpToCheck = 0;
        string result = "";
        int i = 0;
        string textToSeparate = helpToSplitData;
        int textLength = textToSeparate.length();
        int numberOfOccurrences = 0;
        while (textLength>0) {
            while (textToSeparate[i] != '|') {
                result += textToSeparate[i];
                i++;
            }
            numberOfOccurrences++;
            if (numberOfOccurrences == 1) {
                helpToCheck = atoi(result.c_str());
                return helpToCheck;
            }
            textToSeparate.erase(0,i+1);
            textLength = textToSeparate.length();
            i=0;
            result = "";
        }
    return helpToCheck;
}

vector <LoginPassword> splitDataUsersData(vector <string> helpToLoad) {
    int sizeOfVector = helpToLoad.size();
    vector <LoginPassword> helpToSeparate;
    for (int j=0; j<sizeOfVector; j++) {
        string result = "";
        string textToSeparate = helpToLoad[j];
        LoginPassword dataOfUsers;
        int i=0;
        int textLength = textToSeparate.length();
        int numberOfOccurrences = 0;
        while (textLength>0) {
            while (textToSeparate[i] != '|') {
                result += textToSeparate[i];
                i++;
            }
            numberOfOccurrences++;
            if (numberOfOccurrences == 1) {
                dataOfUsers.userID = atoi(result.c_str());
            }else if (numberOfOccurrences == 2) {
                dataOfUsers.login = result;
            } else if (numberOfOccurrences == 3) {
                dataOfUsers.password = result;
            }
            textToSeparate.erase(0,i+1);
            textLength = textToSeparate.length();
            i=0;
            result = "";
        }
        helpToSeparate.push_back(dataOfUsers);
    }

    return helpToSeparate;
}

vector <LoginPassword> loadUsersDataFromFile() {
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    vector <string> helpToLoad;
    vector <LoginPassword> separatedData;
    if (file.good()==true) {
        string line;
        int lineNumber=1;
        while(getline(file,line)) {
            helpToLoad.push_back(line);
            lineNumber++;
        }
        file.close();

        separatedData = splitDataUsersData(helpToLoad);
    }

    return separatedData;
}

void saveUsersDataToATextFile (vector <LoginPassword> loginAndPasswordVec, int numberOfLoggedUser){

    ofstream file;
    int sizeOfLoginAndPasswordVec = loginAndPasswordVec.size();
    file.open("Uzytkownicy.txt");
    file.close();

    file.open("Uzytkownicy.txt", ios::out | ios::app);

    if (file.good() == true) {
        for (int j=0; j<sizeOfLoginAndPasswordVec; j++) {
            file<<loginAndPasswordVec[j].userID<<"|";
            file<<loginAndPasswordVec[j].login<<"|";
            file<<loginAndPasswordVec[j].password<<"|"<<endl;
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        getch();
    }

    file.close();
}

int signIn (vector <LoginPassword> &loginAndPasswordVec){
    int x=0;
    int enteredID = 0;
    while (x<loginAndPasswordVec.size()){
        cout << loginAndPasswordVec[x].login << endl;
        x++;
    }
    string login;
    string password;
    cout << "Wprowadz login: " << endl;
    cin >> login;
    cout << "Wprowadz haslo: " << endl;
    cin >> password;
    int i=0;
    int rozmiar = loginAndPasswordVec.size();
    while (i<rozmiar){
        if ((login == loginAndPasswordVec[i].login) && (password == loginAndPasswordVec[i].password)){
            cout << "Istnieje uzytkownik o takim loginie i hasle. Zalogowano pomyslnie!" << endl;
            getch();
            vector <User> recipients;
            int numberOfLoggedUser = i+1;
            recipients = loadDataFromFile(numberOfLoggedUser);
            while(1) {
                char choice;
                system("cls");
                cout << "1. Dodaj adresata" << endl;
                cout << "2. Wyszukaj po imieniu" << endl;
                cout << "3. Wyszukaj po nazwisku" << endl;
                cout << "4. Wyswietl wszystkich adresatow" << endl;
                cout << "5. Usun adresata" << endl;
                cout << "6. Edytuj adresata" << endl;
                cout << "7. Zmien haslo" << endl;
                cout << "9. Wyloguj sie" << endl;

                cin >> choice;

                if(choice == '1') {
                    saveAllData(recipients, numberOfLoggedUser);
                } else if (choice == '2') {
                    searchByName(recipients);
                } else if (choice == '3') {
                    searchBySurname(recipients);
                } else if (choice == '4') {
                    displayAll(recipients, numberOfLoggedUser);
                } else if (choice == '5') {
                    removeRecipient(recipients, numberOfLoggedUser);
                } else if (choice == '6') {
                    enteredID = editRecipient(recipients, numberOfLoggedUser);
                } else if (choice == '7') {
                    changePassword(loginAndPasswordVec, i);
                } else if (choice == '9') {
                    cout << "Wylogowales sie" << endl;
                    getch();
                    return 0;
                }
            }
        }else if((login != loginAndPasswordVec[i].login) && (password != loginAndPasswordVec[i].password) && (i == rozmiar-1)){
            cout << "Nieprawidlowy login lub haslo" << endl;
            getch();
            signIn(loginAndPasswordVec);
            i++;
        }
        i++;
    }
    return enteredID;
}

void changePassword(vector <LoginPassword> &loginAndPasswordVec, int i){
    string password;
    cout << "Wprowadz nowe haslo: " << endl;
    cin >> password;
    loginAndPasswordVec[i].password = password;
    cout << "Haslo zmieniono pomyslnie!" << endl;
    saveUsersDataToATextFile (loginAndPasswordVec, i+1);
    getch();
}

void signUpLoginPassword (vector <LoginPassword> &loginAndPasswordVec){
        int numberOfLoggedUser = 0;
        LoginPassword dataOfUsers;
        int sizeOfLoginAndPasswordVec = loginAndPasswordVec.size();
        cout << "1. Podaj login: " << endl;
        cin >> dataOfUsers.login;

        int i=0;
        while (i<sizeOfLoginAndPasswordVec){
            while (dataOfUsers.login==loginAndPasswordVec[i].login){
            cout << "Taki login juz istnieje wybierz inny!" << endl;
            cout << "1. Podaj login: " << endl;
            cin >> dataOfUsers.login;
            }
            i++;
        }
        cout << "2. Podaj haslo: " << endl;
        cin >> dataOfUsers.password;
        dataOfUsers.userID = sizeOfLoginAndPasswordVec + 1;
        getch();
        if (sizeOfLoginAndPasswordVec==0){
            numberOfLoggedUser = 1;
            loginAndPasswordVec.push_back(dataOfUsers);
            sizeOfLoginAndPasswordVec = loginAndPasswordVec.size();
            saveUsersDataToATextFile(loginAndPasswordVec, numberOfLoggedUser);
        }
        else {
            i=0;
            while (i<sizeOfLoginAndPasswordVec){
                if ((dataOfUsers.login!=loginAndPasswordVec[i].login)&&(i==sizeOfLoginAndPasswordVec-1)){
                    loginAndPasswordVec.push_back(dataOfUsers);
                    numberOfLoggedUser++;
                    saveUsersDataToATextFile(loginAndPasswordVec, numberOfLoggedUser);
                }
                i++;
            }
        }
}

vector <User> splitData(vector <string> helpToLoad, int numberOfLoggedUser) {
    int sizeOfVector = helpToLoad.size();
    vector <User> helpToSeparate;
    for (int j=0; j<sizeOfVector; j++) {
        string result = "";
        string textToSeparate = helpToLoad[j];
        User friends;
        int i=0;
        int textLength = textToSeparate.length();
        int numberOfOccurrences = 0;
        while (textLength>0) {
            while (textToSeparate[i] != '|') {
                result += textToSeparate[i];
                i++;
            }
            numberOfOccurrences++;
            if (numberOfOccurrences == 1) {
                friends.id = atoi(result.c_str());
            }else if (numberOfOccurrences == 2) {
                friends.userIDUser = atoi(result.c_str());
            } else if (numberOfOccurrences == 3) {
                friends.name = result;
            } else if (numberOfOccurrences == 4) {
                friends.surname = result;
            } else if (numberOfOccurrences == 5) {
                friends.phoneNumber = result;
            } else if (numberOfOccurrences == 6) {
                friends.eMail = result;
            } else if (numberOfOccurrences == 7) {
                friends.address = result;
            }
            textToSeparate.erase(0,i+1);
            textLength = textToSeparate.length();
            i=0;
            result = "";
        }
        helpToSeparate.push_back(friends);
    }
    return helpToSeparate;
}

int splitDataToCheckWhetherUserIDEqualsLoggedUserId(string helpToSplitData) {
        int helpToCheck = 0;
        string result = "";
        int i = 0;
        string textToSeparate = helpToSplitData;
        int textLength = textToSeparate.length();
        int numberOfOccurrences = 0;
        while (textLength>0) {
            while (textToSeparate[i] != '|') {
                result += textToSeparate[i];
                i++;
            }
            numberOfOccurrences++;
            if (numberOfOccurrences == 2) {
                helpToCheck = atoi(result.c_str());
                return helpToCheck;
            }
            textToSeparate.erase(0,i+1);
            textLength = textToSeparate.length();
            i=0;
            result = "";
        }
    return helpToCheck;
}

vector <User> loadDataFromFile(int numberOfLoggedUser) {
    User friends;
    fstream file;
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::in);
    vector <string> helpToLoad;
    vector <User> separatedData;
    int helpToCheck = 0;

    if (file.good()==true) {
        string helpToSplitData;
        string line;
        int lineNumber=1;
        while(getline(file,line)) {
            helpToSplitData = line;
            helpToCheck = splitDataToCheckWhetherUserIDEqualsLoggedUserId(helpToSplitData);
            if(helpToCheck==numberOfLoggedUser) {
                helpToLoad.push_back(line);
            }
            lineNumber++;
        }
        separatedData = splitData(helpToLoad, numberOfLoggedUser);
    }
    else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        getch();
    }
    file.close();
    return separatedData;
}

int calculateID(){
    int helpToID = 0;
    fstream file;
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::in);
    int helpToRewrite = 0;

        if (file.good()==true) {
            string helpToSplitData;
            string line;
            while(getline(file,line)) {
                helpToSplitData = line;
                helpToRewrite = splitDataToCheckWhetherIDRecipientInTextFileEqualsEditedIdOfRecipient(helpToSplitData);
                if (helpToRewrite>helpToID){
                    helpToID = helpToRewrite;
                }
            }
        } else {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            getch();
        }
    file.close();
    return helpToID;
}

int saveAllData(vector <User> &recipients, int numberOfLoggedUser) {
    User friends;
    string name, surname, eMail, address, phoneNumber;
    cout << "Podaj imie: ";
    cin >> name;
    cout << "Podaj nazwisko: ";
    cin >> surname;
    cout << "Podaj numerTelefonu: ";
    cin >> phoneNumber;
    cout << "Podaj e-mail: ";
    cin >> eMail;
    cin.clear();
    cin.sync();
    cout << "Podaj adres: ";
    getline(cin, address);

    int sizeOfVector = recipients.size();
    if (!(ifstream("ksiazkaAdresowaPrzyjaciol.txt"))){
        friends.id = 1;
    } else {
        friends.id = calculateID()+1;
    }
    friends.userIDUser = numberOfLoggedUser;
    friends.name = name;
    friends.surname = surname;
    friends.phoneNumber = phoneNumber;
    friends.eMail = eMail;
    friends.address = address;

    recipients.push_back(friends);

    fstream file;
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::out | ios::app);

        if (file.good() == true) {
            file<<recipients[sizeOfVector].id<<"|";
            file<<recipients[sizeOfVector].userIDUser<<"|";
            file<<recipients[sizeOfVector].name<<"|";
            file<<recipients[sizeOfVector].surname<<"|";
            file<<recipients[sizeOfVector].phoneNumber<<"|";
            file<<recipients[sizeOfVector].eMail<<"|";
            file<<recipients[sizeOfVector].address<<"|"<<endl;
        } else {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            getch();
            }
    cout << "Przyjaciel zapisany" << endl;
    Sleep(1000);
    return sizeOfVector;
}

void displayData(vector <User> recipients, int i) {
    cout << "ID: "<< recipients[i].id << endl;
    cout << "ID UZYTKOWNIKA: "<< recipients[i].userIDUser << endl;
    cout << "Imie: "<< recipients[i].name << endl;
    cout << "Nazwisko: "<< recipients[i].surname << endl;
    cout << "Numer Telefonu: "<< recipients[i].phoneNumber << endl;
    cout << "E-mail: "<< recipients[i].eMail << endl;
    cout << "Adres: "<< recipients[i].address << endl;
}

int searchByName (vector <User> recipients) {
    string name;
    int sizeOfVector = recipients.size();

    while (true) {
        system("cls");
        int howManyPeopleDoNotMeetTheCondition = 0;

        cout << "Podaj imie: ";
        cin >> name;

        int i=0;

        while (i<sizeOfVector) {

            if (recipients[i].name == name) {
                cout << "Wyszukiwanie po imionach: Uzytkownik o imieniu: ";
                cout << name << endl << "Dane uzytkownika: " << endl;
                displayData(recipients, i);
                i++;
            } else {
                howManyPeopleDoNotMeetTheCondition++;
                i++;
                if (howManyPeopleDoNotMeetTheCondition==sizeOfVector)
                    cout << "Nie ma przyjaciela o takim imieniu!";
            }
        }
        getch();
        return 0;
    }
}

int searchBySurname (vector <User> recipients) {
    string surname;
    int sizeOfVector = recipients.size();

    while (true) {
        system("cls");
        int howManyPeopleDoNotMeetTheCondition = 0;

        cout << "Podaj nazwisko: ";
        cin >> surname;

        int i=0;

        while (i<sizeOfVector) {
            if (recipients[i].surname == surname) {
                cout << "Wyszukiwanie po nazwiskach: Uzytkownik o nazwisku: ";
                cout << surname << endl << "Dane uzytkownika: " << endl;
                displayData(recipients, i);
                i++;
            } else {
                howManyPeopleDoNotMeetTheCondition++;
                i++;
                if (howManyPeopleDoNotMeetTheCondition==sizeOfVector)
                    cout << "Nie ma przyjaciela o takim nazwisku!";
            }
        }
        getch();
        return 0;
    }
}

void displayAll(vector <User> recipients, int numberOfLoggedUser) {
    system("cls");
    int sizeOfVector = recipients.size();
    int i=0;
    while (i<sizeOfVector) {
        if (recipients[i].userIDUser == numberOfLoggedUser){
            cout << "Dane przyjaciela: " << endl;
            displayData(recipients, i);
            cout << endl;
        }
        i++;
    }
    getch();
}

void deleteTxtFile(){
    char path[] = "ksiazkaAdresowaPrzyjaciol.txt";
    int remove(const char *path);
    if( remove( path ) == -1 ){
      cout << "Could not delete " << path;
      getch();
    } else {
        cout << "Deleted " << path << endl;
        getch();
    }
}

void renameTxtFile(){
    int result;
    char oldname[] = "ksiazkaAdresowaPrzyjaciol_tymczasowy.txt", newname[] = "ksiazkaAdresowaPrzyjaciol.txt";
    result = rename(oldname, newname);
    if( result != 0 ){
      cout << "Could not rename" << oldname << endl;
      getch();
    }else {
      cout << "File " << oldname << " renamed " << newname << endl;
      getch();
    }
}

void rewriteEditedDataAndFillInDataInTextFile(vector <User> recipients, int IdToEdit){
    fstream file;
    ofstream file_temporary;
    file_temporary.open("ksiazkaAdresowaPrzyjaciol_tymczasowy.txt");
    file_temporary.close();
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::in);
    file_temporary.open("ksiazkaAdresowaPrzyjaciol_tymczasowy.txt", ios::out | ios::app);
    int helpToRewrite = 0;

        if (file.good()==true) {
            string helpToSplitData;
            string line;
            int helpToCheck = 0;
            int numberOfIDLastLine = 0;
            int howManyTimes=0;
            while(getline(file,line)) {
                helpToSplitData = line;
                helpToRewrite = splitDataToCheckWhetherIDRecipientInTextFileEqualsEditedIdOfRecipient(helpToSplitData);
                helpToCheck = splitDataToCheckWhetherUserIDEqualsLoggedUserId(helpToSplitData);
                numberOfIDLastLine = calculateID();
                if(helpToRewrite!=IdToEdit) {
                    if (file_temporary.good() == true) {
                            file_temporary << helpToSplitData << endl;
                        } else {
                        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                        getch();
                        }
                }else{
                    if (file_temporary.good() == true){
                        file_temporary <<recipients[howManyTimes].id <<"|";
                        file_temporary << recipients[howManyTimes].userIDUser <<"|";
                        file_temporary << recipients[howManyTimes].name <<"|";
                        file_temporary << recipients[howManyTimes].surname <<"|";
                        file_temporary << recipients[howManyTimes].phoneNumber <<"|";
                        file_temporary << recipients[howManyTimes].eMail <<"|";
                        file_temporary << recipients[howManyTimes].address <<"|"<<endl;
                    }else {
                        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                        getch();
                    }
                }
                if (helpToCheck == recipients[0].userIDUser){
                    howManyTimes++;
                }
            }
        }else {
            cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
            getch();
            }
            file_temporary.close();
            file.close();

    deleteTxtFile();
    renameTxtFile();
}

void saveNameToATextFile (vector <User> &recipients, int i, int enteredID) {
    string name;
    User friends;

    cout << "Wprowadz imie: ";
    cin >> name;
    friends.name = name;

    friends.id = enteredID;
    friends.userIDUser = recipients[i].userIDUser;
    friends.surname = recipients[i].surname;
    friends.phoneNumber = recipients[i].phoneNumber;
    friends.eMail = recipients[i].eMail;
    friends.address = recipients[i].address;

    recipients[i] = friends;
    rewriteEditedDataAndFillInDataInTextFile(recipients, enteredID);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

void saveSurnameToATextFile (vector <User> &recipients, int i, int enteredID) {
    string surname;
    User friends;

    cout << "Wprowadz nazwisko: ";
    cin >> surname;
    friends.surname = surname;

    friends.id = enteredID;
    friends.userIDUser = recipients[i].userIDUser;
    friends.name = recipients[i].name;
    friends.phoneNumber = recipients[i].phoneNumber;
    friends.eMail = recipients[i].eMail;
    friends.address = recipients[i].address;

    recipients[i] = friends;
    rewriteEditedDataAndFillInDataInTextFile(recipients, enteredID);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

void savePhoneNumberToATextFile (vector <User> &recipients, int i, int enteredID) {
    string phoneNumber;
    User friends;

    cout << "Wprowadz numer Telefonu: ";
    cin >> phoneNumber;
    friends.phoneNumber = phoneNumber;

    friends.id = enteredID;
    friends.userIDUser = recipients[i].userIDUser;
    friends.name = recipients[i].name;
    friends.surname = recipients[i].surname;
    friends.eMail = recipients[i].eMail;
    friends.address = recipients[i].address;

    recipients[i] = friends;
    rewriteEditedDataAndFillInDataInTextFile(recipients, enteredID);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

void saveeMailToATextFile (vector <User> &recipients, int i, int enteredID) {
    string eMail;
    User friends;

    cout << "Wprowadz eMail: ";
    cin >> eMail;
    friends.eMail = eMail;

    friends.id = enteredID;
    friends.userIDUser = recipients[i].userIDUser;
    friends.name = recipients[i].name;
    friends.surname = recipients[i].surname;
    friends.phoneNumber = recipients[i].phoneNumber;
    friends.address = recipients[i].address;

    recipients[i] = friends;
    rewriteEditedDataAndFillInDataInTextFile(recipients, enteredID);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

void saveAddressToATextFile (vector <User> &recipients, int i, int enteredID) {
    string address;
    User friends;

    cin.clear();
    cin.sync();
    cout << "Wprowadz adres: ";
    getline(cin, address);

    friends.address = address;

    friends.id = enteredID;
    friends.userIDUser = recipients[i].userIDUser;
    friends.name = recipients[i].name;
    friends.surname = recipients[i].surname;
    friends.phoneNumber = recipients[i].phoneNumber;
    friends.eMail = recipients[i].eMail;

    recipients[i] = friends;
    rewriteEditedDataAndFillInDataInTextFile(recipients, enteredID);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

int editRecipient(vector <User> &recipients, int numberOfLoggedUser) {

    int enteredID = 0;
    int sizeOfVector = recipients.size();
    int howManyTimes = 1;
    cout << "Wprowadz ID istniejacego przyjaciela: " << endl;
    cin >> enteredID;

    string name, surname, eMail, address, phoneNumber;
    User friends;

    int i=0;
    while (i<sizeOfVector) {
        if ((enteredID == recipients[i].id)&&(recipients[i].userIDUser == numberOfLoggedUser)) {
            while (true) {
                system("cls");
                char choice;
                cout << "Edytuj Dane Przyjaciela" << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer telefonu" << endl;
                cout << "4. Email" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Powrot do menu" << endl;
                cin>>choice;

                if (choice == '1') {
                    saveNameToATextFile(recipients, i, enteredID);
                } else if (choice == '2') {
                    saveSurnameToATextFile(recipients, i, enteredID);
                } else if (choice == '3') {
                    savePhoneNumberToATextFile(recipients, i, enteredID);
                } else if (choice == '4') {
                    saveeMailToATextFile(recipients, i, enteredID);
                } else if (choice == '5') {
                    saveAddressToATextFile(recipients, i, enteredID);
                } else return 0;
            }
        } else if ((enteredID != recipients[i].id)&&((howManyTimes)==sizeOfVector)) {
            cout << "Nie ma na liscie przyjaciela o takim ID!" << endl;
            getch();
        }
        i++;
        howManyTimes++;
    }
    return enteredID;
}

void rewriteDataAfterRemovingRecipient(vector <User> recipients, int IdToEdit){
    fstream file;
    ofstream file_temporary;
    file_temporary.open("ksiazkaAdresowaPrzyjaciol_tymczasowy.txt");
    file_temporary.close();
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::in);
    file_temporary.open("ksiazkaAdresowaPrzyjaciol_tymczasowy.txt", ios::out | ios::app);
    int helpToRewrite = 0;

        if (file.good()==true) {
            string helpToSplitData;
            string line;
            int howManyTimes=0;
            int numberOfIDLastLine=0;
            while(getline(file,line)) {
                helpToSplitData = line;
                helpToRewrite = splitDataToCheckWhetherIDRecipientInTextFileEqualsEditedIdOfRecipient(helpToSplitData);
                numberOfIDLastLine = calculateID();
                if(helpToRewrite!=IdToEdit) {
                    if (file_temporary.good() == true) {
                            file_temporary << helpToSplitData<<endl;
                    } else {
                        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                        getch();
                    }
                }
            }
            file_temporary.close();
            file.close();
    }else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        getch();
    }
    deleteTxtFile();
    renameTxtFile();
}

int removeRecipient(vector <User> &recipients, int numberOfLoggedUser) {
    int enteredID = 0;
    int sizeOfVector = recipients.size();
    int howManyTimes = 1;
    int i=0;
    cout << "Wprowadz ID przyjaciela do skasowania: " << endl;
    cin >> enteredID;

    while (i<sizeOfVector) {
        if (enteredID == recipients[i].id) {
            recipients.erase(recipients.begin() + i);
            sizeOfVector = recipients.size();

            rewriteDataAfterRemovingRecipient(recipients, enteredID);

            cout << "Pomyslnie Skasowano Dane Przyjaciela!" << endl;
            Sleep(1000);
            return 0;
        } else if ((enteredID != recipients[i].id)&&((howManyTimes)==sizeOfVector)) {
            cout << "Nie ma na liscie przyjaciela o takim ID!" << endl;
            Sleep(1000);
        }
        howManyTimes++;
        i++;
    }
    return 0;
}
