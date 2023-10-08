//
// Created by Yang Jerry on 2022/3/30.
//

#include <string>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-macro-parentheses"

#ifndef SEULEXYACC_UTILS_H
#define SEULEXYACC_UTILS_H
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <sstream>
#include <functional>

// #include <concepts>

using namespace std;

namespace sly::utils{

#define FMAP_DECL(functor, method) \
template<typename T> \
functor<T> fmap(const functor<T>& container, std::function<T(const T&)> f) \
{ \
  functor<T> result; \
  for (const T& elem: container) \
  { \
    result.method(f(elem)); \
  } \
  return result;\
}

FMAP_DECL(std::set, emplace)

FMAP_DECL(std::vector, push_back)

template<typename T1, typename T2>
std::map<T1, T2>
fmap(const std::map<T1, T2> &container, std::function<std::pair<T1, T2>(const std::pair<T1, T2> &)> f) {
  std::map<T1, T2> result;
  for (const std::pair<T1, T2> &elem: container) {
    result.insert(f(elem));
  }
  return result;
}


template<typename T>
set<T> fixed_point(set<T> set0, function<set<T>(T)> f) {
  while (true) {
    auto set1 = set0;
    for_each(set0.begin(), set0.end(), [&set1, &f](const auto &v) {
      set1.merge(f(v));
    });
    if (set0 == set1)
      break;
    else
      set0 = set1;
  }
  return set0;
}

class Log {
 public:
  enum LogLevel {
    kInfo = 0, kWarning = 1, kError = 2, kNone = 3
  } level;
  
  
  inline static const Log &GetGlobalLogger();
  
  template<typename ...T>
  void Info(const T &... args) const;
  
  template<typename ...T>
  void Warn(const T &... args) const;
  
  template<typename... T>
  void Err(const T &... args) const;

  static inline void SetLogLevel(LogLevel level);
 
 
 private:
  
  inline static Log &GetGlobalLoggerPrivate();
  template<typename T>
  void Put(ostream &os, T arg) const;
};


template<typename T>
void Log::Put(ostream &os, T arg) const {
  os << arg;
}

template<typename... T>
void Log::Info(const T &... args) const {
  if (level > kInfo)
    return;
  Put(cout, "Info: ");
  int arr[] = {(Put(cout, args), 0)...};
  Put(cout, "\n");
}

template<typename... T>
void Log::Warn(const T &... args) const {
  if (level > kWarning)
    return;
  Put(cout, "Warning: ");
  int arr[] = {(Put(cout, args), 0)...};
  Put(cout, "\n");
}

template<typename... T>
void Log::Err(const T &... args) const {
  if (level > kError)
    return;
  Put(cerr, "Error: ");
  int arr[] = {(Put(cerr, args), 0)...};
  Put(cerr, "\n");
};

inline const Log &Log::GetGlobalLogger() {
  return GetGlobalLoggerPrivate();
}


inline Log &Log::GetGlobalLoggerPrivate() {
  static Log log;
  return log;
}


inline void Log::SetLogLevel(LogLevel level) {
  GetGlobalLoggerPrivate().level = level;
}


inline size_t hash_combine(size_t h1, size_t h2) {
  return h1 ^ (h2 << 1);
}

template<typename T>
size_t hash(const T& v) {
  return std::hash<T>{}(v);
}

template<typename T, typename ... Args>
size_t hash(const T &v, const Args &... args) {
  size_t v1 = std::hash<T>{}(v);
  size_t v2 = sly::utils::hash(args...);
  return hash_combine(v1, v2);
}


struct ToString{
  stringstream ss;
  using type = std::string;
  template<typename T>
  typename enable_if<!is_class<T>::value, type>::type
  operator()(const T &v) {
    ss << v;
    return ss.str();
  }

private:
  type __reduce(const type& h) const { return h; }
  type __combine(const type& l, const type& r) const { 
    return l + "," + r;
  }
  template<typename ... SZ>
  type __reduce(const type& h, const SZ&...args) const {
    return __combine(h, __reduce(args...));
  }

  template <typename T>
  type comb(const T &t) const { 
    return  ToString{}(t);
  }

  template <typename T, typename... Args>
  type comb(const T &t, const Args &...args) const {
    return __reduce(ToString{}(t), comb(args...));
  }

public:
  template <typename T1, typename T2, typename... Args>
  type operator()(const T1 &t1, const T2 &t2, const Args &...args) {
    return "<"+comb(t1, t2, args...)+">";
  }

  template <typename L, typename R>
  type operator()(const pair<L, R> p) const {
    return "<"+comb(p.first, p.second)+">";
  }

