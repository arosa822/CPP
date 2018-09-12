#include <iostream>

#include "PromptModule.h"

//namespace SAMSPrompt
//{
    using namespace std;

    void PauseForUserAcknowledgement (void)
    {
        //note you must tyoe something before the Enter Key
        char anyKey;
        cout  << endl << "Press any key followed by \"ENTER\" to continue.." ;
        cin >> anyKey;
    }
//}