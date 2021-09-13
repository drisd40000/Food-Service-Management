#include<fstream>
#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;

class food
{
private:
    int no;
    char fname[50];
    float price;

public:
    food()
    {
        no=0;
        strcpy(fname,"no food");
        price=0.0;
    }

    void getfood()
    {
        cout<<"\nEnter serial of food:"<<endl;
        cin>>no;
        cin.ignore();
        cout<<"\nEnter food name::"<<endl;
        cin.getline(fname,49);
        for(int i= 0; i< sizeof(fname); i++)
            fname[i]= tolower(fname[i]);
        fname[0]= toupper(fname[0]);
        cout<<"\nEnter price "<<endl;
        cin>>price;
    }

    void showfood()
    {
        cout<<no<<setw(30)<<fname<<setw(20)<<price<<endl;
    }

    float retp()
    {
        return(price);
    }

    char* retn()
    {
        return(fname);
    }

    int storefood();
    void viewallfood();
    void update(char *);
    void deletefood(char *);
    void searchfood(char *);
    int search_order(char *);
//friend class buyer;
//friend class owner;
};

int food::storefood()//storing
{
    ofstream file;

    if(no==0&&price==0)
    {
        cout<<"\n food not initialized"<<endl;
        return 0;
    }
    else
    {
        file.open("food.DAT",ios::app|ios::binary);
        file.write((char*)this,sizeof(*this));
        file.close();
        return 1;
    }
}

void food::viewallfood()
{
    ifstream file;

    file.open("food.DAT",ios::in|ios::binary);
    if(!file)
        cout<<"Food not found"<<endl;
    else
    {
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            showfood();
            file.read((char*)this,sizeof(*this));
        }
    }
    file.close();
}

void food::update(char *t)
{
    fstream file;

    file.open("food.DAT",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,fname))
        {
            getfood();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
}

void food:: deletefood(char *t)
{
    ifstream fin;
    ofstream fout;

    fin.open("food.DAT",ios::in|ios::binary);

    if(!fin)
        cout<<"Food not exist";
    else
    {
        fout.open("tempfile.DAT",ios::out|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(fname,t))
            {
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));

        }
    }

    fin.close();
    fout.close();
    remove("food.DAT");
    rename("tempfile.DAT","food.DAT");
}

void food::searchfood(char *t)
{
    int counter=0;
    ifstream fin;
    fin.open("food.DAT",ios::in|ios::binary);

    if(!fin)
    {
        cout<<"\nFile not found"<<endl;
    }
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,fname))
            {
                cout<<"\nSearched result:\n\n";
                showfood();
                counter++;
            }

            fin.read((char*)this,sizeof(*this));

        }

        if(counter==0)
            cout<<"\nFood not found on food list or try again"<<endl;

        fin.close();
    }
}

int food::search_order(char *r)
{
    fstream file;
    int counter= 0;

    file.open("food.DAT",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(r,fname))
        {
        return 1;
        }
       else{
            cout<<"\nFood not found on food list or try again"<<endl;
            return 0;
            }
            file.read((char*)this,sizeof(*this));
    }
        file.close();

}

food pr;

class owner:public food
{

private:
    char pass[50];

public:

  /*  void regpass()
    {
        cout<<"Enter password:"<<endl;
        cin.ignore();
        cin.getline(pass,49);
        if(pass == '\0')
        {
            cout<<"not intilized";
        }
        else
        {
            ofstream file;
            file.open("pass.DAT",ios::in|ios::out|ios::binary);
            file.write((char*)this,sizeof(*this));
            file.close();
            cout<<"\npass registerd"<<endl;
        }
    }
*/
    void getpass()
    {
        cout<<"Enter password:"<<endl;
        cin.getline(pass,49);
    }


    void showpass()
    {
        cout<<"\nYour password:"<<pass;
    }

    char* retps()
    {
        return(pass);
    }

    void updatepass();
    void addfood();
    void deletef();
    void updatef();
    //  friend class buyer;
};

void owner::updatepass()
{
    char t[50];
    cout<<"Enter present password:"<<endl;
    cin.ignore();
    cin.getline(t,49);

    fstream file;
    file.open("pass.DAT",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,pass))
        {
            cout<<"\nEnter your new password"<<endl;
            getpass();
            showpass();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }

}

void owner::addfood()
{
    char t[50];
    int n,i;
    cout<<"\nEnter password:"<<endl;
    cin.ignore();
    cin.getline(t,49);

    ifstream file;
    file.open("pass.DAT",ios::in|ios::out|ios::binary);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,pass))
        {
            cout<<"\nHow many food to add :\n";
            cin>>n;
            for(i=0; i<n; i++)
            {
                food::getfood();
                food::storefood();
            }
        }

        file.read((char*)this,sizeof(*this));


    }
    file.close();
}

