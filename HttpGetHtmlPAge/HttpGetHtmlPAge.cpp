#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#pragma comment(lib, "urlmon.lib")
using namespace std;

int main()
{
    // the URL to download from
    const char* privatURL = "https://api.privatbank.ua/p24api/pubinfo?json&exchange&coursid=5";
    const char* bankgovuaURL = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
    // the destination file
    const char* destFilePrivat = "privat.txt";
    const char* destFileBankGovUa = "BankGovUa.txt";

    // URLDownloadToFile returns S_OK on success
    if (S_OK == URLDownloadToFileA(NULL, privatURL, destFilePrivat, 0, NULL))
    {
        cout << "Saved to " << destFilePrivat << "\n";
    }
    if (S_OK == URLDownloadToFileA(NULL, bankgovuaURL, destFileBankGovUa, 0, NULL))
    {
        cout << "Saved to " << destFileBankGovUa << "\n";
    }

    string preparcingPrivat,preparcingBankGovUa, buffer;

    std::ifstream ingov("BankGovUa.txt");
    if (ingov.is_open())
    {
        while (getline(ingov, buffer))
        {
            preparcingBankGovUa += buffer;
        }
    }
    ingov.close();

    std::ifstream in("privat.txt");
    if (in.is_open())
    {
        while (getline(in, preparcingPrivat))
        {
            
        }
    }
    in.close();

   
    cout << endl;
    
    for (int i = 0; i < preparcingPrivat.length(); i++)
    {
        if (preparcingPrivat[i + 1] == ',' || preparcingPrivat[i] == '{' || preparcingPrivat[i + 1] == '}') {
            preparcingPrivat.insert(i + 1, 1, '\n');
            i++;
        }
    }   
    string subject_to_search[2] { "EUR", "USD" };
    string postparcingPrivat;

    //Privat Parcing
    for (int i = 0; i < 2; i++)
    {
        size_t found = preparcingPrivat.find(subject_to_search[i]);
        postparcingPrivat += subject_to_search[i] + " - ";
        for (int j = found + subject_to_search[i].length() + 27; preparcingPrivat[j] != '\n'; j++)
        {
            if (preparcingPrivat[j] != '"') {
                postparcingPrivat += preparcingPrivat[j];
            }
        }
        postparcingPrivat += '\n';
    }
    cout << "Privat Bank data:" << endl;
    cout << postparcingPrivat;

    string subject_to_search2[2]{"\"cc\":\"EUR\"", "\"cc\":\"USD\"" };
    string postparcingGovBankUa;

    //BankGovUa Parcing
    for (int i = 0; i < 2; i++)
    {
        size_t found = preparcingBankGovUa.find(subject_to_search2[i]);
        postparcingGovBankUa += subject_to_search[i] + " - ";
        for (int j = found-8; preparcingBankGovUa[j] != ','; j++)
        {
            if (preparcingBankGovUa[j] != ',') {
                postparcingGovBankUa += preparcingBankGovUa[j];
            }
        }
        postparcingGovBankUa += '\n';
    }
    cout << "Bank Gov Ua data:" << endl;
    cout <<  postparcingGovBankUa;
    

}