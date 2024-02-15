#ifndef ATM_HPP_
#define ATM_HPP_
#include "atm/account.hpp"
#include "atm/bank_api.hpp"
#include <iostream>
#include <memory>
enum class Step { card, pinNumber, account, accountMenu };

class Atm {
public:
  Atm();
  void run();

private:
  std::unique_ptr<Bank> bank_;
  std::string atm_key_{"ATM-123456789"};
  std::string pin_number_;
  std::string card_number_;
  std::string user_input_;
  int32_t account_id_;
  bool quit_event_;
  Step step_{Step::card};

private:
  bool runCardInputStep();
  bool runPinNumberInputStep();
  bool runSelectAccountStep();
  bool runAccountMenuStep();

  template <typename Func> auto executeStep(Func func) -> decltype(func());
};

#endif