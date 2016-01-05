//  Birthday reminder software

#include <iostream>
#include <cstring>
#include <ctime>
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
        int compare_date(char [9]);
};

int Birthday_details :: compare_date(char date[9])
{
    char str[9];
    strcpy(str,dateStr);
    str[6]='\0';
    return !strcmp(str,date);
}

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

int main()
{
    Birthday_details BD;
    char dateStr [9];
    int w8;
    _strdate(dateStr);
    dateStr[6]='\0';
    fstream file;
    file.open("Birthday",ios::in);
    if(!file)
        cout<<"Account could not be opened";
    file.read((char*)&BD,sizeof(BD));
    cout<<"The following birthdays are today: "<<endl;
    while(!file.eof())
    {
        if(BD.compare_date(dateStr))
        {
            BD.put_details();
            cout<<endl;
            cin>>w8;
        }
        file.read((char*)&BD,sizeof(BD));
    }
    file.close();
    return 0;
}
