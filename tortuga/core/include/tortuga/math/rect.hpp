#ifndef FOOBAR_RECT_HPP
#define FOOBAR_RECT_HPP

namespace ta::core {

template<typename T>
class rect {
public:
    T x;
    T y;
    T h;
    T w;

    rect() : x(0), y(0), w(0), h(0) {}

    rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}

    rect(const rect& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}

};

typedef rect<int> recti;
typedef rect<float> rectf;
typedef rect<double> rectd;

}  // namespace ta

#endif  // FOOBAR_RECT_HPP
