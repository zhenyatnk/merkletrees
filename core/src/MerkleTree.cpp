#include <merkletrees/core/BaseExceptions.hpp>
#include <merkletrees/core/MerkleTree.hpp>
#include <memory>

namespace merkletrees {
namespace core {
namespace
{
bool HashExist(const HashValue& hash, const std::shared_ptr<MerkleTree::Element>& root)
{
    if(!root->m_left && !root->m_right)
        return hash == root->m_hash;
    
    if(!!root->m_left)
        if(HashExist(hash, root->m_left))
            return true;
    if(!!root->m_right)
        if(HashExist(hash, root->m_right))
            return true;
    return false;
}
}
//////////////////////////////////////////////////////
MerkleTree::Element::Element(const HashValue& value)
:m_hash(value)
{ }
    
MerkleTree::Element::Element(const std::shared_ptr<Element> &left, const std::shared_ptr<Element> &right, const HashValue& value)
:m_left(left), m_right(right), m_hash(value)
{}
 
//////////////////////////////////////////////////////
MerkleTree::MerkleTree(const std::vector<std::string>& elements, const std::shared_ptr<IAlghoritmHash> &algorithm)
    :m_algorithm(algorithm)
{
    auto merkelTop = GetUpHashElements(GetHashElements(elements));
    m_root = merkelTop.empty() ? nullptr: merkelTop.front();
}
    
std::vector<std::shared_ptr<MerkleTree::Element> > MerkleTree::GetHashElements(const std::vector<std::string>& elements)
{
    std::vector<std::shared_ptr<MerkleTree::Element> > result;
    for (const auto& element : elements)
    {
        auto hash = m_algorithm->Hash(element);
        result.push_back(std::make_shared<MerkleTree::Element>(hash));
    }
    return result;
}

std::vector<std::shared_ptr<MerkleTree::Element> > MerkleTree::GetUpHashElements(const std::vector<std::shared_ptr<MerkleTree::Element> >& elements)
{
    std::vector<std::shared_ptr<MerkleTree::Element> > hashs;
    auto index = 0;
    auto sizeElements = elements.size();
    while (index < sizeElements)
    {
        if(index + 1 < sizeElements)
            hashs.push_back(CreateParent(elements[index], elements[index + 1]));
        else
            hashs.push_back(CreateParent(elements[index], std::make_shared<MerkleTree::Element>(elements[index]->m_hash)));
        index += 2;
    }
    
    if(hashs.size() > 1)
        return GetUpHashElements(hashs);
    return hashs;
}
    
std::shared_ptr<MerkleTree::Element> MerkleTree::CreateParent(const std::shared_ptr<MerkleTree::Element> &left, const std::shared_ptr<MerkleTree::Element> &right)
{
    auto hash = m_algorithm->Hash(m_algorithm->Concat(left->m_hash, right->m_hash).m_data);
    return std::make_shared<MerkleTree::Element>(left, right, hash);
}
    
bool MerkleTree::IsExist(const std::string& str)
{
    if(!m_root)
        return false;
    return HashExist(m_algorithm->Hash(str), m_root);
}
    
}
}
