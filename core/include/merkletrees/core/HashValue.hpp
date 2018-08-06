#pragma once

#include <merkletrees/core/BaseExceptions.hpp>
#include <string>

namespace merkletrees {
namespace core {
    
struct HashValue
{
    bool operator==(const HashValue& right) const
    {
        return m_data == right.m_data;
    }
    
    std::string m_data;
};

}
}
