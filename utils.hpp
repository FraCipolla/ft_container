#ifndef UTILS_HPP
#define UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

static class my_nullptr
{
    public:
        template<class T>
        	operator T*() const { return (0); }
        template<class C, class T>
        	operator T C::*() const { return (0); }

    private:
        void operator&() const;

} u_nullptr = {};

#endif