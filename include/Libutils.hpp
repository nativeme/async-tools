#ifndef _LIBUTILS_HPP_
#define _LIBUTILS_HPP_

namespace libutils{
    struct RunCodeBlock{
    template<typename F>
        RunCodeBlock(F&& func){func();};
    };

    template<typename T, typename U>
    constexpr bool same_type = false;
    template<typename T>
    constexpr bool same_type<T, T> = true;
}
#endif
