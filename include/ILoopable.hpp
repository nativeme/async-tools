#ifndef _ILOOPABLE_HPP_
#define _ILOOPABLE_HPP_

namespace async{

class ILoopable
{
private:
    
public:
    ILoopable(){};
    virtual ~ILoopable(){};
    virtual void loop() = 0;
};
}
#endif
