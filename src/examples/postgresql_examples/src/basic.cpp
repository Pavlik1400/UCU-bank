#include <iostream>
#include <pqxx/pqxx>

using namespace pqxx;

using str = std::string;

int main(int argc, char *argv[]) {
    try {
        connection C("dbname = transactions user = postgres password = postgres "
                     "hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            std::cout << "Opened database successfully: " << C.dbname() << std::endl;
        } else {
            std::cout << "Can't open database" << std::endl;
            return 1;
        }

        {
            work W(C);      // CREATE TRANSACTION OBJECT - work

            std::cout << "Create table" << std::endl;
            auto sql = "CREATE TABLE IF NOT EXISTS ACCOUNT_MONEY_TRANSFER("
                       "ID SERIAL PRIMARY KEY               NOT NULL,"
                       "to_acc_number       BIGINT            NOT NULL,"
                       "to_acc_number         BIGINT            NOT NULL,"
                       "AMOUNT         NUMERIC(12,2)     NOT NULL,"
                       "DATE           TIMESTAMP         NOT NULL,"
                       "STATUS         INT               NOT NULL,"
                       "DESCRIPTION    VARCHAR(1000),             "
                       "CATEGORY       INT               NOT NULL,"
                       "RESERVED       VARCHAR(20)                "
                       ");";
            std::cout << "Executing \n" << sql << std::endl;

            W.exec(sql);

            std::cout << "Table created successfully\n\n" << std::endl;

            std::cout << "Truncate table just in case" << std::endl;
            sql = "truncate table account_money_transfer;";
            std::cout << "Executing \n" << sql << std::endl;
            W.exec(sql);
            std::cout << "Truncated successfully\n\n" << std::endl;


            std::cout << "Insert Data" << std::endl;
            sql = "INSERT INTO account_money_transfer (from_acc_number, to_acc_number, amount, date, status, description, category) values"
                  "(0,1,12.55,'2001-09-28 01:00:00',0,'pizza',1),"
                  "(1,2,4.7,'2001-09-29 03:00:00',0,'coffee',2)";
            std::cout << "Executing \n" << sql << std::endl;

            W.exec(sql);
            W.commit();     // FINISH TRANSACTION
            std::cout << "Records created successfully\n\n" << std::endl;

            std::cout << "select query" << std::endl;
            sql = "select * from account_money_transfer";
            std::cout << "Executing \n" << sql << std::endl;
            nontransaction N(C);

            result R(N.exec(sql));
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                std::cout << "=============================================" << std::endl;
                std::cout << "ID = " << c[0].as<int>() << std::endl;
                std::cout << "to_acc_number = " << c[1].as<long long>() << std::endl;
                std::cout << "to_acc_number = " << c[2].as<long long>() << std::endl;
                std::cout << "AMOUNT = " << c[3].as<double>() << std::endl;
                std::cout << "DATE = " << c[4].as<str>() << std::endl;
                std::cout << "DESCRIPTION = " << c[6].as<str>() << std::endl;
            }
            std::cout << "Query finished successfully\n\n" << std::endl;

            std::cout << "Update query" << std::endl;
            sql = "update account_money_transfer set description = 'burger' where (to_acc_number=0 and to_acc_number=1) and date='2001-09-28 01:00:00';";
            std::cout << "Executing \n" << sql << std::endl;

            N.exec(sql);
            std::cout << "select * after update: \n";
            R = result(N.exec("select * from account_money_transfer;"));
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                std::cout << "=============================================" << std::endl;
                std::cout << "ID = " << c[0].as<int>() << std::endl;
                std::cout << "from_acc_number = " << c[1].as<long long>() << std::endl;
                std::cout << "to_acc_number = " << c[2].as<long long>() << std::endl;
                std::cout << "AMOUNT = " << c[3].as<double>() << std::endl;
                std::cout << "DATE = " << c[4].as<str>() << std::endl;
                std::cout << "DESCRIPTION = " << c[6].as<str>() << std::endl;
            }

            std::cout << "Update successfull" << std::endl;

            std::cout << "Alternative update" << std::endl;
            std::cout << "select from_acc_number, to_acc_number, amount FROM account_money_transfer" << std::endl;
            pqxx::result r{N.exec("select from_acc_number, to_acc_number, amount FROM account_money_transfer")};
            for (auto row: r)
                std::cout << row["to_acc_number"].as<long long>() << " -- "
                          << row["amount"].as<double>() << "$ --> 2"
                          << row["to_acc_number"].as<long long>() << std::endl;
        }
        {
            work W1{C};

            pqxx::row r = W1.exec1("SELECT 1, 2, 'Hello'");
            auto[one, two, hello] = r.as<int, int, std::string>();

            W1.commit();

            std::cout << one << " " << two << " " << hello << std::endl;

            // to escape SQL injection, use W.esc() https://libpqxx.readthedocs.io/en/latest/a01432.html

        }
        // FOR SOME REASON IN DOCUMENTATION THERE IS C.disconnect(). Probably this is the same
        C.close();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}