#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct User {
    int id, userIDUser;
    string name, surname, phoneNumber, eMail, address;
};

struct LoginPassword {
    int userID;
    string  login, password;
};

vector <LoginPassword> splitDataUsersData(vector <string> helpToLoad);

vector <LoginPassword> loadUsersDataFromFile();

void saveUsersDataToATextFile (vector <LoginPassword> loginAndPasswordVec, int extremeVariable);

int signIn (vector <User> &recipients, vector <LoginPassword> &loginAndPasswordVec);

//void signUpLoginPassword (vector <string> &login, vector <string> &password);

void changePassword(vector <LoginPassword> &loginAndPasswordVec, int i);

void signUpLoginPassword (vector <LoginPassword> &loginAndPasswordVec);

vector <User> splitData(vector <string> helpToLoad);

vector <User> loadDataFromFile();

int saveAllData(vector <User> &recipients, int extremeVariable);

void displayData(vector <User> recipients, int i);

int searchByName (vector <User> recipients);

int searchBySurname (vector <User> recipients);

void displayAll(vector <User> recipients);

void saveDataToATextFile(vector <User> recipients);

void saveNameToATextFile (vector <User> &recipients, int i, int enteredID);

void saveSurnameToATextFile (vector <User> &recipients, int i, int enteredID);

void savePhoneNumberToATextFile (vector <User> &recipients, int i, int enteredID);

void saveeMailToATextFile (vector <User> &recipients, int i, int enteredID);

void saveAddressToATextFile (vector <User> &recipients, int i, int enteredID);

int editRecipient(vector <User> &recipients);

int removeRecipient(vector <User> &recipients);

int main() {
    vector <LoginPassword> loginAndPasswordVec;
    vector <User> recipients;
    char choice;

    loginAndPasswordVec = loadUsersDataFromFile();

    recipients = loadDataFromFile();

    while(1) {
        system("cls");
        cout << "MENU GLOWNE" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin >> choice;

        if(choice == '1') {
            signIn(recipients, loginAndPasswordVec);
        } else if (choice == '2') {
//            signUpLoginPassword(login, password);
            signUpLoginPassword(loginAndPasswordVec);
        } else if (choice == '3') {
            exit(0);
        }
    }
    return 0;
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

void saveUsersDataToATextFile (vector <LoginPassword> loginAndPasswordVec, int extremeVariable){

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

int signIn (vector <User> &recipients, vector <LoginPassword> &loginAndPasswordVec){
    int x=0;
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
            int extremeVariable = i+1;
//            saveUsersDataToATextFile(loginAndPasswordVec, extremeVariable);
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
                    saveAllData(recipients, extremeVariable);
                } else if (choice == '2') {
                    searchByName(recipients);
                } else if (choice == '3') {
                    searchBySurname(recipients);
                } else if (choice == '4') {
                    displayAll(recipients);
                } else if (choice == '5') {
                    removeRecipient(recipients);
                } else if (choice == '6') {
                    editRecipient(recipients);
                } else if (choice == '7') {
                    changePassword(loginAndPasswordVec, i);
                } else if (choice == '9') {
                    cout << "Wylogowales sie" << endl;
                    getch();
                    return 1;
                }
            }
        }else if((login != loginAndPasswordVec[i].login) && (password != loginAndPasswordVec[i].password) && (i == rozmiar-1)){
            cout << "Nieprawidlowy login lub haslo" << endl;
            getch();
            signIn(recipients, loginAndPasswordVec);
            i++;
        }
        i++;
    }
    return 0;
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
//        string login;
//        string password;
        int extremeVariable = 0;
        LoginPassword dataOfUsers;
        int sizeOfLoginAndPasswordVec = loginAndPasswordVec.size();
        cout << "size login przed wejsciem: " << sizeOfLoginAndPasswordVec << endl;
        cout << "1. Podaj login: " << endl;
        cin >> dataOfUsers.login;

        int i=0;
        while (i<sizeOfLoginAndPasswordVec){
            while (dataOfUsers.login==loginAndPasswordVec[i].login){
            cout << "Taki login juz istnieje wybierz inny!" << endl;
//            signUpLoginPassword(loginAndPasswordVec);
            cout << "1. Podaj login: " << endl;
            cin >> dataOfUsers.login;
            }
            i++;
        }

//        dataOfUsers.login = login;

        cout << "2. Podaj haslo: " << endl;
        cin >> dataOfUsers.password;
