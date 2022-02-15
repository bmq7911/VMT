#pragma once
#include <memory>
#include "Frontend/AST/Node.h"
namespace AST {
    template<typename _T>
    class Pair {
    public:
        using left_type = _T;
        using right_type = Pair<_T>;
    public:
        void add(std::shared_ptr<_T>  left) {
            m_left = left;
        }
        void add(std::shared_ptr<Pair<_T>>  right) {
            m_right = right;
        }
        std::shared_ptr<left_type> getLeft() const {
            return m_left;
        }
        std::shared_ptr<right_type> getRight() const {
            return m_right;
        }
        uint32_t gen( uint32_t begin, uint32_t after) {
            return begin;
        }
    private:
        std::shared_ptr<_T>        m_left;
        std::shared_ptr<Pair<_T>>  m_right;
    };
}