#include "ADT/graphs.h"
#include <iostream>
#include "gtest/gtest.h"
#include "ADT/graphs_algorithm.h"

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
        auto v3 = g.add_vertex();
        g.add_edge(v1, v2);
        g.add_edge(v1, v3);
        auto startVertex = ADT::graph::get_start_vertex(g);
        auto endVertex   = ADT::graph::get_end_vertex(g);
        EXPECT_EQ(1, startVertex.size());
        EXPECT_EQ(2, endVertex.size());
        g.add_edge(v2, v3);
        endVertex = ADT::graph::get_end_vertex(g);
        EXPECT_EQ(1, endVertex.size());
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