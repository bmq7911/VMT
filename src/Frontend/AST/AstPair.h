#pragma once
#include <memory>
namespace AST {
    template<typename _T>
    class AstPair {
    public:
        using left_type = _T;
        using right_type = AstPair<_T>;
    public:
        void add(std::shared_ptr<_T>  left) {
            if( !m_left )
                m_left = left;
            else {
                m_right = std::make_shared<AstPair<_T>>();
                m_right->add(left);
            }
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
        std::shared_ptr<AstPair<_T>>  m_right;
    };
}