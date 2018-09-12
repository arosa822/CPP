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
   
    char Operator;
    cin >> Operator;

    return Operator;
}

float GetOperand(void)
{
    float Operand;
    cin >> Operand;

    return Operand;
}

void Tape(const char theOperator, const float theOperand = 0)
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

float Accumulator(const char theOperator, const float theOperand = 0)
{
    static float myAccumulator = 0;
        //Initialized to 0 when the program starts
    
    switch(theOperator)
    {
        case '+':
            myAccumulator = myAccumulator + theOperand;
            Tape(theOperator,theOperand);
            break;

        case '-':
            myAccumulator = myAccumulator - theOperand;
            Tape(theOperator,theOperand);
            break;
        
        case '*':
            myAccumulator = myAccumulator * theOperand;
            Tape(theOperator,theOperand);
            break;
        
        case '/':
            myAccumulator = myAccumulator / theOperand;
            Tape(theOperator,theOperand);
            break;

        case '@':
            myAccumulator =  theOperand;
            Tape(theOperator,theOperand);
            break;

        case '=':
            cout << endl << myAccumulator << endl;
            break;

        case '?':
            Tape(theOperator);
            break;
        
        default:
            throw std::runtime_error("Error - Invalid operator");
    };

    
    return myAccumulator;
}

bool TestOK(
        const char theOperator,
        const float theOperand,
        const float theExpectedResult
    )
{
    float Result = Accumulator(theOperator,theOperand);

    if(Result == theExpectedResult)
    {
        cout << theOperator << theOperand << " - succeeded." << endl;
        return true;
    }
    else
    {
        cout << theOperator << theOperand << " - failed." <<
             "Expected " << theExpectedResult << ", got " << 
                Result << endl;
        return false;
    };
}

void SelfTest(void)
{
    float OldValue = Accumulator('=');

    try
    {
        if  
            (
                TestOK('@',0,0) &&
                TestOK('+',3,3) &&
                TestOK('-',2,1) &&
                TestOK('*',4,4) &&
                TestOK('/', 2,2)
            )
        {
            cout << "Test completed successfully" << endl;
        }
        else
        {
            cout << "Test failed" << endl;

        };           
    }
    catch(...)
    {
        cout << "An exception occured during self test." << endl;
    };

    Accumulator('@', OldValue);
}

int main(int argc, char* argv[])
{
    SAMSErrorHandling::Initialize();

    char Operator; //Used in the loop

        do
        {
            try
            {
                Operator = GetOperator();
                
                if
                    (
                        Operator == '+' ||
                        Operator == '-' ||
                        Operator == '*' ||
                        Operator == '/' ||
                        Operator == '@'  //set Value  
                    )
                {
                    float Operand = GetOperand();
                    Accumulator(Operator,Operand);
                }
                else if (Operator == '!')
                {
                    SelfTest();
                }
                else if (Operator == '.')
                {
                    //Do nothing we are stopping
                }
                else // Some other operator, no operand
                {
                    Accumulator(Operator);
                };
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
        while (Operator != '.'); // continue

        Tape('.');
          
        return 0;
}

