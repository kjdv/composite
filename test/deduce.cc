#include <types.hh>
#include "deduce.hh"

using namespace std;

namespace composite {

// this test can be completely done compile time
static_assert(is_same<double, decay_deduce<double>::type>::value, "double does not map to double");
static_assert(is_same<double, decay_deduce<const double &>::type>::value, "double does not map to double");
static_assert(is_same<double, decay_deduce<float>::type>::value, "float does not map to double");
static_assert(is_same<int64_t, decay_deduce<int>::type>::value, "int does not map to int64_t");
static_assert(is_same<int64_t, decay_deduce<char>::type>::value, "char does not map to int64_t");
static_assert(is_same<int64_t, decay_deduce<unsigned>::type>::value, "unsigned does not map to int64_t");
static_assert(is_same<none, decay_deduce<none>::type>::value, "none does not map to none");
static_assert(is_same<none, decay_deduce<void>::type>::value, "void does not map to none");
static_assert(is_same<bool, decay_deduce<bool>::type>::value, "bool does not map to bool");
static_assert(is_same<string, decay_deduce<char []>::type>::value, "char[] does not map to string");
static_assert(is_same<string, decay_deduce<const char *>::type>::value, "const char * does not map to string");
static_assert(is_same<string, decay_deduce<string>::type>::value, "string does not map to string");
static_assert(is_same<sequence, decay_deduce<sequence>::type>::value, "sequence does not map to sequence");
static_assert(is_same<mapping, decay_deduce<mapping>::type>::value, "mapping does not map to mapping");
static_assert(is_same<mapping, decay_deduce<mapping&>::type>::value, "mapping does not map to mapping");
static_assert(is_same<mapping, decay_deduce<const mapping&>::type>::value, "mapping does not map to mapping");

}
