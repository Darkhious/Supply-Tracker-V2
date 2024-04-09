#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX = 200;

string response;
int i;
bool found;
string n_Supply[MAX] = {""};
string n_Inventory[MAX] = {""};
int p_Supply[MAX] = {0};
int q_Supply[MAX] = {0};
int p_Inventory[MAX] = {0};
int q_Inventory[MAX] = {0};

void clear()
{
    system("cls");
}

void companyName()
{
    cout<<"Jolliwasp Foods Corporation\n\n\n";
}

string capitalize(string text)
{
    for (i = 0; i < text.length(); i++)
    {
        text[i] = toupper(text[i]);
    }

    return text;
}

void message(string text)
{
    clear();
    cout<<"NOTICE: "<<text<<endl;
}

bool yesOrNo()
{
    bool falseInput;

    falseInput = true;

    while (falseInput)
    {
        cout<<"Would you like to open the invoice? (Y/N): ";
        getline(cin, response);

        if (response == "Y" || response == "y")
        {
            falseInput = false;

            return true;
        }  
            else if (response == "N" || response == "n")
            {
                falseInput = false;

                return false;
            }
                else
                {
                    cout<<"\nPlease input 'Y' or 'N' only!\n";
                }
    }
}

bool numOnly(string text)
{
    char character;

    found = false;

    for(i = 0; i < text.length(); i++)
    {
        character = text[i];

        if (character <= '9' && character >= '0')
        {
            continue;
        }
            else
            {
                found = true;
            }

    }
    if (found)
    {
        return true;
    }
        else
        {
            return false;
        }
}

bool security()
{
    string password, filename, line;
    bool firstLog;

    found = false;
    firstLog = true;

    while (!found)
    {
        password = "";

        if (!firstLog)
            clear();
            else
                firstLog = false;

        while (!found)
        {
            companyName();
            cout<<"LOG IN\n\n";

            cout<<"Username: ";
            getline(cin, response);

            filename = response + ".txt";
            ifstream account(filename);

            if (account.is_open())
            {
                for(i = 0; i <= 7; i++)
                {
                    getline(account, line);
                }
                for(i = 10; i < line.length(); i++)
                {
                    password += line[i];
                }

                account.close();

                break;
            }
                else
                {
                    message("Account not found!");
                }
        }
        cout<<"Password: ";
        getline(cin, response);

        if (response == password)
        {
            found = true;

            break;
        }
            else
            {
                message("Account not found!");
            }
    }
    if (found)
        return true;
        else
            return false;
}

void inventory()
{
    int ctr;

    ctr = 1;

    companyName();
    cout<<"INVENTORY SECTOR\n\n";

    for (i = 0; i < MAX; i++)
    {
        if (n_Inventory[i] != "")
        {
            cout<<ctr<<".) "<<n_Inventory[i]<<endl;
            cout<<"AMOUNT: "<<q_Inventory[i]<<"x"<<endl;
            cout<<"TOTAL: "<<p_Inventory[i]<<" PHP"<<endl<<endl;
        }
    }

    cout<<"Enter anything to continue: ";
    getline(cin, response);
}

void getMenu()
{
    string n_Product, p_Product;

    ifstream menu("menu.txt");

    i = 0;
    while (getline(menu, n_Product))
    {
        getline(menu, p_Product);

        if (n_Supply[i] == "")
        {
            p_Supply[i] = stoi(p_Product);

        }
        i++;
    }
}

void supply()
{
    int ctr;
    string filename, name, quantity;
    bool read;
    
    companyName();
    cout<<"SUPPLY SECTOR\n\n";

    ctr = 1;
    for(i = 0; i < MAX; i++)
    {
        if (n_Supply[i] == "")
        {
            break;
        }
            else
            {
                cout<<ctr<<".) "<<n_Supply[i]<<endl;
                cout<<"QUANTITY: "<<q_Supply[i]<<"x"<<endl;
                cout<<"PRICE: "<<p_Supply[i]<<" PHP"<<endl<<endl;

                ctr++;
            }
    }

    filename = "supply.txt";
    ifstream supply(filename);
    if (supply.is_open())
    {
        cout<<"NOTICE: The system found a supply invoice.\n";
        
        read = yesOrNo();
        if (read)
        {
            while (getline(supply, name))
            {
                getline(supply, quantity);

                name = capitalize(name);

                found = false;
                for (i = 0; i < MAX; i++)
                {
                    if (name == n_Supply[i])
                    {
                        found = true;

                        break;
                    }
                }

                if (found)
                {
                    q_Supply[i] += stoi(quantity);
                }
                    else
                    {
                        for(i = 0; i < MAX; i++)
                        {
                            if (n_Supply[i] == "")
                            {
                                n_Supply[i] = name;
                                q_Supply[i] = stoi(quantity);

                                break;
                            }
                        }
                    }
            }

            supply.close();
            remove("supply.txt");

            message("\nSupply has been added! Please refresh this sector.\n");
        }
    }

    cout<<"Enter anything to exit: ";
    getline(cin, response);
}

void record()
{
    int p_Product, q_Product, total;
    string n_Product;
    bool buying, stocks;

    buying = true;
    stocks = true;

    companyName();
    cout<<"RECORD SECTOR\n\n";

    while (buying)
    {
        found = false;

        cout<<"Enter the name of the product (Enter nothing to exit): ";
        getline(cin, response);

        n_Product = capitalize(response);
        if (response != "")
        {
            for(i = 0; i < MAX; i++)
            {
                if (n_Product == n_Supply[i])
                {
                    p_Product = p_Supply[i];
                    found = true;

                    break;
                }
            }
            if (found)
            {
                cout<<"Enter the amount of purchase: ";
                getline(cin, response);

                q_Product = stoi(response);

                if (q_Product > q_Supply[i])
                {
                    cout<<"\nNOTICE: Amount to buy exceeded remaining stocks.\n\n";
                }
                    else
                    {
                        total = q_Product * p_Product;

                        cout<<"PRODUCT NAME: "<<n_Product<<endl;
                        cout<<"QUANTITY: "<<q_Product<<"x\n";
                        cout<<"PRICE: "<<p_Product<<" PHP\n";
                        cout<<"AMOUNT DUE: "<<total<<endl<<endl;

                        if (yesOrNo())
                        {
                            for(i = 0; i < MAX && stocks; i++)
                            {
                                if (n_Inventory[i] == "")
                                {
                                    n_Inventory[i] = n_Product;
                                    q_Inventory[i] = q_Product;
                                    p_Inventory[i] = total;
                                }
                            }
                        }
                            else
                            {
                                cout<<"Transaction cancelled.\n\n";
                            }
                            

                    }
            }
                else
                    {
                        cout<<"NOTICE: Product not found.\n";
                    }
        }
    }
}

int main()
{
    bool letIn;

    getMenu();
    letIn = security();

    if (letIn)
    {
        do
        {
            clear();
            companyName();
            cout<<"MAIN MENU\n\n";
            cout<<"1.) Inventory \n2.) Supply \n3.) Record \n4.) Exit\n\n";

            cout<<"Select from the options above (1/2/3/4): ";
            getline(cin, response);

            clear();

            if (response == "1")
                inventory();
                else if (response == "2")
                    supply();
                    else if (response == "3")
                        record();
                        else if (response == "4")
                            cout<<"PROGRAM TERMINATED.\n\n";
                            else
                                message("Please input only within the choices!");
        }while (response != "4");
    }

    return EXIT_SUCCESS;
}