#include "transaction_constants.hpp"

Transaction Transaction::from_row(const pqxx::row &row) {
    return Transaction{
            "",
            row["from_acc_number"].as<std::string>(),
            row["to_acc_number"].as<std::string>(),
            row["description"].as<std::string>(),
            row["amount"].as<double>(),
            transaction::categories(row["category"].as<int>()),
            row["date"].as<std::string>(),
            transaction::db_entry_status(row["status"].as<int>())
    };
}

Transaction::Transaction(
        str user_id,
        str from_acc_number,
        str to_acc_number,
        str description,
        const double amount,
        transaction::categories category
) :
        user_id(user_id),
        from_acc_number(from_acc_number),
        to_acc_number(to_acc_number),
        description(description),
        amount(amount),
        category(category),
        date(ucu_optional<std::string>{}),
        status(ucu_optional<transaction::db_entry_status>{}) {}

Transaction::Transaction(
        str user_id,
        str from_acc_number,
        str to_acc_number,
        str description,
        const double amount,
        transaction::categories category,
        str date,
        transaction::db_entry_status status
) :
        user_id(user_id),
        from_acc_number(from_acc_number),
        to_acc_number(to_acc_number),
        description(description),
        amount(amount),
        category(category),
        date(date),
        status(status) {}

Transaction::Transaction() = default;