void owner::deletef()
{
    char t[50],f[50];
    int j,m;

    cout<<"\nEnter password:"<<endl;
    cin.ignore();
    cin.getline(t,49);

    ifstream fp;
    fp.open("pass.DAT",ios::in|ios::out|ios::binary);
    fp.read((char*)this,sizeof(*this));

    while(!fp.eof())
    {
        if(!strcmp(t,pass))
        {
            cout<<"\nEnter food name :"<<endl;
            cin.getline(f,49);
            for(int i= 0; i< sizeof(f); i++)
                f[i]=tolower(f[i]);
            f[0]=toupper(f[0]);
            food::deletefood(f);
        }

        fp.read((char*)this,sizeof(*this));
    }

    fp.close();
}

void owner::updatef()
{
    char t[50],f[50];
    cout<<"\nEnter password:"<<endl;
    cin.ignore();
    cin.getline(t,49);

    ifstream file;
    file.open("pass.DAT",ios::in|ios::out|ios::binary);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,pass))
        {
            cout<<"\nEnter food name that you want to update :"<<endl;
            cin.getline(f,49);
            for(int i= 0; i< sizeof(f); i++)
                f[i]=tolower(f[i]);
            f[0]=toupper(f[0]);
            food::update(f);
        }
        file.read((char*)this,sizeof(*this));
    }
    file.close();
}

owner s;

class buyer:public food
{
private:
    char bname[50];
    char password[50];
    float cash;
    int total;

public:

    buyer()
    {
        cash=100;
        total=0.0;
    }

    void registration()
    {
        cout<<"\nEnter your name"<<endl;
        cin.ignore();
        cin.getline(bname,49);
        cout<<"\nEnter your password"<<endl;
        cin.getline(password,49);

    }

    void showregister()
    {
        cout<<bname<<setw(30)<<password<<setw(20)<<cash<<endl;
    }

    void order()
    {
        ifstream fp;
        char c[50];
        string arr[50];
        float p[50];
        float d,q;
        float total= 0;
        int n,i,j=0,k=0,x,y;

        cout<<"Enter total number of order :";
        cin>>n;

        for(i=0; i<n; i++)
        {
            cout<<"\nEnter food name:"<<endl;
            cin.ignore();
            cin.getline(c,49);

            for(int i =0; i< sizeof(c); i++)
            c[i]=tolower(c[i]);
            c[0]=toupper(c[0]);
            int m;
            m = search_order(c);
            if(m!=0){
            cout<<"\nEnter "<<c<<" quantity:"<<endl;
            cin>>q;

            fp.open("food.DAT",ios::in|ios::binary);
            fp.read((char*)&pr,sizeof(food));

            while(!fp.eof())
            {
                if(!strcmp(c,pr.retn()))
                {
                    d=pr.retp()*q;
                    arr[j]=c;
                    p[k]=pr.retp()*q;
                    cout<<"\nprice is :"<<d;
                    total+=d;
                }
                fp.read((char*)&pr,sizeof(food));
            }
            j++;
            k++;

            fp.close();
        }


        cout<<"\n Total Price is:"<<total;
        cout<<"\n\n\n CASHMEMO\n\n\n";
        for(x=0,y=0; x<j,y<k ; x++,y++)
        {
            cout<<arr[x]<<setw(30)<<p[y]<<endl;
        }
        cout<<"\n--------------------------------------------------------------------------------\n";
        cout<<"TOTAL"<<setw(30)<<total;
        }
    }

    int storegister();
    void addregister();
    void viewallregister();
    void searchregister(char *t);
    void addcash(char* t);
    void viewallrecord();
};

int buyer::storegister()
{
    ofstream file;
    if(bname==""&&password=="")
    {
        cout<<"\n not initialized"<<endl;
        return 0;
    }
    else
    {
        file.open("register.DAT",ios::app|ios::binary);
        file.write((char*)this,sizeof(*this));
        file.close();
        return 1;
    }
}
void buyer::viewallrecord()
{
    ifstream file;
    file.open("register.DAT",ios::in|ios::binary);

    if(!file)
        cout<<"Record not found"<<endl;
    else
    {
        file.read((char*)this,sizeof(*this));
        while(!file.eof())
        {
            cout<<"\n"<<bname<<setw(30)<<password<<setw(30)<<cash<<"\n";
            file.read((char*)this,sizeof(*this));
        }
    }
    file.close();
}

void buyer::viewallregister()
{
    char t[50];
    cout<<"\nEnter password:"<<endl;
    cin.ignore();
    cin.getline(t,49);

    ifstream fp;
    fp.open("pass.DAT",ios::in|ios::out|ios::binary);
    fp.read((char*)&s,sizeof(owner));
    while(!fp.eof())
    {
        if(!strcmp(t,s.retps()))
        {
            cout<<"\n\n\t\t\tAccounts Record(Username, Password, Balance)"<<endl;
            viewallrecord();
        }
        fp.read((char*)this,sizeof(*this));
    }
    fp.close();
}

