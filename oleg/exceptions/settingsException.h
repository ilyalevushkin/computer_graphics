#ifndef SETTINGSEXCEPTION_H
#define SETTINGSEXCEPTION_H

#include "baseException.h"

class settingsException : public BaseException
{
private:
    static constexpr const char* ErrorMsg = "Error in settings of tree!\n";
public:
    explicit settingsException() : BaseException(ErrorMsg) {}
    explicit settingsException(const std::string& message) : \
        BaseException(ErrorMsg + message) {}
};

#endif // SETTINGSEXCEPTION_H
