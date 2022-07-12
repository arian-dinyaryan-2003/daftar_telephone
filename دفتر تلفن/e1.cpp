#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class Mokhatab
{
public:
    char name[31];
    char kind[20];
    char emial[31];
    char house_call[12];
    char phone_call[12];
    char work_call[12];
    bool delleted;
    int Id;
};
int filesize(string filename)
{
    ifstream X;
    int size;
    X.open(filename, ios::in);
    if (!X.is_open())
    {
        return 0;
    }
    else
    {
        X.seekg(0, ios::end);
        size = X.tellg();
        X.close();
        return size;
    }
}
void regster_mo(void)
{
    Mokhatab A;
    fstream F;
    cout << "\n ******* Enter Information ******\n";
    cout << "\nEnter name : ";
    cin >> A.name;
    cout << "\nEnter email: ";
    cin >> A.emial;
    cout << "\nIf your mokhatab dont have a that number enter 0 ";
    cout << "\nHouse number: ";
    cin >> A.house_call;
    cout << "\nWork number: ";
    cin >> A.work_call;
    cout << "\nphone number: ";
    cin >> A.phone_call;
    do
    {
        cout << "\nWhat kind is your mokhotab (enter frind/reguler/family) : ";
        cin >> A.kind;
    } while (!(strcmp(A.kind, "frind") == 0 || strcmp(A.kind, "reguler") == 0 || strcmp(A.kind, "family") == 0));
    A.delleted = false;
    A.Id = 1000 + filesize("daftar.dat") / sizeof(Mokhatab);
    F.open("daftar.dat", ios::app | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again \n";
        return;
    }
    F.write((char *)&A, sizeof(Mokhatab));
    F.close();
    return;
}
void show_mokhotab(Mokhatab A)
{
    cout << "\n---------------------\n";
    cout << "\n name : " << A.name;
    cout << "\nemail: " << A.emial;
    if (strcmp(A.house_call, "0") != 0)
    {
        cout << "\nHouse number: " << A.house_call;
    }
    if (strcmp(A.work_call, "0") != 0)
    {
        cout << "\nwork number: " << A.work_call;
    }
    if (strcmp(A.phone_call, "0") != 0)
    {
        cout << "\nHouse number: " << A.phone_call;
    }
    cout << "\nMokhatab type : " << A.kind;
    cout << "\n---------------------\n";
}
void show_all(void)
{
    ifstream F;
    Mokhatab A;
    F.open("daftar.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Mokhatab));
    while (!F.eof())
    {
        if (!A.delleted)
        {
            show_mokhotab(A);
        }
        F.read((char *)&A, sizeof(Mokhatab));
    }
}
void delete_Mokhatb(void)
{
    fstream f;
    Mokhatab A;
    if (filesize("daftar.dat") == 0)
    {
        cout << "\nNo customer is register !!! ";
        return;
    }
    int ID;
    cout << "enter house ID to delete : ";
    cin >> ID;
    int pos = ((ID)-1000) * sizeof(Mokhatab);
    if (pos > filesize("daftar.dat"))
    {
        cout << "\nWrong id enterd ";
        return;
    }
    else
    {

        f.open("daftar.dat", ios::in | ios::out | ios::binary);
        if (!f.is_open())
        {
            cout << "\nWrong openning file";
            return;
        }
        else
        {
            f.seekg(pos, ios::beg);
            f.read((char *)&A, sizeof(Mokhatab));
            A.delleted = true;
            f.seekg(pos, ios::beg);
            f.write((char *)&A, sizeof(Mokhatab));
            f.close();
            return;
        }
    }
}
void search_name(void)
{
    Mokhatab A;
    char nam[31];
    cout << "\nEnter name :";
    cin >> nam;
    ifstream F;
    F.open("daftar.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Mokhatab));
    while (!F.eof())
    {
        if (strcmp(nam, A.name) == 0)
        {
            show_mokhotab(A);
            return;
        }
        F.read((char *)&A, sizeof(Mokhatab));
    }
    cout << "\nsorry no such name is exisist ";
    return;
}
void search_call(void)
{
    Mokhatab A;
    char nam[31];
    cout << "\nEnter number :";
    cin >> nam;
    ifstream F;
    F.open("daftar.dat", ios::in | ios::binary);
    if (!F.is_open())
    {
        cout << "\nError whit openning file.please try again\n";
        return;
    }
    F.read((char *)&A, sizeof(Mokhatab));
    while (!F.eof())
    {
        if (strcmp(nam, A.work_call) == 0 || strcmp(nam, A.house_call) == 0 || strcmp(nam, A.phone_call) == 0)
        {
            show_mokhotab(A);
            return;
        }
        F.read((char *)&A, sizeof(Mokhatab));
    }
    cout << "\nsorry no such name is exisist ";
    return;
}
void menue_for_user(void)
{
    int chose;
    do
    {
        cout << "\n\n";
        cout << "\nFor add  mokhatab enter 1";
        cout << "\nFor show all mokhatab enter 2";
        cout << "\nFor search name enter 3";
        cout << "\nFor search call number enter 4";
        cout << "\nFor dellet mokhotab enter 5";
        cout << "\nFor exit that menue enter 0";
        cout << "\n\n>>> ";
        cin >> chose;
        switch (chose)
        {
        case 1:
            regster_mo();
            break;
        case 2:
            show_all();
            break;
        case 3:
            search_name();
            break;
        case 4:
            search_call();
            break;
        case 5:
            delete_Mokhatb();
            break;
        case 0:
            return;
            break;

        default:
            cout << "\nErorr invalid chose ";
            break;
        }
    } while (true);
}
int main()
{
    menue_for_user();
    return 0;
}