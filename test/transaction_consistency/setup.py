from utils import *


def create_3_super_users():
    print_header("Create 3 super users")
    for i in range(1, 4):
        # register
        resp = make_request(
            API_ROOT_v2 + "user/register/",
            data=state.__getattribute__(f"USER{i}")
        )
        assert resp["status"] == 200 or resp["message"] == "USER_EXISTS"

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


def create_3_super_accounts():
    print_header("Create 3 super accounts")
    for i in range(1, 4):
        resp = make_request(
            API_ROOT_v2 + "account/create/",
            data={
                "token": state.__getattribute__(f"TOKEN{i}"),
                "user_id": state.__getattribute__(f"UID{i}"),
                "account_type": "silver",
            }
        )
        assert resp["status"] == 200


if __name__ == '__main__':
    state.VERBOSE = True
    create_3_super_users()
    create_3_super_accounts()
