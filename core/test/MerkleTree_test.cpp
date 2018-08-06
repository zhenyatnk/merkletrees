#include <merkletrees/core/MerkleTree.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//--------------------------------------------------
using namespace merkletrees::core;
using namespace testing;

class MockIAlghoritmHash
  : public IAlghoritmHash
{
public:
    MOCK_CONST_METHOD1(Hash, HashValue(const std::string &));
    MOCK_CONST_METHOD2(Concat, HashValue(const HashValue &,const HashValue &));
};

class MerkleTree_test
    :public ::testing::Test
{
public:
    void SetUp()
    {
        m_MockAlghoritm = std::make_shared<NiceMock<MockIAlghoritmHash> >();
    }
    
protected:
    std::shared_ptr<MockIAlghoritmHash> m_MockAlghoritm;
};

TEST_F(MerkleTree_test, ctor_empty)
{
    ASSERT_NO_THROW(MerkleTree({}, m_MockAlghoritm));
}

TEST_F(MerkleTree_test, ctor_double)
{
    EXPECT_CALL(*m_MockAlghoritm, Hash(_)).Times(3);
    EXPECT_CALL(*m_MockAlghoritm, Concat(_,_)).Times(1);
    MerkleTree({"test", "test2"}, m_MockAlghoritm);
}

TEST_F(MerkleTree_test, ctor_triple)
{
    EXPECT_CALL(*m_MockAlghoritm, Hash(_)).Times(6);
    EXPECT_CALL(*m_MockAlghoritm, Concat(_,_)).Times(3);
    MerkleTree({"test", "test2", "test3"}, m_MockAlghoritm);
}

TEST_F(MerkleTree_test, IsExist_Found)
{
    EXPECT_CALL(*m_MockAlghoritm, Hash(_))
    .WillRepeatedly(
    Invoke([](const std::string &str)
    {
        HashValue hash;
        for(const auto& symbol : str)
            hash.m_data += symbol;
        return hash;
    }));
    
    EXPECT_CALL(*m_MockAlghoritm, Concat(_,_))
    .WillRepeatedly(
    Invoke([](const HashValue &l,const HashValue &r)
    {
        HashValue hash;
        hash.m_data = l.m_data + r.m_data;
        return hash;
    }));
    
    MerkleTree tree({"test", "test2", "test3"}, m_MockAlghoritm);
    
    ASSERT_EQ(true, tree.IsExist("test"));
}

TEST_F(MerkleTree_test, IsExist_NotFound)
{
    EXPECT_CALL(*m_MockAlghoritm, Hash(_))
    .WillRepeatedly(
    Invoke([](const std::string &str)
           {
               HashValue hash;
               for(const auto& symbol : str)
                   hash.m_data += symbol;
               return hash;
           }));
    
    EXPECT_CALL(*m_MockAlghoritm, Concat(_,_))
    .WillRepeatedly(
    Invoke([](const HashValue &l,const HashValue &r)
           {
               HashValue hash;
               hash.m_data = l.m_data + r.m_data;
               return hash;
           }));
    
    MerkleTree tree({"test", "test2", "test3"}, m_MockAlghoritm);
    
    ASSERT_EQ(false, tree.IsExist("test12"));
}

TEST_F(MerkleTree_test, IsExist_InEmpty)
{
    EXPECT_CALL(*m_MockAlghoritm, Hash(_))
    .WillRepeatedly(
                    Invoke([](const std::string &str)
                           {
                               HashValue hash;
                               for(const auto& symbol : str)
                                   hash.m_data += symbol;
                               return hash;
                           }));
    
    EXPECT_CALL(*m_MockAlghoritm, Concat(_,_))
    .WillRepeatedly(
                    Invoke([](const HashValue &l,const HashValue &r)
                           {
                               HashValue hash;
                               hash.m_data = l.m_data + r.m_data;
                               return hash;
                           }));
    
    MerkleTree tree({}, m_MockAlghoritm);
    
    ASSERT_EQ(false, tree.IsExist("test12"));
}

