#ifndef FOOBAR_EVENT_HPP
#define FOOBAR_EVENT_HPP

namespace ta {

enum class event_type {
  keyUp,
  keyDown,
  mouseMove,
  MouseWheel,
  MouseClick,
};

struct variant {
  enum class type_t { INT_T, FLOAT_T, DOUBLE_T, BOOL_T };

  type_t type;

  union {
    int intValue;
    float floatValue;
    bool boolValue;
  };
};

struct event {
  event_type type;
  variant v1;
  variant v2;
  variant v3;
  variant v4;
  variant v5;
  variant v6;
  variant v7;
  variant v8;
  variant v9;
  variant v10;
  variant v11;
  variant v12;
};

}  // namespace ta

#endif