  template <typename I, typename C = typename I::const_iterator>
  type operator()(const I &it) const {
    string hv = "";
    for (const auto& i: it) {
      hv = hv + ToString{}(i) + ",";
    }
    return "[" + hv + "]";
  }

  type operator()(const vector<bool> &bs) const {
    string hv = "";
    for (int i = 0; i < bs.size(); ++i) {
      hv = ToString{}((int)bs[i]) + ",";
    }
    return "[" + hv + "]";
  }

  template <typename... Args> size_t operator()(const tuple<Args...> &tup) {
    return apply([](Args... v) -> size_t { return ToString{}.comb<Args...>(v...); },
                 tup);
  }
  template <
      typename ToStringable,
      typename = is_same<decltype(std::declval<ToStringable>().ToString()), string>>
  string operator()(const ToStringable &v) {
    return v.ToString();
  }
};


////////////////////// MY HASH //////////////////////
struct Hash {
  template <typename T>
  typename enable_if<!is_class<T>::value, size_t>::type
  operator()(const T &v) const {
    return std::hash<T>{}(v);
  }

private:
  size_t __hash_reduce(size_t h) const { return h; }
  size_t __hash_combine(size_t l, size_t r) const { return (l << 1) ^ r; }
  template<typename ... SZ>
  size_t __hash_reduce(size_t h, SZ ... t) const {
    return Hash::__hash_combine(h, __hash_reduce(t...));
  }

  template <typename T> size_t comb(const T &t) const { return Hash{}(t); }

  template <typename T, typename... Args>
  size_t comb(const T &t, const Args &...args) const {
    return __hash_reduce(Hash{}(t), comb(args...));
  }

public:
  template <typename T1, typename T2, typename... Args>
  size_t operator()(const T1 &t1, const T2 &t2, const Args &...args) {
    return comb(t1, t2, args...);
  }

  template <typename L, typename R>
  size_t operator()(const pair<L, R> p) const {
    return Hash{}(p.first, p.second);
  }

  template <typename I, typename C = typename I::const_iterator>
  size_t operator()(const I &it) const {
    size_t hv = 0;
    for (const auto &v : it) {
      hv = __hash_combine(hv, Hash{}(v));
    }
    return hv;
  }
  size_t operator()(const vector<bool> &bs) const {
    size_t hv = 0;
    for (int i = 0; i < bs.size(); ++i) {
      hv = __hash_combine(hv, Hash{}((int)bs[i]));
    }
    return hv;
  }

  template <typename... Args> size_t operator()(const tuple<Args...> &tup) {
    return apply([](Args... v) -> size_t { return Hash{}.comb<Args...>(v...); },
                 tup);
  }
  template <
      typename Hashable,
      typename = is_same<decltype(std::declval<Hashable>().hash()), size_t>>
  size_t operator()(const Hashable &v) {
    return v.hash();
  }
};
////////////////////// MY HASH //////////////////////



// #define FUNC_END_INFO sly::utils::Log::GetGlobalLogger().Info(__FILE__, __LINE__, __FUNCTION__, "Done.")

// #define FUNC_START_INFO sly::utils::Log::GetGlobalLogger().Info(__FILE__, __LINE__, __FUNCTION__, "Start.")

#ifndef NDEBUG
#define FUNC_END_INFO spdlog::debug("{} {} {} {}",__FILE__, __LINE__, __FUNCTION__, "Done.")
#define FUNC_START_INFO spdlog::debug("{} {} {} {}",__FILE__, __LINE__, __FUNCTION__, "Start.")
#else
#define FUNC_END_INFO
#define FUNC_START_INFO
#endif


template<typename T>
std::string to_string(const T& v) {
  stringstream ss;
  ss << v;
  return ss.str();
}

inline void ltrim(std::string &str, const string &val = " \r\n\0") {
  str.erase(0, str.find_first_not_of(val));
}

inline void rtrim(std::string &str, const string &val = " \r\n\0") {
  str.erase(str.find_last_not_of(val) + 1);
}

inline void trim(std::string &str, const string &val = " \r\n\0") {
  ltrim(str, val);
  rtrim(str, val);
}

inline void replace_all(std::string &str, const std::string &from, const std::string &to) {
  for (std::string::size_type pos = str.find(from); 
       pos != std::string::npos; 
       pos = str.find(from)) {
    str.replace(pos, from.length(), to);
  }
}

inline std::string escape(const std::string &str) {
  std::string res = str;
  replace_all(res, "\t", "\\t");
  
  replace_all(res, "\r", "\\r");
  replace_all(res, "\n", "\\n");
  return res;
}
} // namespace sly::utils

#endif //SEULEXYACC_UTILS_H

#pragma clang diagnostic pop
