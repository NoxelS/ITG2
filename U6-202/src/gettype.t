#ifndef GET_TYPE_T
#define GET_TYPE_T GET_TYPE_T
#include <string>

using std::string;

/** Check if type is a pointer */
template <typename T>
string getPointerStar(T t) {
    return static_cast<string>((std::is_pointer<T>::value ? "*" : ""));
};

/** Das wäre der einfache Weg */
template <typename T>
string getType(T t) {
    return static_cast<string>(typeid(t).name()) + getPointerStar(t);
};

/** Aber eigentlich macht man das mit tempalte spezifikationen...*/
// ...

#endif