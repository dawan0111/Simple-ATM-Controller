#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_
#include <string>
class Account {
public:
  Account(const int32_t &id, const std::string &account_name,
          const int32_t &money);
  const int32_t &get_money();
  const int32_t &get_id();
  const std::string &get_name();
  bool deposit(const int32_t money);
  bool withdraw(const int32_t money);

private:
  int32_t id_;
  std::string account_name_;
  int32_t money_;
};

#endif