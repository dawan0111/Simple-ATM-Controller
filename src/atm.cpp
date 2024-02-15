#include "atm/atm.hpp"

Atm::Atm() { bank_ = std::make_unique<Bank>(atm_key_); }

template <typename Func> auto Atm::executeStep(Func func) -> decltype(func()) {
  while (true) {
    auto result = func();
    if (!result) {
      std::cout << "Wrong input... try align." << std::endl;
    } else {
      return result;
    }
  }
}

void Atm::run() {
  quit_event_ = false;
  while (true) {
    executeStep([this]() {
      if (step_ == Step::card) {
        return runCardInputStep();
      } else if (step_ == Step::pinNumber) {
        return runPinNumberInputStep();
      } else if (step_ == Step::account) {
        return runSelectAccountStep();
      } else if (step_ == Step::accountMenu) {
        return runAccountMenuStep();
      }
      return true;
    });
    if (quit_event_) {
      break;
    }
  }
}

bool Atm::runCardInputStep() {
  std::cout << "Please choose an option:" << std::endl;
  std::cout << "1. Insert Card" << std::endl;
  std::cout << "2. Exit" << std::endl;
  std::cout << "Selection: ";
  std::cin >> user_input_;

  if (user_input_ == "1") {
    card_number_ = "1";
    step_ = Step::pinNumber;
    return true;
  } else if (user_input_ == "2") {
    std::cout << "Good bye" << std::endl;
    quit_event_ = true;
    return true;
  }
  return false;
}

bool Atm::runPinNumberInputStep() {
  int32_t try_count = 0;
  while (true) {
    std::cout << "(Try: " << try_count << ") ";
    std::cout << "Please enter your PIN number (Press 'q' to go back): ";
    std::cin >> user_input_;

    if (user_input_ == "q") {
      step_ = Step::card;
      break;
    } else {
      std::cout << "Verifying PIN number, please wait..." << std::endl;
      bool success = bank_->checkPinNumber(card_number_, user_input_);

      if (!success) {
        std::cout << "Invalid PIN number. Please try again." << std::endl;
      } else {
        std::cout << "PIN number verified successfully." << std::endl;
        step_ = Step::account;
        break;
      }
    }
    ++try_count;
  }

  return true;
}

bool Atm::runSelectAccountStep() {
  std::cout << "Please select your account by entering the number (#n). (Press "
               "'q' to go back):"
            << std::endl;
  auto account_vector = bank_->getAccountList(card_number_);
  auto account_size = account_vector.size();

  for (int32_t i = 0; i < account_size; ++i) {
    std::cout << "#" << (i + 1) << ". ID: " << account_vector[i].get_id()
              << ", NAME: " << account_vector[i].get_name() << std::endl;
  }

  std::cout << "Selection: ";
  std::cin >> user_input_;

  if (user_input_ == "q") {
    step_ = Step::card;
    return true;
  }

  try {
    int32_t account_index = stoi(user_input_) - 1;
    auto account_id = account_vector.at(account_index).get_id();
    account_id_ = account_id;
    step_ = Step::accountMenu;
  } catch (const std::exception &e) {
    return false;
  }
  return true;
}

bool Atm::runAccountMenuStep() {
  std::cout << "===== Selected Account ID: " << account_id_
            << " =====" << std::endl;
  std::cout << "Select Menu: " << std::endl;
  std::cout << "1. See Balance" << std::endl;
  std::cout << "2. Deposit" << std::endl;
  std::cout << "3. Withdraw" << std::endl;
  std::cout << "4. Go back" << std::endl;

  std::cout << "Selection: ";
  std::cin >> user_input_;

  if (user_input_ == "1") {
    const auto account_ptr = bank_->getAccount(account_id_);
    if (account_ptr == nullptr) {
      std::cout << "Account search Error" << std::endl;
      step_ = Step::account;
    } else {
      std::cout << "===== Account Info =====" << std::endl;
      std::cout << "ID: " << account_ptr->get_id() << std::endl;
      std::cout << "Name: " << account_ptr->get_name() << std::endl;
      std::cout << "Balance: " << account_ptr->get_money() << std::endl;
    }
  } else if (user_input_ == "2") {
    std::cout << "Enter the amount you are depositing: ";
    std::cin >> user_input_;

    try {
      int32_t money = stoi(user_input_);
      if (money < 0) {
        return false;
      }
      auto transcation = bank_->depositAccount(account_id_, money);

      if (transcation.success) {
        std::cout << "===== Account Updated =====" << std::endl;
        std::cout << "Before: " << transcation.account_ptr->get_money() - money
                  << std::endl;
        std::cout << "After: " << transcation.account_ptr->get_money()
                  << std::endl;
      } else {
        std::cout << "Transaction Error." << std::endl;
      }
    } catch (const std::exception &e) {
      return false;
    }
  } else if (user_input_ == "3") {
    std::cout << "Enter the amount you are withdrawing: ";
    std::cin >> user_input_;

    try {
      int32_t money = stoi(user_input_);
      if (money < 0) {
        return false;
      }
      auto transcation = bank_->withdrawAccount(account_id_, money);

      if (transcation.success) {
        std::cout << "===== Account Updated =====" << std::endl;
        std::cout << "Before: " << transcation.account_ptr->get_money() + money
                  << std::endl;
        std::cout << "After: " << transcation.account_ptr->get_money()
                  << std::endl;
      } else {
        std::cout << "No enough money." << std::endl;
      }
    } catch (const std::exception &e) {
      return false;
    }
  } else if (user_input_ == "4") {
    step_ = Step::account;
  } else {
    return false;
  }

  return true;
}