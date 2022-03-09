#include "ADT/graphs.h"
#include <iostream>
#include "gtest/gtest.h"

class vertex {
public:
    vertex() {
        std::cout << "vertex::vertex()" << std::endl;
    }
    vertex(vertex const& v) {
        std::cout << "vertex::vertex(vertex const&v)" << std::endl;
    }
    ~vertex() {
        std::cout << "vertex::~vertex()" << std::endl;
    }
};
class edge {
public:
    edge() {
        std::cout << "edge::edge()" << std::endl;
    }
    edge(edge const& v) {
        std::cout << "edge::edge(edge const&e)" << std::endl;
    }
    ~edge() {
        std::cout << "edge::~edge()" << std::endl;
    }
};




int main( int argc, char *argv[]) {
    {
        using G = ADT::graph::adjacency_list<vertex, edge>;
        G g;
        auto v1 = g.add_vertex();
        auto v2 = g.add_vertex();
        ADT::graph::__detail::__Link(v1, v2);

        G g1(g);
    }
    std::cout << "*************************************" << std::endl;
    {
        using G = ADT::graph::adjacency_list<vertex>;
        G g;
        auto v1 = g.add_vertex();
        auto v2 = g.add_vertex();

        ADT::graph::__detail::__Link(v1, v2);
        G g1(g);
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS( );
}