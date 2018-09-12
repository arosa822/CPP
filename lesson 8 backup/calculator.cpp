#include <iostream>

#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

float GetDividend(void)
{
   
    float Dividend = 0;
    cout << "Dividend: ";
    cin >> Dividend;

    return Dividend;
}

float GetDivisor(void)
{
    float Divisor = 1;

    cout << "Divisor: ";
    cin >> Divisor;

    return Divisor;
}

float Divide
    (const float theDividend, const float theDivisor)
{
    return (theDividend/theDivisor);
}

int main(int argc, char* argv[])
{
    SAMSEerrorHandling::Initialize();

    float ReturnCode = 0; 

    try
    {
        float Dividend = GetDividend();
        float Divisor = GetDivisor();

        cout << Divide(Dividend,Divisor) << endl;
    }
    catch(...)
    {
        ReturnCode = SAMSEerrorHandling::HandleNotAnumberError();

    };

    SAMSPrompt::PauseForUserAcknowlegment();
    return ReturnCode;
}

