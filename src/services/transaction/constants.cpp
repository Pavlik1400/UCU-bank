#include "transaction/constants.hpp"

transaction_t transaction_t::from_row(const pqxx::row &row) {
    return transaction_t{
            "",
            row["from_acc_number"].as<std::string>(),
            row["to_acc_number"].as<std::string>(),
            row["description"].as<std::string>(),
            row["amount"].as<double>(),
            transaction::category(row["category"].as<int>()),
            row["date"].as<std::string>(),
            transaction::db_entry_status(row["status"].as<int>())
    };
}

transaction_t::transaction_t(
        str user_id,
        str from_acc_number,
        str to_acc_number,
        str description,
        const double amount,
        transaction::category category
) :
        user_id(user_id),
        from_acc_number(from_acc_number),
        to_acc_number(to_acc_number),
        description(description),
        amount(amount),
        category(category),
        date(ucu_optional<std::string>{}),
        status(ucu_optional<transaction::db_entry_status>{}) {}

transaction_t::transaction_t(
        str user_id,
        str from_acc_number,
        str to_acc_number,
        str description,
        const double amount,
        transaction::category category,
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

transaction_t::transaction_t() = default;
