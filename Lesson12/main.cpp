#include <iostream>
#include <stdexcept>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

void print(const char* toPrint)
{
    cout << toPrint << endl;
}

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

void Tape(const char theOperator, const float theOperand)
{

    static const int myTapeSize = 20; //Array size

    static char myOperator[myTapeSize]; // Operator part
    static float myOperand[myTapeSize]; // Operand part

    static int myNumberOfEntries = 0; // what is in the tape right now

    //Remember that arrays start with the element 0
    //and that the highest element is the size -theOperand1

    if (theOperator != '?') // add to the tape
    {
        if(myNumberOfEntries < myTapeSize) // we have room
        {
            print("Adding elements to the tape...");
            myOperator[myNumberOfEntries] = theOperator;
            myOperand[myNumberOfEntries] = theOperand;
            myNumberOfEntries++;
        }
        else // about to overflow the array
        {
            throw std::runtime_error("Error- Out of room on the tape.");
        };
    }
    else // Display the tape
    {
        print("displaying values...");

        for (int Index = 0; Index < myNumberOfEntries; Index++)
       
        {
            
            //cout << "Index: " << Index << endl;
            cout << myOperator[Index]; 
            cout << " , " ;
            cout << myOperand[Index] << endl;
        };
    };
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

        case '?':
            break;
        
        default:
            throw std::runtime_error("Error - Invalid operator");

    };
    Tape(theOperator,theOperand);
    
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
         while (SAMSPrompt::UserWantsToContinueYorN("More?"));
          
        return 0;
}

