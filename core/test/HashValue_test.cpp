#include <merkletrees/core/HashValue.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace merkletrees::core;

class HashValue_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(HashValue_test, eq_noteq1)
{
    HashValue value1; value1.m_data = "test1";
    HashValue value2; value2.m_data = "test2";
    
    ASSERT_EQ(false , value1 == value2);
}

TEST_F(HashValue_test, eq_noteq2)
{
    HashValue value1; value1.m_data = "test1";
    HashValue value2; value2.m_data = "tEst2";
    
    ASSERT_EQ(false , value1 == value2);
}

TEST_F(HashValue_test, eq_noteq3)
{
    HashValue value1; value1.m_data = "test1";
    HashValue value2; value2.m_data = "";
    
    ASSERT_EQ(false , value1 == value2);
}

TEST_F(HashValue_test, eq_eq1)
{
    HashValue value1; value1.m_data = "test1";
    HashValue value2; value2.m_data = "test1";
    
    ASSERT_EQ(true , value1 == value2);
}

TEST_F(HashValue_test, eq_eq2)
{
    HashValue value1; value1.m_data = "";
    HashValue value2; value2.m_data = "";
    
    ASSERT_EQ(true , value1 == value2);
}
