#ifndef _IASYNCFUNCTION_HPP_
#define _IASYNCFUNCTION_HPP_

namespace async{

class IAsyncFunction
{
private:
    
public:
    int id = 0;
    uint8_t state = 0;

    IAsyncFunction(){};
    virtual ~IAsyncFunction(){};
    
    virtual int new_id(){
        static int id_counter = 0;
        return id_counter++;
    }

    virtual void loop() = 0;
};
}
#endif