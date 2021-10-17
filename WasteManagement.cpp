#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<string.h>
using namespace std;

void menu(void);

char p[30],ch;
char pass[20];

char* pas()
{
    char p;
    int i;
    s:
    printf("Enter password: ");
    for(i=0;;)
    {
        p=getch();
        if(p=='\r')
        {
            pass[i]='\0';
            break;
        }
        
        else if(p=='\b')
        {
            if(i==0)
            continue;
            printf("\b \b");
            i--;
        }
        else
        {
            pass[i]=p;
            printf("\033[31m*\033[30m");
            i++;
        }
    }
    if(i<8)
    {
        printf("!\nPassword should be minimum of 8 characters!\nPress Enter to Try Again\n");
        printf("\n");
        getch();
        goto s;
    }
    return pass;
}

class user{
    char name[150],phno[15],add[150],accno[20],ifsc[10],usernm[10],paswrd[30];
    float price;
    float N,M,wt1,wt2,net;
    public:
      void getd(void){
          cin.get(ch);
          cout<<"Enter name       : ";    cin.getline(name,150);
          cout<<"Enter phone no.  : "; cin.getline(phno,15);
          cout<<"Enter address    : ";   cin.getline(add,150);
          cout<<"Enter account no.: ";  cin.getline(accno,20);
          cout<<"Enter IFSC Code  : ";  cin.getline(ifsc,10);

          for(int i=0;i<8;i++)
          {
              if(i<=3&&i>=0)
              usernm[i]=name[i];
              else
              usernm[i]=phno[i];
          }
          cout<<"\nYour username is : "<<usernm<<"\nRemember this carefully"<<endl;
          strcpy(paswrd,pas());
          cout<<"\nYour password is : "<<paswrd<<endl;
          getch();
      }
      
      void ins(void);
      void login(void);
      void sample(void);
      void result(void);
      void logmenu(void);
}F;

void user::ins(){
          ofstream fout("regdata.dat",ios::app|ios::binary);
          system("cls");
          cout<<"-------Enter Details-------\n";
          getd();
          fout.write((char*)&F,sizeof(F));
          fout.close();
      }
void user::login(){
    ifstream fin("regdata.dat",ios::app|ios::binary);
    if(!fin){
        cout<<"No Data\n";
        getch();
        return;
    }
    system("cls");
    char username[10],password[30],found='n';
    memset(username,'\0',10);
    memset(password,'\0',30);
    cin.get(ch);
    cout<<"Enter username: "; cin>>username;
    while(1){
        fin.read((char*)&F,sizeof(F));
        if(fin.eof())
            break;
        if(strcmp(username,F.usernm)==0){
            found='y';
            if(strcmp(F.paswrd,pas())==0){
                logmenu();
            }
            else{
                cout<<"\nWrong Password\n";
                cout<<"Login Failed\n";
                return;
            }
        }
        }
          if(found=='n')
          {
              cout<<"\nNo such username, You need to register first\n";
              cout<<"----If you want to register then Press 1----";
              ch=getch();
              if(ch=='1')
              ins();
              return;
          }
}
void user::logmenu(){
    system("cls");
    cout<<"----------Login Successfull----------\n";
    cout<<"1. To submit sample\n2. To edit your profile\n3. Exit\nPress your choice (1/2)";
    ch=getch();
    switch (ch)
    {
    case '1':
        sample();
        break;
    case '2':
        getch();
        break;
    
    case '3':
        cout<<"Exiting.......\n";
        getch();
        break;
    
    default:
        while (ch=getchar()!='\n');
        cout<<"\nWrong input\n";
        break;
    }
}
void user::sample(){
    system("cls");
    price=10;
    net=5;
    cout<<"After Submitting your sample in box Press 1\n";
    getch();
    //further evaluation of sample will be done on machines and result will be returned to this function
    if(N>5&& N<10) //Nitrogen Percentage
        price=10;
    else
        price=7;
    M=wt1-wt2; //wt1 is submitted weight of sample, wt2 is remaining weight of sample after heating
    if(M<(wt1/2))   //if weight reduces to half of initial weight
        price-=3;
    cout<<"Price per Kg of waste: Rs."<<price<<endl;
    cout<<"To dump your entire waste Press 1\n";
    ch=getch();
    switch (ch)
    {
    case '1':
        cout<<"\nNet Weight of your waste is: "<<net<<" Kg"<<endl;
        result();
        break;
    
    default:
        while (ch=getchar()!='\n');
        cout<<"Exiting........"    ;
        getch();
        break;
    }
}
void user::result(){
    float amt=price*net;
    cout<<"Rs."<<amt<<" deposited to "<<F.accno<<endl;
}
void menu(){
    again:
    system("cls");
    cout<<"1. Login\n2. Sign Up\n3. Exit\nPress your choice (1/2/3)";
    ch=getch();
    switch (ch)
    {
    case '1':
        F.login();
        getch();
        break;
    case '2':
        F.ins();
        break;
    case '3':
        return;

    default:
        cout<<"\nbWrong Input\n";
        while (ch=getchar()!='\n');
        getch();
        goto again;
    }
    goto again;
}


int main(){
    system("Color 70");
    menu();
    return 0;
}
