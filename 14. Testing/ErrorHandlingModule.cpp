#include <iostream>
#include "ErrorHandlingModule.h"
#include <stdexcept>

namespace SAMSErrorHandling
{
    using namespace std;

    void Initialize(void)
    {
        cin.exceptions(cin.failbit);
    }

    int HandleNotANumberError(void) // Returns the error code
    {
        cerr << "Input Error - not a number?" << endl;
        cin.clear(); //Clear Error state from the stream

        //Eat the bad input so we can pause the program
        char BadInput[5];
        cin >> BadInput;

        return 1; // an error has occured

    }

    int HandleRuntimeError(std::runtime_error theRuntimeError)
    {
        cerr << theRuntimeError.what() << endl;

        return 1;
    }
}