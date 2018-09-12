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

    static const int myTapeChunk = 3; //Array size

    static char *myOperator = new char[myTapeChunk];
    static int *myOperand = new int[myTapeChunk];

    static int myTapeSize = myTapeChunk; 
    static int myNumberOfEntries = 0;

    //Remember that arrays start with the element 0
    //and that the highest element is the size -theOperand1

    switch (theOperator) // add to the tape
    {
        case '?': // Display the tape

            for (int Index =0; Index < myNumberOfEntries; Index++)
            {
                cout << myOperator[Index] << myOperand[Index] << endl; 
            };

            break;

        case '.': // The program is stopping, delete arrays

            delete [] myOperator;
            delete [] myOperand;

            break;

        default: // Add to the tape and expand if needed

            if (myNumberOfEntries == myTapeSize) //expand
            {
                print("expanding the array...");
                //create a destination for the expansion
                
                char *ExpandedOperator = new char [myNumberOfEntries + myTapeChunk];
                int * ExpandedOperand = new int [myNumberOfEntries + myTapeChunk];

                //we use pointers to do the array copy
                //starting at the array start position

                char *FromOperator = myOperator;
                int *FromOperand = myOperand;

                char *ToOperator = ExpandedOperator;
                int *ToOperand = ExpandedOperand;

                //Copy the old arrays to the new
                //This is supposed to be faster
                //than copying arrays using indexes
                //but it is dangerous

                for(int Index=0;Index < myNumberOfEntries; Index++ )
                {
                    *ToOperator++ = *FromOperator++;
                    *ToOperand++ = *FromOperand++;

                };

                //Delete the old pointers with the new

                myOperator = ExpandedOperator;
                myOperand = ExpandedOperand;

                //Record how big the array is now

                myTapeSize += myTapeChunk;
                
                //now it is safe to add a new entry
            };

            myOperator[myNumberOfEntries] = theOperator;
            myOperand[myNumberOfEntries] = theOperand;
            myNumberOfEntries++;
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

