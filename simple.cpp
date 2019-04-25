#include <gtest/gtest.h>


//https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.cbclx01/variadic_templates.htm

#include <functional>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <iostream>
#include <array>
#include <type_traits>
 
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

TEST(TypeInfo,eq)
{
  Header A;
const std::type_info& ti1 = typeid(A);
const std::type_info& ti2 = typeid(Header);


 EXPECT_TRUE(ti1.hash_code() == ti2.hash_code()); // guaranteed
EXPECT_TRUE(std::type_index(ti1) == std::type_index(ti2)); // guaranteed 
}

struct Base {}; // non-polymorphic
struct Derived : Base {};
 
struct Base2 { virtual void foo() {} }; // polymorphic
struct Derived2 : Base2 {};

TEST(TypeInfo,Base)
{
    int myint = 50;
    std::string mystr = "string";
    double *mydoubleptr = nullptr;
 
    std::cout << "myint has type: " << typeid(myint).name() << '\n'
              << "mystr has type: " << typeid(mystr).name() << '\n'
              << "mydoubleptr has type: " << typeid(mydoubleptr).name() << '\n';
 
    // std::cout << myint is a glvalue expression of polymorphic type; it is evaluated
    const std::type_info& r1 = typeid(std::cout << myint);
    std::cout << '\n' << "std::cout<<myint has type : " << r1.name() << '\n';
 
    // std::printf() is not a glvalue expression of polymorphic type; NOT evaluated
    const std::type_info& r2 = typeid(std::printf("%d\n", myint));
    std::cout << "printf(\"%d\\n\",myint) has type : " << r2.name() << '\n';
 
    // Non-polymorphic lvalue is a static type
    Derived d1;
    Base& b1 = d1;
    std::cout << "reference to non-polymorphic base: " << typeid(b1).name() << '\n';
 
    Derived2 d2;
    Base2& b2 = d2;
    std::cout << "reference to polymorphic base: " << typeid(b2).name() << '\n';
 
    try {
        // dereferencing a null pointer: okay for a non-polymorphic expression
        std::cout << "mydoubleptr points to " << typeid(*mydoubleptr).name() << '\n'; 
        // dereferencing a null pointer: not okay for a polymorphic lvalue
        Derived2* bad_ptr = nullptr;
        std::cout << "bad_ptr points to... ";
        std::cout << typeid(*bad_ptr).name() << '\n';
    } catch (const std::bad_typeid& e) {
         std::cout << " caught " << e.what() << '\n';
    }

   Derived* pd = new Derived;
   Base* pb = pd;
   std::cout << typeid( pb ).name() << std::endl;   //prints "class Base *"
   std::cout << typeid( *pb ).name() << std::endl;   //prints "class Derived"
   std::cout << typeid( pd ).name() << std::endl;   //prints "class Derived *"
   std::cout << typeid( *pd ).name() << std::endl;   //prints "class Derived"
   delete pd;
}