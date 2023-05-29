#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include <cmath>
#include<ctime>
#include<cstring>
int currentYear(void);
using namespace std;
//#include "account.h"
class account
{
protected:
    std::string DepositorName;
    short AccountNo;
    float balance;
    static float min_balance;
    int InitYear;
    std::string AccountType;
public:
    //void GetDetails();
    void putDetails(std::string name, std::string type, short num, int year, float bal);
    void deposit();
    float ServiceCharge();
    void CheckBalance();
    virtual float withdraw(void);
    void connectToFile();
};

void account::connectToFile()
    {
        std::ofstream outfile(DepositorName);

        if(!outfile.is_open())
            {
                std::cout<<"Unable to open account's file"<<std::endl;
                exit(1);
            }

        outfile<<DepositorName<<std::endl;
        outfile<<AccountType<<std::endl;
        outfile<<AccountNo<<std::endl;
        outfile<<InitYear<<std::endl;
        outfile<<balance<<std::endl;
        outfile.close();
    }    

float account::withdraw(void)
{
    float amount;
    std::cout<<"Enter amount: ";std::cin>>amount;
    if (amount > 0)
    {
        if (amount <= balance)
        {
            return (balance = balance - amount);
        }
        else
        {
            std::cout << "Insufficient balance!" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid amount!" << std::endl;
    }
    return (balance);
}
//setting minimum balance
float account::min_balance = 10000;

void account::deposit(void)
{   
    float amount;
    std::cout<<"Enter amount: ";std::cin>>amount;
    //no maximum limit for the amount
    if (amount > 0)
    {
        balance = balance + amount;
    }
    else
    {
        std::cout << "Invalid amount!" << std::endl;
    }
}

float account::ServiceCharge()
{
    float PercentageCharge = 0.1;
    if (balance < min_balance)
    {
        return (balance = balance - (PercentageCharge * balance));
    }
    else
    {
        return (balance);
    }
}

// void account::GetDetails()
// {
//     std::cout << "Depositor name: ";
//     std::cin >> DepositorName;
//     std::cout << "Account No.: ";
//     std::cin >> AccountNo;
//     std::cout << std::endl;
// }

void account::putDetails(std::string name, std::string type, short num, int year, float bal)
    {
        DepositorName = name;
        AccountType = type;
        AccountNo = num;
        InitYear = year;
        balance = bal;
    }
void account::CheckBalance()
{
    std::cout << "Your account balance is: " << balance << std::endl;
}

//savings account inherited from account
class saving_account : public account
{
    const float rate = 0.1;
    int WithdrawYear;

public:
    saving_account() {};
    saving_account(std::string DepositorName, std::string AccountType, short AccountNo, int InitYear, float balance);
    float CompInterest();
    friend void readFile(saving_account &obj);
};

//constructor for entering details
saving_account::saving_account(std::string DepositorName, std::string AccountType, short AccountNo, int InitYear, float balance)
{
        this->DepositorName = DepositorName;
        this->AccountType = AccountType;
        this->AccountNo = AccountNo;
        this->InitYear = InitYear;
        this->balance = balance;
        if(balance < min_balance)
            {
                std::cout<<"The initial amount should be greater than "<<min_balance<<"\n";
                exit(1);
            }
            //connect to output file
            connectToFile();
        std::cout<<"\n";

}


float saving_account::CompInterest()
{
    int n = currentYear()- InitYear;
    std::cout<<"No of yrs is "<<n<<endl;
    balance = balance * pow((1 + rate), n);
    return (balance);
}

//current account inherited from account
class current_account:public account{
    string payee_name;
    string bank_name;
    int checkNo;
    float payment_amount;
    string date;
    public:
    current_account() {};
    current_account(std::string DepositorName, std::string AccountType, short AccountNo, int InitYear, float balance);
    void checkbook();
    float withdraw(float amount);    

};
void current_account::checkbook()
	{
        cout<<"CHECKBOOK"<<std::endl;
		std::cout<<"Payee's name: ";
        std::cin>>payee_name;
        std::cout<<"Bank name: ";
        std::cin>>bank_name;
        std::cout<<"Check number: ";
        std::cin>>checkNo;
        std::cout<<"Amount: ";
        std::cin>>payment_amount;
        std::cout<<"Date(DD/MM/YYYY): ";
        std::cin>>date;
        withdraw(payment_amount);
        connectToFile();
        ofstream outfile("Checkbook");
        if(!outfile.is_open())
            {
                std::cout<<"Unable to open account's file"<<std::endl;
                exit(1);
            }
        outfile<<payee_name<<std::endl;  
        outfile<<bank_name<<std::endl;
        outfile<<checkNo<<std::endl;
        outfile<<payment_amount<<std::endl;
        outfile<<date<<std::endl;
        outfile.close();
        
	}

current_account::current_account(std::string DepositorName, std::string AccountType, short AccountNo, int InitYear, float balance)
	{
        this->DepositorName = DepositorName;
        this->AccountType = AccountType;
        this->AccountNo = AccountNo;
        this->InitYear = InitYear;
        this->balance = balance;
        
            if(balance < min_balance)
                {
                    std::cout<<"The initial amount should be greater than "<<min_balance<<"\n";
                    exit(1);
                }
                //connect to output file
                connectToFile();
            std::cout<<"\n";
	}
    
    float current_account::withdraw(float amount)
        {
            
            if (amount > 0)
            {
                if (amount <= balance)
                {
                    return (balance = balance - amount);
                }
                else
                {
                    std::cout << "Insufficient balance!" << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid amount!" << std::endl;
            }
            return (balance);
        }
    //declared as a friend
    // void readFile(saving_account &obj)
    // {

    //     while(!infile.eof())
    //     {
    //         int c = 0;
    //         std::string line; 
    //         std::getline(infile, line);
    //         stringstream ss;
    //         ss <<line;
    //         if(c == 0)      ss >>obj.DepositorName;
    //         else if(c == 1) ss >>obj.AccountType;
    //         else if(c == 2) ss >>obj.AccountNo;
    //         else if (c == 3) ss>> obj.InitYear;
    //         else if (c == 4) ss>>obj.balance;
    //         line ="";
    //         c++;
    //     }
    // }
//main
int main()
{
   
    short opt;
    string accountName;
    short choice;


   //starting program
	std::cout<<"WELCOME TO QUALITY BANK"<<endl;

    tryAgain:
	std::cout<<"1.Create account"<<std::endl;
    std::cout<<"2.Already have an account"<<std::endl;
    std::cout<<"> "; std::cin>>choice;

            string name;
            string type;
            short num;
            int year;
            float bal;
            saving_account acc1;
            current_account acc2;
    
            //creating an account
            if(choice == 1)
            {
                    re_enter_choice:
                    std::cout<<"Choose account type"<<std::endl;
                    std::cout<<"1.Saving"<<std::endl;
                    std::cout<<"2.Current"<<std::endl;
                    short opt;
                    std::cout<<"> ";std::cin>>opt;
                    //saving account
                    if(opt == 1)
                        {
                            std::cout<<"Depositor's name(username): ";std::cin>>name;
                            std::cout<<"Account Type(Saving/Current): "; std::cin>>type;
                            std::cout<<"Account Number: ";std::cin>>num;
                            std::cout<<"Initial year: "; std::cin>>year;
                            std::cout<<"Initial amount: "; std::cin>>bal;

                            //saving accout object created
                            //registration details are automatically invoked by constructor
                            saving_account save1(name, type, num, year, bal);
                            return(0);
                        }
                    else if(opt == 2)
                        {
                            std::cout<<"Depositor's name(username): ";std::cin>>name;
                            std::cout<<"Account Type(Saving/Current): "; std::cin>>type;
                            std::cout<<"Account Number: ";std::cin>>num;
                            std::cout<<"Initial year: "; std::cin>>year;
                            std::cout<<"Initial amount: "; std::cin>>bal;
                        
                            //current account abject created
                            current_account current1(name, type, num, year, bal);
                            return(0);     
                        }
                    else
                        {
                            std::cout<<"Invalid account!"<<std::endl;
                            goto re_enter_choice;
                        }
                

            }

             //reading and manipulating existing account   
            else if(choice == 2)
            {

            std::string username;
            cout<<"Enter username ";cin>>username;
            ifstream file(username);
            if(!file)
                {
                    cout<<"This account does not exist!"<<std::endl;
                    exit(1);
                }
                stringstream ss;
                const int N = 10;
                //char line[N];
                std::string line;
                int c = 0;
                const int LINE_COUNT = 5;
                std::string* data = new std::string[LINE_COUNT]; 
                for( int i = 0; i<LINE_COUNT; i++)
                    {
                        std::getline(file, line);
                        *data = line;
                        line = "";
                      ss<<*data<<std::endl;
                        if(c == 0) ss>> name;
                        else if(c == 1) ss>>type;
                        else if(c == 2) ss>>num;
                        else if(c == 3) ss>>year;
                        else if(c == 4) ss>>bal;
                        c++;
                        ss.str("");
                        ss.clear();
                        
                    }
                    file.close();
                    delete[] data;
                    
                    if( type == "Saving")
                        {
                            goto saving_account;
                        }
                    else if(type == "Current")
                    {
                        goto current_account;
                    }
                    else
                    {
                        cout<<"Invalid account!"<<"\n";
                        return(0);
                    }
                
            }
            
            //invalid choice
            else
            {
                cout<<"Invalid option"<<std::endl;
                goto tryAgain;
            }
        
        //inside the savings account
            saving_account:
            //create saving object to capture file content
            
            acc1.putDetails(name,type,num,year,bal);
        // acc1.GetDetails();
            cout<<"Choose what you would like to do"<<"\n";
            cout<<"1. Check balance"<<endl;
            cout<<"2. Deposit"<<endl;
            cout<<"3. Withdraw"<<endl;
            cout<<"\n";
            cout<<"> "; cin>>opt;

            switch (opt)
            {
                case 1:
                    acc1.CheckBalance();
                    acc1.connectToFile();
                    break;
                case 2:
                    acc1.deposit();
                    acc1.connectToFile();
                    break;
                case 3:
                    acc1.withdraw();
                    acc1.CheckBalance();
                    break;
                default:
                    cout<<"Invalid option!"<<endl;

            }
            return(0);
   
	
        
	        
        current_account:
        
        acc2.putDetails(name, type,num,year,bal);
    	acc2.checkbook();
    	//acc2.withdraw();
        //acc2.connectToFile();

    	return(0);
}//end of main

int currentYear()
{
    time_t currentTime;
    currentTime =(time(NULL)/(3600*24*365))+ 1970;
    return(currentTime); 
    
}