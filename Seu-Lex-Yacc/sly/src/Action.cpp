//
// Created by Yang Jerry on 2022/3/30.
//

#include <sly/Action.h>
#include <string>
#include <sly/utils.h>
namespace sly::core::type {

Action::Action() = default;


Action::Action(Action::ActionFType f) :
  opt_f_(f),
  impl_(""){
}


Action::Action(Action::ActionFType f, std::string impl) :
  opt_f_(f),
  impl_(move(impl)){
}

void Action::Modify(std::vector<TokenAttr> &tokens) {
  if (opt_f_.has_value())
    opt_f_.value()(tokens);
}

bool Action::operator==(const Action &rhs) const {
  if (opt_f_.has_value() != rhs.opt_f_.has_value())
    return false;
  else
    return true;
}


std::ostream& operator <<(std::ostream& os, const Action& act) {
  os << "sly::core::type::Action([](std::vector<YYSTATE>& v) {"
    << act.GetImpl() << "}, \"" << act.GetImpl() << "\"}";
  return os;
}

std::string Action::ToString() const {
  return "Action{" + impl_ + "}";
}

}