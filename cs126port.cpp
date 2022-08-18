#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

struct Medicine {
    string id;
    string name;
    string expiry_date;
};

int getdate(Medicine med){   
    string date_in_str;
    int date;
    for(int i = med.expiry_date.length() - 4; i < med.expiry_date.length(); i++){
        date_in_str.push_back(med.expiry_date[i]);
    }
    date = stoi(date_in_str);
    time_t tim = time(0);
    tm *year = localtime(&tim);
    return year->tm_year+1900 - date;
}

void check_expiry_date(){
    Medicine medicine[10];
    
    fstream file;
    file.open("medicineRecord.txt", ios::in);

    string en;
    char ch;
    int Cot = 0, counter = 0;

    if(file.is_open()){
        while(!file.eof()){
            file.get(ch);
            //input name and expiry date into array
            if(Cot == 0){
                medicine[counter].id.push_back(ch);
                Cot++;
            }else if(ch != ',' && ch != '.' && Cot == 1 && ch != '\n'){
                medicine[counter].name.push_back(ch);
            }else if(ch != ',' && Cot == 2 && ch != '\n'){
                medicine[counter].expiry_date.push_back(ch);
            } 
            //check for next line
            if(ch == '\n'){
                Cot = 0;
                counter++;
            }else if(ch == ','){
                Cot += 1;
            }
        }

        //loop out all medicine data in record
        for(int i = 0; i <= counter; i++){
            cout << "------------------------\n";
            cout << "Medicine " << medicine[i].id << ":" << endl; 
            cout << setw(12) << "Name: " << medicine[i].name << endl;
            cout << setw(12) << "Expiry Date: " << medicine[i].expiry_date << endl;

            if(getdate(medicine[i])>0){
                cout << setw(12) << "ALREADY EXPIRED!!!"<< endl;    
            }
        }
    }else{
        cout << "File is error" << endl;
    }

    file.close();
}

void add_medicine(){
    system("clear");
    string name,day,month,year;   
    fstream file;
    ifstream file1; //ifstream for count string - this is bad code but it work so it is what it is
    file.open("medicineRecord.txt",ios::app | ios::out);
    file1.open("medicineRecord.txt",ios::app | ios::out);

    if(file.is_open() && file1.is_open()){
        cout << "----Add medicine-----" << endl;
        cout << "Input Medicine name: ";
        cin >> name;
        cout << "Input expiry date: ";
        cout << "Day: ";
        cin >> day;
        cout << "Input expiry month: ";
        cin >> month;
        cout << "Input expiry year: ";
        cin >> year;

        int counter = 0;
        string line;
        while(getline(file1,line)){
            counter = counter + 1;
        }
        string id = to_string(counter+1);
        file << "\n" << id << "." <<name << "," << day << " " << month << " " << year << ",";
        file1.close();
        file.close();
    }else{
        cout << "Error!!" << endl;
    }
}

void delete_medicine(){
    system("clear");
    fstream file,temporaryFile;
    string medicineId;
    Medicine medicine[10];
    string en;
    char ch;
    int Cot = 0, counter = 0;

    cout << "-----Delete Mecidine----" << endl;
    file.open("medicineRecord.txt", ios::in);

    if(!file){
        cout << "No Data is found" << endl;
        file.close();
    }else{
        cout << "Input Medicine ID: ";
        cin >> medicineId;
        temporaryFile.open("tempRecord.txt", ios::app | ios::out);
        while(!file.eof()){
            file.get(ch);
            //input name and expiry date into array
            if(Cot == 0){
                medicine[counter].id.push_back(ch);
                Cot++;
            }else if(ch != ',' && ch != '.' && Cot == 1 && ch != '\n'){
                medicine[counter].name.push_back(ch);
            }else if(ch != ',' && Cot == 2 && ch != '\n'){
                medicine[counter].expiry_date.push_back(ch);
            } 
            //check for next line
            if(ch == '\n'){
                Cot = 0;
                counter++;
            }else if(ch == ','){
                Cot += 1;
            }        
        }

        cout << "string" << endl;
        for(int i=0;i<=counter;i++){
            if(medicineId != medicine[i].id){
                temporaryFile << medicine[i].id << "." << medicine[i].name << "," << medicine[i].expiry_date << ",\n";
            }
        }
        temporaryFile.close();
        file.close();
        //deleting in this case is just creating a new file with the deleted info then rename that file to the correct one
        remove("medicineRecord.txt");
        rename("tempRecord.txt","medicineRecord.txt");
    }
}

int Menu(){
    int options = 0;

    cout << "-----Menu-----" << endl;
    cout << "1. Check medicine record for expiry date" << endl;
    cout << "2. Add medicine" << endl;
    cout << "3. Delete record" << endl;
    cout << "4. Exit" << endl;
    cout << "Options number: ";
    cin >> options;
    cin.ignore();

    return options;
}

int main(){
    bool isContinue = true;
    do{
        int options = Menu();
        switch(options){
            case 1:
                check_expiry_date();
                break;
            case 2:
                add_medicine();
                break;
            case 3:
                delete_medicine();
                break;
            case 4:
                isContinue = false;
                cout<< "Successfully exited!!!" << endl;
                break;
            default:
                cout << "Please input a valid options of 1-4" << endl;
                break;
        }
    }while(isContinue);

    return 0;
}