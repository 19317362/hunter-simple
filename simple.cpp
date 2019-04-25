#include <gtest/gtest.h>

#include <functional>
#include <memory>

class Header
{
  public:
    int m_cnt;
    std::string m_name;
  public:
    void Dump()
    {
        std::cout<<"name:"<<m_name<<"  Cnt:"<<m_cnt<<std::endl;
    }
    Header()
    {

    }
    void Print(const std::string& name,int cnt)
    {
      m_name = name;
      m_cnt = cnt;

      Dump();
    }

    template <typename TReqBody,typename TAckBody> 
    void Print2(const TReqBody& reqBody,const TAckBody& ackBody)
    {
      m_name = reqBody;
      m_cnt = ackBody;

      Dump();

    }
    ~Header()
    {

    }
};



template < typename... Args>
void call_test(Args&&... args  )
{
  Header vl_hdr;
  std::cout<<"Cnt:" << sizeof...(args) <<std::endl;
  vl_hdr.Print(std::forward<Args>(args)...);
  vl_hdr.Print2(std::forward<Args>(args)...);
  //return vl_hdr;
} 



TEST(Simple, simple) {
  auto ptr = std::make_shared<Header>();
  ptr->Dump();

  call_test("123",5);

  ASSERT_EQ(1 + 1, 2);
}
