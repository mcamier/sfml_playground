#ifndef TA_HASH_HPP
#define TA_HASH_HPP

template <unsigned int N, unsigned int I>
struct FnvHash {
  inline static unsigned int hash(const char (&str)[N]) {
    return (FnvHash<N, I - 1>::hash(str) ^ str[I - 1]) * 16777619u;
  }
};

template <unsigned int N>
struct FnvHash<N, 1> {
  inline static unsigned int hash(const char (&str)[N]) {
    return (2166136261u ^ str[0]) * 16777619u;
  }
};

template <unsigned int N>
inline unsigned int makeHash(const char (&str)[N]) {
  return FnvHash<N, N>::hash(str);
}

#endif  // TA_HASH_HPP