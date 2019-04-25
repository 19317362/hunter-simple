#include <gtest/gtest.h>


//https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/variadic_templates.htm

#include <functional>
#include <memory>


// #include <iostream>
// #include <array>
// #include <type_traits>
 
// template<typename... Ts>
// constexpr auto make_array(Ts&&... ts)
//     -> std::array<std::common_type_t<Ts...>,sizeof...(ts)>
// {
//     return { std::forward<Ts>(ts)... };
// }

template <class... Pack>
void store_pack(Pack... p) {
    std::tuple<Pack...> store( p... );
    std::cout<<std::get<2>(store)<<std::endl;
}

//https://stackoverflow.com/questions/15953139/get-the-nth-type-of-variadic-template-templates/15953673
template<typename... Args>
class MyClass
{
    typename std::tuple_element<0, std::tuple<Args...> >::type mA;
};

template<unsigned int index, unsigned int In, unsigned int... remPack> struct getVal
{
    static const unsigned int val = getVal<index-1, remPack...>::val;
};
template<unsigned int In, unsigned int...remPack> struct getVal<0,In,remPack...>
{
    static const unsigned int val = In;
};

template<unsigned int... T> struct MyClass2
{
    //go to any arg by : getVal<Some_Unsigned_Index, T...>::val;
};



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
  std::cout<<"Cnt:" << sizeof...(args) <<" No.1" 
    //<< std::get<1>(args...) 
    <<std::endl;

  vl_hdr.Print(std::forward<Args>(args)...);
  vl_hdr.Print2(std::forward<Args>(args)...);
  //return vl_hdr;
} 


// This function will obtain a reference to the parameter 'r' and increment it.
void func (int &r)  { r++; }

// Template function.
template<class F, class P> void g (F f, P t)  { f(t); }

int t00_main()
{
    int i = 0;
    g (func, i); // 'g<void (int &r), int>' is instantiated
                 // then 'i' will not be modified.
    std::cout << i << std::endl; // Output -> 0

    g (func, std::ref(i)); // 'g<void(int &r),reference_wrapper<int>>' is instantiated
                           // then 'i' will be modified.
    std::cout << i << std::endl; // Output -> 1
    return 0;
}


TEST(Simple, simple) {

    //   auto b = make_array(1, 2, 3);
    // std::cout << b.size() << '\n';
    // for (auto i : b)
    //     std::cout << i << ' ';

  auto ptr = std::make_shared<Header>();
  ptr->Dump();

  call_test("123",5);
  store_pack("123",1,2.1,3.4,5.6);
  ASSERT_EQ(1 + 1, 2);
}
