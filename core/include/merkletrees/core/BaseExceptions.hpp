#pragma once

#include <merkletrees/core/export.hpp>
#include <stdexcept>

namespace merkletrees {
namespace core {
namespace exceptions_base {

class MERKLETREES_CORE_EXPORT merkletrees_error_base
    :public std::runtime_error
{
public:
    merkletrees_error_base(const std::string &aMessage, const int &aErrorCode)
        :runtime_error(aMessage), m_ErrorCode(aErrorCode)
    {}

    int GetErrorCode() const
    {
        return m_ErrorCode;
    }

private:
    int m_ErrorCode;
};

}
}
}
