#ifndef TA_MSG_HPP
#define TA_MSG_HPP

#define CREATE

namespace ta {

typedef unsigned int messageType_t;

struct variant {
  enum class type_t { INT_T, UINT_T, FLOAT_T, DOUBLE_T, BOOL_T };

  type_t type;

  union {
    int intValue;
    unsigned int uintValue;
    float floatValue;
    double doubleValue;
    bool boolValue;
  };
};

struct message {
  messageType_t type = 0;
  variant v0;
  variant v1;
  variant v2;
  variant v3;
  variant v4;
  variant v5;
  variant v6;
  variant v7;
  variant v8;
  variant v9;
};

}  // namespace ta

#endif  // TA_MSG_HPP