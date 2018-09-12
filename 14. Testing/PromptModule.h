#ifndef PromptModuleH
#define PromptModuleH

namespace SAMSPrompt
{
    void PauseForUser(void);

    bool UserWantsToContinue(const char*);

    bool InitialPrompt(const char*);

    bool UserWantsToContinueYorN(const char*);
}
    #endif
