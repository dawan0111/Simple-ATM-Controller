#include "atm/bank_api.hpp"
#include "atm/atm.hpp"
#include <gtest/gtest.h>

class BankTest : public ::testing::Test {
protected:
  Bank bank{"ATM-123456789"};

  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(BankTest, validPINNumberTest) {
  auto success = bank.checkPinNumber("1", "1234");
  EXPECT_EQ(success, true);
}

TEST_F(BankTest, inValidPINNumberTest) {
  auto success = bank.checkPinNumber("1", "1234567");
  EXPECT_EQ(success, false);
}

TEST_F(BankTest, GetBalanceTest) {
  auto account = bank.getAccount(1);
  EXPECT_EQ(account->get_money(), 10000);
}

TEST_F(BankTest, WithdrawTest) {
  auto transcation = bank.withdrawAccount(1, 5000);
  EXPECT_EQ(transcation.account_ptr->get_money(), 5000);
}

TEST_F(BankTest, WithdrawErrorTest) {
  auto transcation = bank.withdrawAccount(1, 11000);
  EXPECT_EQ(transcation.success, false);
}

TEST_F(BankTest, DepositTest) {
  auto transcation = bank.depositAccount(1, 7000);
  EXPECT_EQ(transcation.account_ptr->get_money(), 17000);
}

TEST_F(BankTest, DepositErrorTest) {
  auto transcation = bank.depositAccount(1, -7000);
  EXPECT_EQ(transcation.success, false);
}

TEST_F(BankTest, MultipleTranscationTest) {
  bank.depositAccount(1, 1000);
  bank.withdrawAccount(1, 2000);
  auto account = bank.getAccount(1);
  EXPECT_EQ(account->get_money(), 9000);
}

TEST_F(BankTest, getAccountListTest) {
  auto account_vector_ = bank.getAccountList("1");
  EXPECT_EQ(account_vector_.size(), 3);
}