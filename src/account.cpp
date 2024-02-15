#include "atm/account.hpp"

Account::Account(const int32_t &id, const std::string &account_name,
                 const int32_t &money)
    : id_(id), account_name_(account_name), money_(money){};

const int32_t &Account::get_money() { return money_; }
const int32_t &Account::get_id() { return id_; }
const std::string &Account::get_name() { return account_name_; }

bool Account::deposit(int32_t money) {
  if (money < 0) {
    return false;
  }
  money_ += money;
  return true;
}
bool Account::withdraw(int32_t money) {
  if (money < 0 || money_ < money) {
    return false;
  }
  money_ -= money;
  return true;
}