#pragma once

#include <merkletrees/core/BaseExceptions.hpp>
#include <merkletrees/core/HashValue.hpp>
#include <merkletrees/core/IAlghoritmHash.hpp>
#include <vector>

namespace merkletrees {
namespace core {

class MerkleTree final
{
public:
    struct Element
    {
        explicit Element(const HashValue& value);
        Element(const std::shared_ptr<Element> &left, const std::shared_ptr<Element> &right, const HashValue& value);
        
        std::shared_ptr<Element> m_left;
        std::shared_ptr<Element> m_right;
        HashValue m_hash;
    };
    
public:
    explicit MerkleTree(const std::vector<std::string>& elements, const std::shared_ptr<IAlghoritmHash> &algorithm);
    
    bool IsExist(const std::string& str);
    
private:
    std::vector<std::shared_ptr<Element> > GetHashElements(const std::vector<std::string>& elements);
    std::vector<std::shared_ptr<Element> > GetUpHashElements(const std::vector<std::shared_ptr<Element> >& elements);
    std::shared_ptr<Element> CreateParent(const std::shared_ptr<Element> &left, const std::shared_ptr<Element> &right);
    
private:
    std::shared_ptr<Element> m_root;
    std::shared_ptr<IAlghoritmHash> m_algorithm;
};
    
}
}
