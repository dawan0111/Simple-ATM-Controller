#ifndef BANK_API_HPP_
#define BANK_API_HPP_

#include "atm/account.hpp"
#include <iostream>
#include <vector>

struct Transaction {
  Account *account_ptr;
  bool success;
};

class Bank {
public:
  Bank(const std::string &atm_key_);
  bool checkPinNumber(const std::string &card_number,
                      const std::string &pin_number);
  const std::vector<Account> &getAccountList(const std::string &card_number);
  Account *getAccount(const int32_t &account_id);
  Transaction depositAccount(const int32_t &account_id, const int32_t &money);
  Transaction withdrawAccount(const int32_t &account_id, const int32_t &money);

private:
  std::string atm_key_;
  std::vector<Account> account_vector_;
  Account *getAccount_(const int32_t &account_id);
};

#endif