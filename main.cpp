#include "stack.hpp"
// #include "vector.hpp"
// #include "random_access_iterator.hpp"
// #include "reverse_iterator.hpp"
// #include "utils.hpp"
// #include <vector>
#include <iostream>

using namespace ft;

int main()
{
	stack<int>  st;

    std::cout << "Empty:" << (st.empty() ? "true" : "false") << std::endl;
    st.push(34);
    std::cout << "Size:" << st.size() << std::endl;
    std::cout << "Empty:" << (st.empty() ? "true" : "false") << std::endl;
    std::cout << "Top:" << st.top() << std::endl;

}