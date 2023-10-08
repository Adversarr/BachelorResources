//
// Created by Yang Jerry on 2022/3/30.
//

#ifndef SEULEXYACC_ATTRDICT_H
#define SEULEXYACC_ATTRDICT_H

#include <any>
#include <cassert>
#include <string>
#include <optional>
#include <map>
#include <functional>
#include <memory>
#include <typeindex>
#include <spdlog/spdlog.h>

#include "def.h"
#include "utils.h"

using namespace std;

namespace sly::core::type{
class AttrDict
{
 public:
  template<typename T>
  T Get(const std::string& attr_name) const;
  
  template<typename T>
  T& Ref(const std::string& attr_name);
  
  template<typename T>
  const T& CRef(const std::string& attr_name) const;
  
  template<typename T>
  bool Has(const std::string& attr_name) const;
  
  template<typename T>
  void Emplace(const string& attr_name, T&& attr_value);
  
  template<typename T>
  void Set(string attr_name, T attr_value);
  
  inline void Clear();

  map<string, string> ToStrDict() const;

  string ToString() const;
 
 private:
  map<string, any> attr_dict_;
};

extern map<std::type_index, function<std::string(const any& v)>> type_registery;

template<typename T>
void mark_as_printable(std::function<std::string(const T & v)> f) {
  type_registery.emplace(std::type_index(typeid(T)), [g = f](const any& a) {
    return g(std::any_cast<T>(a));
  });
}

template<typename T>
void mark_as_printable() {
  type_registery.emplace(std::type_index(typeid(T)), [](const any& a) {
    return utils::to_string<T>(std::any_cast<T>(a));
  });
}



template<typename T>
T AttrDict::Get(const std::string& attr_name) const
{
  // check attr_name available:
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end()){
    spdlog::error("cannot find attribute[[{}]].", attr_name);
    throw runtime_error(fmt::format("cannot find attribute[[{}]].", attr_name));
  }
  auto& v = i->second;
  // check has_value
  if (!v.has_value())
    throw runtime_error("this attribute " + attr_name + " doesn't Has value.");
  
  return any_cast<T>(v);
}

template<typename T>
bool AttrDict::Has(const std::string& attr_name) const
{
  // check attr_name available:
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end())
    return false;
  else
    return i->second.type() == typeid(T);
}

template<typename T>
void AttrDict::Emplace(const string& attr_name, T &&attr_value)
{
  static_assert(is_copy_constructible<T>::value);
  static_assert(is_copy_assignable<T>::value);
  
  
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end())
  {   // doesn't has this name, create only.
    attr_dict_.insert({attr_name, make_any<T>(attr_value)});
    return;
  }
  
  auto& v = i->second;
  v = attr_value;
}

template<typename T>
const T &AttrDict::CRef(const string &attr_name) const
{
  // check attr_name available:
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end())
    throw runtime_error("cannot find attribute[[" + attr_name + "]].");
  
  auto& v = i->second;
  // check has_value
  if (!v.has_value())
    throw runtime_error("this attribute " + attr_name + " doesn't Has value.");
  
  const T& retval = any_cast<const T&>(v);
  return retval;
}

template<typename T>
T &AttrDict::Ref(const string &attr_name)
{
  // check attr_name available:
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end())
    throw runtime_error("cannot find attribute[[" + attr_name + "]].");
  
  auto& v = i->second;
  // check has_value
  if (!v.has_value())
    throw runtime_error("this attribute " + attr_name + " doesn't Has value.");
  
  T& retval = any_cast<T&>(v);
  return retval;
}

template<typename T>
void AttrDict::Set(string attr_name, T attr_value)
{
  static_assert(is_copy_constructible<T>::value || is_move_constructible<T>::value);
  
  auto i = attr_dict_.find(attr_name);
  if (i == attr_dict_.end())
  {   // doesn't has this name, create only.
    attr_dict_.insert({attr_name, make_any<T>(attr_value)});
    return;
  }
  
  auto& v = i->second;
  v = move(attr_value);
}


inline void AttrDict::Clear()
{
  attr_dict_.clear();
}
}

#endif //SEULEXYACC_ATTRDICT_H
