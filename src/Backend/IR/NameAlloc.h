#pragma once
#include <atomic>
#include <set>
#include <string>

namespace IR {

    /// <summary>
    /// 1.����3������
    /// 1.1 ����������, ����ĸ,�»��߿�ͷ,������ֻ�����»���;����ĸ,�»���,���������,���к����ɸ�@����չ����,������ʹ�����ƴ����ظ�ʱ
    /// 1.2 δ��������, ȫδ����
    /// 1.3 �ڽ�����,�� "." ��ʼ,��ĸ,����,�»������,���������ɾ�����������,������IR֮��ʹ��
    /// </summary>
    class NameAlloc {
    public:
        NameAlloc()
            : m_temporaryId(0 )
            , m_allocedIndex( 0 )
        {
        }

        std::string allocTemporaryName() {
            uint32_t id = m_temporaryId.load();
            do {
                if (true == m_temporaryId.compare_exchange_strong(id, id+1)) {
                    //std::string name = std::string("%") +std::to_string(id);
                    std::string name = std::to_string(id);
                    m_allocedName.insert(name);
                    return name;
                }
                else {
                    id = m_temporaryId.load();
                }
            } while (true);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        std::string allocName(const char* name) {
            if (nullptr == name) {
                return allocTemporaryName();
            }

            if ( !_IsFullNum(name)) {
                return "";
            }
            return _AllocName( name );

        }
    private:
        bool _IsFullNum(const char* name) {
            size_t i = 0;
            char ch = char(0);
            for ( ch = name[0]; ch != char(0); name ++, ch = *name) {
                if (!('0' <= ch && ch <= '9')) {
                    return true;
                }
            }
            return false;
        }
        std::string _AllocNamedName(std::string const& name) {
            if (false == _CheckIsRightNamedName(name)) {
                return std::string();
            }
            else {
                   
            }
        }

        bool _CheckIsRightNamedName(std::string const& name) const {
            if (name.empty()) {
                return false;
            }
            else {
                if (std::isalpha(name[0]) || '_' == name[0]) {
                    if (true == _IsIncludeInvalidAlpha(name)) {
                        return false;
                    }
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        bool _IsIncludeInvalidAlpha( std::string const& name  ) const {
            for (size_t i = 0; i < name.length(); ++i) {
                if ( !(std::isalnum(name[i]) || '_' == name[i]) ){
                    return true;
                }
            }
            return false;
        }
        std::string _AllocName(std::string const& name ) {
            auto strFixName = name;
            auto iter = m_allocedName.find(strFixName);
            if (iter == m_allocedName.end()) {
                m_allocedName.insert(strFixName);
                return strFixName;
            }
            else {
                std::string tName = name;
                while ((tName = name + _GetRandomSuffix(), iter = m_allocedName.find( tName), iter != m_allocedName.end() ));
                m_allocedName.insert(tName);
                return tName;
            }
        }

        std::string _GetRandomSuffix() {
            std::string name("#");
            //auto iter = m_allocedName.find(name)            
            uint32_t id = m_allocedIndex.load();
            do {
                if (true == m_allocedIndex.compare_exchange_strong(id, id + 1)) {
                    name +=  std::to_string(id);
                    m_allocedIndex++;
                    m_allocedName.insert(name);
                    return name;
                }
                else {
                    id = m_allocedIndex.load();
                }
            } while (true);;
        }
    private:
        std::atomic<uint32_t>  m_temporaryId;
        std::atomic<uint32_t>  m_allocedIndex;
        std::set<std::string > m_allocedName;
    };
}