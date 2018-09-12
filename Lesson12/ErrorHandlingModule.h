
#ifndef ErrorHandlingModuleH
#define ErrorHandlingModuleH


namespace SAMSErrorHandling
{
    void Initialize(void);
    int HandleNotANumberError(void); // Returns the Error Code
    int HandleRuntimeError(std::runtime_error theRuntimeError);
}

#endif