void buyer::searchregister(char *t)
{
    int pc;
    char p[50];
    fstream file;

    file.open("register.DAT",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,bname))
        {
            cout<<"Enter Password of Your Account:"<<endl;
            cin.getline(p,49);
            if(!strcmp(p,password))
            {
                cout<<"Enter Your Cash To Pay:";
                cin>>pc;
                cash=cash-pc;
                if(cash<-100)
                {
                    cout<<"\nYou Can't Pay AS It IS Under -100 tk \nSo You Can't pay through Account\n Pay in Cash\n THANK YOU";
                    break;
                }
                cout<<"Now Your Account Balance Is::"<<cash;
                file.seekp(file.tellp()-sizeof(*this));
                file.write((char*)this,sizeof(*this));
            }
        }
        file.read((char*)this,sizeof(*this));
    }
}

void buyer::addcash(char *t)
{
    int cs;
    cout<<"Enter cash to your account:";
    cin>>cs;

    fstream file;
    file.open("register.DAT",ios::in|ios::out|ios::binary);
    file.seekg(0);
    file.read((char*)this,sizeof(*this));

    while(!file.eof())
    {
        if(!strcmp(t,password))
        {
            cash=cash+cs;
            cout<<"Now Your Account Balance Is "<<cash<<endl;
            cout<<"\n\t\t\tYour Account Info\n\t\t\t(Name,Password,Balance)\n"<<endl;
            showregister();
            file.seekp(file.tellp()-sizeof(*this));
            file.write((char*)this,sizeof(*this));
        }
        file.read((char*)this,sizeof(*this));
    }
}

int menu()
{
    int ch;
    cout<<"\n\n\n**********WELCOME TO BOTTALA FOOD SERVICE***********";
    cout<<"\n PRESS 1 TO ORDER ";
    cout<<"\n PRESS 2 TO VIEW FOOD MENU ";
    cout<<"\n PRESS 3 TO SEARCH FOOD ITEM";
    cout<<"\nTO ADD,DELETE,UPDATE FOOD ITEM (***BUT YOU MUST HAVE PASSWORD TO ACCESS ";
    cout<<"\n PRESS 4 TO ADD ITEM IN THE MENU";
    cout<<"\n PRESS 5 TO DELETE ITEM";
    cout<<"\n PRESS 6 TO UPDATE FOOD MENU";
    cout<<"\n PRESS 7 TO UPDATE PASSWORD (SELLER)";
    cout<<"\n PRESS 8 TO OPEN ACCOUNT";
    cout<<"\n PRESS 9 TO VIEW ALL ACCOUNT (MUST HAVE PASSWORD TO ACCESS:";
    cout<<"\n PRESS 10 TO ADD CASH TO YOUR ACCOUNT:";
    cout<<"\n PRESS 0 TO EXIT";
    cout<<"\nENTER YOUR CHOICE  ::"<<endl;
    cin>>ch;
    return (ch);
}

int main()
{
    food f;
    owner w;
    buyer b;
    char title[50];
    char btitle[50];
    char name[50];
    int x=1,n,i,m,j,z,a;

    while(x)
    {
        switch(menu())
        {

        case 1:
            cout<<"\n\t***Today's Food Menu***\n\n";
            f.viewallfood();
            b.order();
            cout<<"\nDo You Want To Pay Through Account or NOT(if YES  1  NO 0"<<endl;
            cin>>a;
            if(a==1)
            {
                cout<<"Enter Name of Your Account:\n";
                cin.ignore();
                cin.getline(name,49);
                b.searchregister(name);
            }
            if(a==0)
            {
                cout<<"please pay cash Then ...\n Thank YOU";
                break;
            }
            break;

        case 2:
            cout<<"\n\n\t\t***Food Menu*** \n\n";
            f.viewallfood();
            break;

        case 3:
            cout<<"Enter food name :"<<endl;
            cin.ignore();
            cin.getline(title,49);
            for(int i= 0; i< sizeof(title); i++)
                title[i]=tolower(title[i]);
            title[0]=toupper(title[0]);
            f.searchfood(title);
            break;

        case 4:
            w.addfood();
            cout<<"\n\n\t\t*****Updated food menu*****\n\n";
            w.viewallfood();
            break;

        case 5:
            w.deletef();
            cout<<"\n\n\t\t*****Updated food menu*****\n\n";
            f.viewallfood();
            break;

        case 6:
            cout<<"How many food item to update :";
            cin>>n;
            for(i=0; i<n; i++)
                w.updatef();
            cout<<"\n\n\t\t*****Updated food menu*****\n\n";
            f.viewallfood();
            break;

        case 7:
            w.updatepass();
            break;

        case 8:
            b.registration();
            b.storegister();
            cout<<"Your Account Open Successfully"<<endl;
            break;

        case 9:
            b.viewallregister();
            break;

        case 10:
            cout<<"Enter Your Account Password:"<<endl;
            cin.ignore();
            cin.getline(btitle,49);
            b.addcash(btitle);
            break;

        default:
            cout<<"\nINVALID CHOICE";
            break;

        case 0:
            x=0;
            break;
        }
    }
    return 0;
}
