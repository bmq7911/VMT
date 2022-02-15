#include <stdio.h>
#include <iostream>
#include <stack>
#include "ADT/graphs.h"

int main( int argc, char * argv[]) {

    ADT::adjacency_list<std::set, std::string, std::string > g;
    ADT::vertex<std::string>* v0 = g.add_vertex("hello world");
    ADT::vertex<std::string>* v1 = g.add_vertex("hello world11");
    g.add_edge(v0, v1, "this is a test");
    g.add_edge(v0, v1, "this is b test"); /// 可以加重复边就存在问题,我们要去掉重复边

    ADT::adjacency_list<std::set, std::string, std::string>::const_edgeIterator begin = static_cast<ADT::adjacency_list<std::set, std::string, std::string> const&>(g).edgeBegin(v0);
    ADT::adjacency_list<std::set, std::string, std::string>::const_edgeIterator end   = static_cast<ADT::adjacency_list<std::set, std::string, std::string>const&>(g).edgeEnd(v0);
    
    for (; begin != end; ++begin) {
        std::cout << "begin != end" << std::endl;
        std::cout << begin->src()->data() << "->" << begin->dst()->data() << std::endl;
        std::cout << begin->data() << std::endl;
    }

    std::cout << "hello World" << std::endl;

}
