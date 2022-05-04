/**
 * @file CodeBlock.hpp
 * @author Łukasz Kaniak - nativeme (lukaszkaniak@gmail.com)
 * @brief 
 * CodeBlock of whatever non blocking code that will be executed along with async::runtime.
 * @version 0.1
 * @date 2022-05-04
 * @copyright Copyright (c) 2022
 */

#ifndef _CODEBLOCK_HPP_
#define _CODEBLOCK_HPP_
#include "Arduino.h"
#include "Runtime.hpp"

namespace async{
/**
 * @brief 
 * CodeBlock of whatever non blocking code that will be executed along with async::runtime.
 */
class CodeBlock
: ILoopable
{
private:
    const std::function<void(void)> codeblock;
public:
    CodeBlock(){};
    template<typename Lambda>
    CodeBlock(const Lambda&& codeblock)
    :   codeblock(codeblock)
    {
        async::Runtime::loopables.push_back(this);
    };
    virtual ~CodeBlock() override {};
    virtual void loop() override {
        this->codeblock();
    };
};
}
#endif
