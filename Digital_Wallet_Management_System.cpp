#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> user_ids;
vector<double> balances;

void add_user(int id, double balance) {
    if (id < 0 || balance < 0) {
        cerr << "Error: User ID and balance must be non-negative." << endl;
        return;
    }
    user_ids.push_back(id);
    balances.push_back(balance);
}

bool transfer_funds(int from_id, int to_id, double amount) {
    if (amount < 0) {
        cerr << "Error: Transfer amount must be non-negative." << endl;
        return false;
    }

    auto from_it = find(user_ids.begin(), user_ids.end(), from_id);
    auto to_it = find(user_ids.begin(), user_ids.end(), to_id);

    if (from_it == user_ids.end() || to_it == user_ids.end()) {
        cerr << "Error: User ID not found." << endl;
        return false;
    }

    int from_index = distance(user_ids.begin(), from_it);
    int to_index = distance(user_ids.begin(), to_it);

    if (balances[from_index] < amount) {
        cerr << "Error: Insufficient funds." << endl;
        return false;
    }

    balances[from_index] -= amount;
    balances[to_index] += amount;
    return true;
}

void sort_and_display_users() {
    vector<pair<int, double>> users;
    for (size_t i = 0; i < user_ids.size(); ++i) {
        users.emplace_back(user_ids[i], balances[i]);
    }

    sort(users.begin(), users.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    for (const auto& user : users) {
        cout << user.first << " " << fixed << setprecision(0) << user.second << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of users: ";
    cin >> n;

    if (n < 0) {
        cerr << "Error: Number of users must be non-negative." << endl;
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        int id;
        double balance;
        cout << "Enter user ID and balance: ";
        cin >> id >> balance;
        add_user(id, balance);
    }

    int t;
    cout << "Enter the number of transactions: ";
    cin >> t;

    if (t < 0) {
        cerr << "Error: Number of transactions must be non-negative." << endl;
        return 1;
    }

    for (int i = 0; i < t; ++i) {
        int from_id, to_id;
        double amount;
        cout << "Enter from ID, to ID, and amount: ";
        cin >> from_id >> to_id >> amount;

        bool success = transfer_funds(from_id, to_id, amount);
        cout << (success ? "Success" : "Failure") << endl;
    }

    cout << endl;
    sort_and_display_users();

    return 0;
}