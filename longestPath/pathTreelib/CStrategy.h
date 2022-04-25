#ifndef _CPATHSTRATEGY_H_
#define _CPATHSTRATEGY_H_

class CStrategy {
public:
    virtual ~CStrategy() {}
    virtual int getFileAbsPath() = 0;
    virtual void Init(std::string input) = 0;
};


#endif

