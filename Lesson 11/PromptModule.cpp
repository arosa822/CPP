#include <iostream>

#include "PromptModule.h"

namespace SAMSPrompt
{
    using namespace std;

    void PauseForUser(void)
    {
        //note you must tyoe something before the Enter Key
        char anyKey;
        cout  << endl << "Press any key followed by \"ENTER\" to continue.." ;
        cin >> anyKey;
    }

    bool InitialPrompt(const char *theInitialPrompt)
    {
        char DoneCharacter;
        

        cout << endl <<  "Did you want to divide? - press any key followed by ENTER to continue"; 
        cout << "Press \"n\" to terminate the program" << endl;


        cin >> DoneCharacter;

        return (DoneCharacter != 'n'); //true when not "n"

    }

        bool UserWantsToContinue(const char *theContinuePrompt)
    { 
        char DoneCharacter;

        

        cout << endl << theContinuePrompt << " - press any key followed by ENTER to continue" << endl;
        cout << "Press \"n\" to terminate the program" << endl;


        cin >> DoneCharacter;

        return (DoneCharacter != 'n'); //true when not "n"

    }

    bool UserWantsToContinueYorN(const char * theThingWeAreDoing)
    {
        char DoneCharacter;
        bool InvalidCharater;

        do
        {
            cout << endl << theThingWeAreDoing << " -  Enter \"y\" to Continue, \"n\" to terminate...";

            cin >> DoneCharacter;

            InvalidCharater = 
            !
            (
                
                (DoneCharacter == 'y')
                ||
                (DoneCharacter == 'n')   
            
            );
            
            if (InvalidCharater)
            {
                cout << "...Error -" << "please press enter \"y\" or \"n\" " << endl;
            };
        }
        while (InvalidCharater);

        return (DoneCharacter != 'n');
    }
}