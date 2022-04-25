#ifndef _CEASYSTRATEGY_H_
#define _CEASYSTRATEGY_H_
#include <string>
#include "CStrategy.h"

class CEasyStrategy : public CStrategy {
public:
    std::string m_sInputStr;
public:
    virtual int getFileAbsPath() override;
    virtual void Init(std::string input) override;
};


#endif

