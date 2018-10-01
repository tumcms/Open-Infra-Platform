#ifndef SKELETON_HPP
#define SKELETON_HPP

#include <tuple>

#define MEMBERS(...)    enum { __VA_ARGS__ };

#define TEMPLATE_GENERATION(NAME, DATA)                                                        \
    template <typename ... Args>                                                            \
    struct NAME##_Skelaton : public Entity_Skelaton<Args...>                                \
    {                                                                                        \
        MEMBERS(DATA)                                                                        \
        NAME##_Skelaton(Args ... args) : Entity_Skelaton<Args...>(args...) {}                \
    };            

struct Skelaton_Base
{
    virtual void f()  = 0;
};

template <typename ... Args>
struct Entity_Skelaton : public Skelaton_Base
{
    std::tuple<Args...> items;

    void f() {}

    Entity_Skelaton(Args... args)
    {
        items = std::make_tuple(args...);
    }

    template <int index>
    auto return_data_member() -> decltype(std::get<index>(items))
    {
        return std::get<index>(items);
    }
};
#endif
