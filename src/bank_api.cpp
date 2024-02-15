#include "atm/bank_api.hpp"

Bank::Bank(const std::string &atm_key) : atm_key_(atm_key) {
  account_vector_.emplace_back(1, "Account 1", 10000);
  account_vector_.emplace_back(2, "Account 2", 5000);
  account_vector_.emplace_back(3, "Account 3", 1000);
}
bool Bank::checkPinNumber(const std::string &card_number,
                          const std::string &pin_number) {
  return card_number == "1" && pin_number == "1234";
}

const std::vector<Account> &
Bank::getAccountList(const std::string &card_number) {
  return account_vector_;
}

Account *Bank::getAccount(const int32_t &account_id) {
  return getAccount_(account_id);
}

Transaction Bank::depositAccount(const int32_t &account_id,
                                 const int32_t &money) {
  auto account_ptr = getAccount_(account_id);
  Transaction transcation;

  transcation.account_ptr = account_ptr;
  transcation.success = false;
  if (account_ptr != nullptr) {
    transcation.success = account_ptr->deposit(money);
  }
  return transcation;
}
Transaction Bank::withdrawAccount(const int32_t &account_id,
                                  const int32_t &money) {
  auto account_ptr = getAccount_(account_id);
  Transaction transcation;

  transcation.account_ptr = account_ptr;
  transcation.success = false;
  if (account_ptr != nullptr) {
    transcation.success = account_ptr->withdraw(money);
  }
  return transcation;
}

Account *Bank::getAccount_(const int32_t &account_id) {
  for (auto &account : account_vector_) {
    if (account.get_id() == account_id) {
      return &account;
    }
  }

  return nullptr;
}