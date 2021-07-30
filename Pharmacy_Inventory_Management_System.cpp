#include <fstream>
#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

class MedicineData{
public:
    int medicineId;
    string medicineName;
    string medicineType;
    string medicineCompany;
    string arrivalDate;
    string expiryDate;
    int medicineQuantity;
    int medicinePrice;

    int getId(){
        return medicineId;
    }

    void add(){
        cout << "Enter Medicine ID: ";
        cin >> medicineId;
        cin.ignore();

        cout << "Enter Medicine Name: ";
        getline(cin, medicineName);

        cout << "Enter Medicine Company: ";
        getline(cin, medicineCompany);

        cout << "Enter Arrival Date: ";
        getline(cin, arrivalDate);

        cout << "Enter Expiry Date: ";
        getline(cin, expiryDate);

        cout << "Enter the Type of Medicine: ";
        getline(cin, medicineType);

        cout << "Enter Quantity: ";
        cin >> medicineQuantity;

        cout << "Enter Price: ";
        cin >> medicinePrice;
    }

    void addMedicineQuantity(){
        cout << "Please enter the total Quantity: ";
        cin >> medicineQuantity;
    }

    void removeMedicineQuantity(){
        cout << "Please enter the Quantity after removal: ";
        cin >> medicineQuantity;
    }

    void inventory(){
        cout << "| " << setw(9) << medicineId << " "
             << "| " << setw(12) << medicineName << " "
             << "| " << setw(12) << medicineCompany << " "
             << "| " << setw(16) << arrivalDate << " "
             << "| " << setw(15) << expiryDate << " "
             << "| " << setw(8) << medicineType << " "
             << "| " << setw(12) << medicineQuantity << " "
             << "| " << setw(9) << medicinePrice << " |" << endl;
    }
}ph;

void addMedicineToInventory(){
    ofstream phWrite;
    phWrite.open("Pharmacy.txt", ios::out|ios::binary|ios::app);
    ph.add();
    phWrite.write((char*)&ph, sizeof(ph));
    phWrite.close();
    cout << endl << "MEDICINE ADDED TO INVENTORY SUCCESSFULLY" << endl;

    cout << endl << "Press any key to continue...";
    getch();
    system("CLS");
}

void addMedicineStock(int ch){
    fstream io;
    int flag = 0, pos;
    io.open("Pharmacy.txt", ios::in|ios::binary|ios::out);

    while(io.read((char*)&ph,sizeof(ph))){
        pos = io.tellg();
        if(ch == ph.getId()){
            flag++;
            ph.addMedicineQuantity();
            io.seekg(pos - sizeof(ph));
            io.write((char*)&ph,sizeof(ph));
            cout << "DATA MODIFIED SUCCESSFULLLY" << endl;
        }
    }
    io.close();
    if(flag==0)
        cout << "MEDICINE NOT FOUND" << endl;

    cout << endl << "Press any key to continue...";
    getch();
    system("CLS");
}

void issueMedicineStock(int ch){
    fstream io;
    int flag, pos;
    io.open("Pharmacy.txt", ios::in|ios::binary|ios::out);

    while(io.read((char*)&ph,sizeof(ph))){
        pos = io.tellg();
        if(ch == ph.getId()){
            flag++;
            ph.removeMedicineQuantity();
            io.seekg(pos - sizeof(ph));
            io.write((char*)&ph,sizeof(ph));
            cout << "DATA MODIFIED SUCCESSFULLY" << endl;
        }
    }
    io.close();
    if(flag==0)
        cout << "MEDICINE NOT FOUND" << endl;

    cout << endl << "Press any key to continue...";
    getch();
    system("CLS");
}

void viewInventory(){
    ifstream phRead;

    cout << "+-----------+--------------+--------------+------------------+-----------------+----------+--------------+-----------+" << endl;
    cout << "| ID        | Name         | Company      | Arrival Date     | Expiry Date     | Type     | Quantity     | Price     |" << endl;
    cout << "+-----------+--------------+--------------+------------------+-----------------+----------+--------------+-----------+" << endl;

    phRead.open("Pharmacy.txt", ios::out|ios::binary|ios::app);
    while(phRead.read((char*)&ph, sizeof(ph))){
        ph.inventory();
    }
    cout << "+-----------+--------------+--------------+------------------+-----------------+----------+--------------+-----------+" << endl;
    phRead.close();

    cout << "Press any key to continue...";
    getch();
    system("CLS");
}

void editMedicineData(int ch){
    fstream io;
    int flag, pos;
    io.open("Pharmacy.txt", ios::in|ios::binary|ios::out);

    while(io.read((char*)&ph,sizeof(ph))){
        pos = io.tellg();
        if(ch == ph.getId()){
            flag++;
            cout << "Enter New Details: " << endl;
            ph.add();
            io.seekg(pos - sizeof(ph));
            io.write((char*)&ph,sizeof(ph));
            cout << "\nDATA MODIFIED SUCCESSFULLY" << endl;
        }
    }
    io.close();
    if(flag==0)
        cout << "MEDICINE NOT FOUND" << endl;

    cout << "Press any key to continue...";
    getch();
    system("CLS");
}

void removeMedicineFromInventory(int ch){
    ifstream phRead;
    ofstream phWrite;
    int flag=0;
    phRead.open("Pharmacy.txt", ios::out|ios::binary|ios::app);
    phWrite.open("temp.txt", ios::out|ios::binary);

    while(phRead.read((char*)&ph, sizeof(ph))){
        if(ch == ph.getId()){
            flag++;
            cout << "RECORD DELETED SUCCESSFULLY" << endl;
        }
        else{
            phWrite.write((char*)&ph, sizeof(ph));
        }
    }
    phRead.close();
    phWrite.close();
    if(flag==0){
        cout << "MEDICINE NOT FOUND" << endl;
    }

    remove("Pharmacy.txt");
    rename("temp.txt", "Pharmacy.txt");

    cout << "Press any key to continue...";
    getch();
    system("CLS");
}

int main() {
    while(true){

        cout << "       Pharmacy Inventory Management System " << endl;
		cout << "==================================================" << endl << endl;
		cout << "--------------------------------------------------" << endl;
        cout << "||        1. Add Medicine to Inventory          ||" << endl;
        cout << "||        2. Add Medicine Stock                 ||" << endl;
        cout << "||        3. Issue Medicine Stock               ||" << endl;
        cout << "||        4. View Inventory                     ||" << endl;
        cout << "||        5. Edit Medicine Data                 ||" << endl;
        cout << "||        6. Remove Medicine From Inventory     ||" << endl;
        cout << "||        0. Exit                               ||" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Enter choice: ";

        int choice,x;
        cin >> choice;

        switch(choice){
            case 1:
                addMedicineToInventory();
                break;
            case 2:
                    cout << "Enter the Id of the Medicine: ";
                    cin >> x;
                    addMedicineStock(x);
                break;
            case 3:
                    cout << "Enter the Id of the Medicine: ";
                    cin >> x;
                    issueMedicineStock(x);
                break;
            case 4: viewInventory();
                break;
            case 5:
                    cout << "Enter the Id of the Medicine: ";
                    cin >> x;
                    editMedicineData(x);
                break;
            case 6:
                    cout << "Enter the Id of the Medicine: ";
                    cin >> x;
                    removeMedicineFromInventory(x);
                    break;
            case 0: exit(0);
        }
    }
    return 0;
}