//        dataOfUsers.password = password;
        dataOfUsers.userID = sizeOfLoginAndPasswordVec + 1;
        cout << "dataOfUsers wynosi: " << dataOfUsers.userID << endl;
        getch();
        if (sizeOfLoginAndPasswordVec==0){
            extremeVariable = 1;
            loginAndPasswordVec.push_back(dataOfUsers);
            sizeOfLoginAndPasswordVec = loginAndPasswordVec.size();
            cout << "Login z vectora wynosi: " << loginAndPasswordVec[0].login << endl;
            cout << "size login: " << sizeOfLoginAndPasswordVec << endl;
            saveUsersDataToATextFile(loginAndPasswordVec, extremeVariable);
        }
        else {
            cout << "WSZEDLEM DO TEGO ELSA" << endl;
            i=0;
            while (i<sizeOfLoginAndPasswordVec){
                if ((dataOfUsers.login!=loginAndPasswordVec[i].login)&&(i==sizeOfLoginAndPasswordVec-1)){
                    loginAndPasswordVec.push_back(dataOfUsers);
                    extremeVariable++;
                    saveUsersDataToATextFile(loginAndPasswordVec, extremeVariable);
                    cout << "Login z vectora po wejsciu do ifa wynosi: " << loginAndPasswordVec[1].login << endl;
                    getch();
                }
                i++;
            }
        }
        int j=0;
        int rozmiar = loginAndPasswordVec.size();
        if (rozmiar == 4){
            while (j<rozmiar){
                cout << "login " << j << " wynosi: " << loginAndPasswordVec[j].login << endl;
                cout << "haslo " << j << " wynosi: " << loginAndPasswordVec[j].password << endl;
                cout << "idUsera " << j << " wynosi: " << loginAndPasswordVec[j].userID << endl;
                j++;
            }
            getch();
        }
}

vector <User> splitData(vector <string> helpToLoad) {
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

vector <User> loadDataFromFile() {
    User friends;
    fstream file;
    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::in);
    vector <string> helpToLoad;
    vector <User> separatedData;
    if (file.good()==true) {
        string line;
        int lineNumber=1;
        while(getline(file,line)) {
            helpToLoad.push_back(line);
            lineNumber++;
        }
        file.close();

        separatedData = splitData(helpToLoad);
    }

    return separatedData;
}

int saveAllData(vector <User> &recipients, int extremeVariable) {
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
    if (sizeOfVector==0){
        friends.id = 1;
    } else {
        friends.id = recipients[sizeOfVector-1].id+1;
    }
    friends.userIDUser = extremeVariable;
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
        file.close();
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

void displayAll(vector <User> recipients) {
    system("cls");
    int sizeOfVector = recipients.size();
    for (int i=0; i<sizeOfVector; i++) {
        cout << "Dane przyjaciela: " << endl;
        displayData(recipients, i);
        cout << endl;
    }
    getch();
}

void saveDataToATextFile(vector <User> recipients) {

    ofstream file;
    int sizeOfVector = recipients.size();
    file.open("ksiazkaAdresowaPrzyjaciol.txt");
    file.close();

    file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::out | ios::app);

    if (file.good() == true) {
        for (int j=0; j<sizeOfVector; j++) {
            file<<recipients[j].id<<"|";
            file<<recipients[j].userIDUser<<"|";
            file<<recipients[j].name<<"|";
            file<<recipients[j].surname<<"|";
            file<<recipients[j].phoneNumber<<"|";
            file<<recipients[j].eMail<<"|";
            file<<recipients[j].address<<"|"<<endl;
        }
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        getch();
    }

    file.close();
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
    saveDataToATextFile(recipients);
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
    saveDataToATextFile(recipients);
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
    saveDataToATextFile(recipients);
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
    saveDataToATextFile(recipients);
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
    saveDataToATextFile(recipients);
    cout << "Pomyslnie Zmodyfikowano Dane Przyjaciela!" << endl;
    Sleep(1000);
}

int editRecipient(vector <User> &recipients) {

    int enteredID = 0;
    int sizeOfVector = recipients.size();
    int howManyTimes = 1;
    cout << "Wprowadz ID istniejacego przyjaciela: " << endl;
    cin >> enteredID;

    string name, surname, eMail, address, phoneNumber;
    User friends;

    int i=0;
    while (i<sizeOfVector) {
        if (enteredID == recipients[i].id) {
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
            Sleep(1000);
        }
        i++;
        howManyTimes++;
    }
    return 0;
}

int removeRecipient(vector <User> &recipients) {
    int enteredID = 0;
    int sizeOfVector = recipients.size();
    int howManyTimes = 1;
    int i=0;
    cout << "Wprowadz ID przyjaciela do skasowania: " << endl;
    cin >> enteredID;

    ofstream file;
    file.open("ksiazkaAdresowaPrzyjaciol.txt");
    file.close();

    while (i<sizeOfVector) {
        if (enteredID == recipients[i].id) {
            recipients.erase(recipients.begin() + i);
            sizeOfVector = recipients.size();
            file.open("ksiazkaAdresowaPrzyjaciol.txt", ios::out | ios::app);
            if (file.good() == true) {
                for (int j=0; j<sizeOfVector; j++) {
                    file<<recipients[j].id<<"|";
                    file<<recipients[j].userIDUser<<"|";
                    file<<recipients[j].name<<"|";
                    file<<recipients[j].surname<<"|";
                    file<<recipients[j].phoneNumber<<"|";
                    file<<recipients[j].eMail<<"|";
                    file<<recipients[j].address<<"|"<<endl;
                }
                file.close();
            } else {
                cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
                getch();
            }
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
