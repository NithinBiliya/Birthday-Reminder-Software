//  Birthday manager software

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

class Birthday_details
{
    char nameStr[20],dateStr[9];
    public:
        Birthday_details(void)
        {
            strcpy(nameStr,"");
            strcpy(dateStr,"");
        }
        void get_details(void);
        void put_details(void);
        int compare(char [20]);
};

int Birthday_details :: compare(char name[20])
{
    return !strcmp(name,nameStr);
}

void Birthday_details :: get_details(void)
{
    cout<<"Enter the full name: ";
    cin>>nameStr;
    cout<<"Enter the date of birth (MM/DD/YY): ";
    cin>>dateStr;
}

void Birthday_details :: put_details(void)
{
    cout<<"\tName: "<<nameStr<<endl<<"\tBirthday: "<<dateStr<<endl;
}

void add_new(Birthday_details);
void deleteBD(char [20]);
void modify(char [20]);
void display(void);

int main()
{
    Birthday_details BD;
    char name[20];
    unsigned int opt;
    do
    {
        cout<<"\n\n\t\tBIRTHDAY MANAGER"
            <<"\n\t1. Add new birthday"
            <<"\n\t2. Delete a birthday"
            <<"\n\t3. Modify a birthday"
            <<"\n\t4. Display all birthdays"
            <<"\n\t5. Delete the old database"
            <<"\n\t6. Exit"
            <<"\nEnter your choics: ";
        cin>>opt;
        switch(opt)
        {
            case 1: cout<<"Please enter the following details: "<<endl;
                    BD.get_details();
                    add_new(BD);
                    break;
            case 2: cout<<"Please enter the name of the person to be deleted: "<<endl;
                    cin>>name;
                    deleteBD(name);
                    break;
            case 3: cout<<"Please enter the name of the person to be modified: "<<endl;
                    cin>>name;
                    modify(name);
                    break;
            case 4: cout<<"The birthdays are as follows: \n"<<endl;
                    display();
                    break;
            case 5: remove("Birthday");
                    cout<<"Old database deleted!"<<endl;
                    break;
            case 6: cout<<"Thank you!";
                    exit(0);
            default: cout<<"Wrong option!"<<endl;
        }
    }while(1);
    return 0;
}

void add_new(Birthday_details BD)
{
    fstream file;
    file.open("Birthday",ios::out | ios::app);
    if(!file)
        cout<<"Account could not be opened";
    file.write((char*)&BD,sizeof(BD));
    cout<<"New name added succesfully!";
}

void deleteBD(char name[20])
{
    int flag=0;
    fstream file1,file2;
    Birthday_details BD;
    file1.open("Birthday",ios::in);
    file2.open("temp",ios::out);
    if(!file1 || !file2)
        cout<<"Account could not be opened";
    file1.read((char*)&BD,sizeof(BD));
    while(!file1.eof())
    {
        if(!BD.compare(name))
            file2.write((char*)&BD,sizeof(BD));
        else
            flag=1;
        file1.read((char*)&BD,sizeof(BD));
    }
    if(flag)
        cout<<"Successfully deleted!"<<endl;
    else
        cout<<"The entered name is not found!"<<endl;
    file1.close();
    file2.close();
    remove("Birthday");
    rename("temp","Birthday");
}

void modify(char name[20])
{
    int flag=0;
    fstream file1,file2;
    Birthday_details BD;
    file1.open("Birthday",ios::in);
    file2.open("temp",ios::out);
    if(!file1 || !file2)
        cout<<"Account could not be opened";
    file1.read((char*)&BD,sizeof(BD));
    while(!file1.eof())
    {
        if(BD.compare(name))
        {
            flag=1;
            cout<<"Please enter the new information: "<<endl;
            BD.get_details();
        }
        file2.write((char*)&BD,sizeof(BD));
        file1.read((char*)&BD,sizeof(BD));
    }
    if(!flag)
        cout<<"The entered name does not exist in the databae.!"<<endl;
    file1.close();
    file2.close();
    remove("Birthday");
    rename("temp","Birthday");
}

void display(void)
{
    Birthday_details BD;
    fstream file;
    file.open("Birthday",ios::in);
    if(!file)
        cout<<"Account could not be opened";
    file.read((char*)&BD,sizeof(BD));
    while(!file.eof())
    {
        BD.put_details();
        cout<<endl;
        file.read((char*)&BD,sizeof(BD));
    }
    file.close();
}
