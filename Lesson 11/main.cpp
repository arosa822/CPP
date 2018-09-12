#include <iostream>
#include <stdexcept>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

char GetOperator(void)
{
   
    char Operator = '+';
    cout << "Operator: ";
    cin >> Operator;

    return Operator;
}

float GetOperand(void)
{
    float Operand = 1;

    cout << "Operand: ";
    cin >> Operand;

    return Operand;
}

float Divide
    (const float theDividend, const float theDivisor)
{
    return (theDividend/theDivisor);
}

float Accumulate(const char theOperator, const float theOperand)
{
    static float myAccumulator = 0;
        //Initialized to 0 when the program starts
    
    switch(theOperator)
    {
        case '+':
            myAccumulator = myAccumulator + theOperand;
            break;

        case '-':
            myAccumulator = myAccumulator - theOperand;
            break;
        
        case '*':
            myAccumulator = myAccumulator * theOperand;
            break;
        
        case '/':
            myAccumulator = myAccumulator / theOperand;
            break;
        
        default:
            throw std::runtime_error("Error - Invalid operator");

    };

    return myAccumulator;
}

int main(int argc, char* argv[])
{
    SAMSErrorHandling::Initialize();

        do
        {
            try
            {
                char Operator = GetOperator();
                float Operand = GetOperand();

                cout << Accumulate(Operator,Operand) << endl;
            }
            catch(std::runtime_error RuntimeError)
            {
                SAMSErrorHandling::HandleRuntimeError(RuntimeError);
            }
            catch(...)
            {
                SAMSErrorHandling::HandleNotANumberError();   
            };
         }
         while (SAMSPrompt::UserWantsToContinue("More?"));
          
        return 0;
}

