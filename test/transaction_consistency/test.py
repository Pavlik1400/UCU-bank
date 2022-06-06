import time

from utils import *
from argparse import ArgumentParser


def login_3_super_users():
    print_header("login 3 super users")
    for i in range(1, 4):
        # login1
        resp = make_request(
            API_ROOT_v2 + "user/login1/",
            data={
                "phone_num": state.__getattribute__(f"USER{i}")["phone_num"],
                "password": state.__getattribute__(f"USER{i}")["password"]
            }
        )
        assert resp["status"] == 200

        # login2
        resp = make_request(
            API_ROOT_v2 + "user/login2/",
            data=resp  # just a trick with reponse of login1 and request of login2
        )

        assert resp["status"] == 200
        state.__setattr__(f"TOKEN{i}", resp["token"])
        state.__setattr__(f"UID{i}", resp["uid"])


def get_3_super_accounts():
    print_header("Create 3 super accounts")
    for i in range(1, 4):
        resp = make_request(
            API_ROOT_v2 + "account/get_accounts/",
            data={
                "user_id": state.__getattribute__(f"UID{i}"),
                "token": state.__getattribute__(f"TOKEN{i}")
            }
        )

        assert resp["status"] == 200
        state.__getattribute__(f"USER{i}_ACCOUNTS").append(resp["accounts"][-1])


def make_circle_transactions():
    """
    u1 -> u2  10$
    u2 -> u3  10$
    u3 -> u1  10$
    :return:
    """
    resp = make_request(
        API_ROOT_v2 + "transaction/create/",
        data={
            "user_id": state.UID1,
            "from_acc_number": state.USER1_ACCOUNTS[-1]["number"],
            "to_acc_number": state.USER2_ACCOUNTS[-1]["number"],
            "description": "1 --> 2",
            "amount": 10.0,
            "category": 9,
            "token": state.TOKEN1
        }
    )

    assert resp["status"] == 200

    resp = make_request(
        API_ROOT_v2 + "transaction/create/",
        data={
            "user_id": state.UID2,
            "from_acc_number": state.USER2_ACCOUNTS[-1]["number"],
            "to_acc_number": state.USER3_ACCOUNTS[-1]["number"],
            "description": "2 --> 3",
            "amount": 10.0,
            "category": 9,
            "token": state.TOKEN2
        }
    )

    assert resp["status"] == 200

    resp = make_request(
        API_ROOT_v2 + "transaction/create/",
        data={
            "user_id": state.UID3,
            "from_acc_number": state.USER3_ACCOUNTS[-1]["number"],
            "to_acc_number": state.USER1_ACCOUNTS[-1]["number"],
            "description": "3 --> 1",
            "amount": 10.0,
            "category": 9,
            "token": state.TOKEN3
        }
    )

    assert resp["status"] == 200


def get_users_balances():
    balances = []
    for i in range(1, 4):
        resp = make_request(
            API_ROOT_v2 + "account/info/",
            data={
                "account_number": state.__getattribute__(f"USER{i}_ACCOUNTS")[-1]["number"],
                "token": state.__getattribute__(f"TOKEN{i}")
            }
        )
        assert resp["status"] == 200
        balances.append(resp["info"]["balance"])
    return balances


def main():
    parser = ArgumentParser("make N circular transaction between 3 accounts")
    parser.add_argument("--N", type=int, default=10_000)
    parser.add_argument("--n", type=int, required=True,  help="number of this process")
    parser.add_argument("--verbose", action="store_const", const=True)
    args = parser.parse_args()
    N = args.N
    n = args.n
    state.VERBOSE = args.verbose

    login_3_super_users()
    get_3_super_accounts()
    accs = list(map(lambda x: x[-1]["number"], [x for x in [state.USER1_ACCOUNTS, state.USER2_ACCOUNTS, state.USER3_ACCOUNTS]]))
    print(f"Process {n}: accounts: {accs}")
    balances = get_users_balances()

    print(f"Process {n}: initialized users and accounts. Start transactions")
    print(f"Process {n}: balances before: {balances}")

    for _ in range(N):
        make_circle_transactions()

    balances = get_users_balances()
    print(f"Process {n}: waiting 5 seconds to wait for other processes...")
    time.sleep(5)
    print(f"Process {n}: finished. Balances: {balances}")


if __name__ == '__main__':
    main()
