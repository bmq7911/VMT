#pragma once
#include "Frontend/AST/Node.h"
#include "Frontend/AST/Function.h"
#include "Frontend/AST/Structure.h"
#include "Frontend/AST/Pair.h"
#include "Frontend/AST/TopElement.h"

namespace AST {
    class Program : public std::enable_shared_from_this<Program>,public Node {
    public:
        void addTopElement( std::shared_ptr<TopElement> top) {
            std::shared_ptr<AST::Pair<TopElement>> pair = std::make_shared<AST::Pair<TopElement>>();
            pair->add(top);
            pair->add(m_top);
            m_top = pair;
        }
        std::shared_ptr<AST::Pair<TopElement>> getTop() {
            return m_top;
        }
    private:
        std::shared_ptr<AST::Pair<TopElement>> m_top;
    };
}