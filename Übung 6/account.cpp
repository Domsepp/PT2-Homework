#include <iostream>
#include <random>

class Account {
	protected:
	int m_accountNumber;
	int64_t m_balance = 0;

	public:
	explicit Account(int accountNumber) {
		m_accountNumber = accountNumber;
		std::cout << "Account " << m_accountNumber << ": Created\n";
	}
	
	virtual ~Account(){}

	int64_t balance() const {
		return m_balance;
	}

	int accountNumber() const {
		return m_accountNumber;
	}

	virtual bool transaction(int64_t amount, const std::string& reason) {
		std::cout << "Account " << m_accountNumber << ": Transaction (Amount: " << amount
				  << " Reason: " << reason << ")\n";
		m_balance += amount;
		return true;
	}
};

class SavingAccount : public Account {
	public:
	SavingAccount(int accountNumber) : Account(accountNumber){}

	~SavingAccount() { // Destruktor
		std::cout << "Account " << m_accountNumber << ": Destroyed saving account (Balance: " << m_balance << ")\n";
	}
};

class YouthAccount : public Account {
	public:
	YouthAccount(int accountNumber) : Account(accountNumber){}

	~YouthAccount() { // Destruktor
		std::cout << "Account " << m_accountNumber << ": Destroyed youth account (Balance: " << m_balance << ")\n";
	}

	bool transaction(int64_t amount, const std::string& reason) {
		if (m_balance < -amount) {
			std::cout << "Account " << m_accountNumber << ": Declined transaction (Current balance: " << m_balance << ", Requested Transaction: " << amount << ")\n";
			return false;
		}else {
			std::cout << "Account " << m_accountNumber << ": Transaction (Amount: " << amount << " Reason: " << reason << ")\n";
			m_balance += amount;
		}
		return true;
	}
};

int main() {
	std::vector<Account*> m_accounts;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution youthAccountDistrib(0.25);
	std::uniform_int_distribution<> initDepositDistrib(0, 50); // ohne <> wirft es bei mir nen error: missing template arguments before 'initDepositDistrib'
	int64_t init = initDepositDistrib(gen);
	constexpr int accountCount = 20;
	for (int i = 0; i < accountCount; ++i) {
		if (youthAccountDistrib(gen)) {
			m_accounts.push_back(new YouthAccount(i));
			m_accounts.back()->transaction(init, "Youth welcome gift");
		} else {
			m_accounts.push_back(new SavingAccount(i));
		}
		m_accounts.back()->transaction(initDepositDistrib(gen), "Deposit");
	}

	std::uniform_int_distribution<> transactionDistrib(-100, 100); //same here as in line 67
	constexpr int simulationRuns = 5;
	for (int i = 0; i < simulationRuns; ++i) {
		for (auto& account : m_accounts) {
			account->transaction(transactionDistrib(gen), "Random transaction");
		}
	}

	for (auto& account : m_accounts) {
		delete account;
	}
	
	return 0;
}
