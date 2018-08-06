#pragma once

#include <merkletrees/core/BaseExceptions.hpp>
#include <merkletrees/core/HashValue.hpp>
#include <string>

namespace merkletrees {
namespace core {
    
class IAlghoritmHash
{
public:
    virtual ~IAlghoritmHash() = default;
    
    virtual HashValue Hash(const std::string &value) const = 0;
    virtual HashValue Concat(const HashValue &left, const HashValue &right) const = 0;
};
    
}
}
