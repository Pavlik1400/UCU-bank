import unittest

from constants import *
from utils import *
from user import USER1

unittest.TestLoader.sortTestMethodsUsing = None


class Test2AccountAPI(unittest.TestCase):
    def setUp(self) -> None:
        self.account = "account/"

    def test1_create(self):
        print_header("test /account/create/")
        resp = make_request(
            API_ROOT_v2 + self.account + "create/",
            data={
                "token": state.TOKEN1,
                "user_id": state.UID1,
                "account_type": "gold"
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        state.USER1_ACCOUNTS.append({"account_type": "gold"})

    def test2get(self):
        print_header("test /account/get_accounts/")
        resp = make_request(
            API_ROOT_v2 + self.account + "get_accounts/",
            data={
                "token": state.TOKEN1,
                "user_id": state.UID1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("accounts" in resp)

        for acc in resp["accounts"]:
            state.USER1_ACCOUNTS.append(acc)
            self.assertTrue(acc["active"])
            self.assertEqual(acc["balance"], 0.0)
            self.assertEqual(acc["user_id"], state.UID1)

    def test3_info(self):
        print_header("test /account/info/")
        resp = make_request(
            API_ROOT_v2 + self.account + "info/",
            data={
                "token": state.TOKEN1,
                "account_number": state.USER1_ACCOUNTS[-1]["number"],
            }
        )

        self.assertEqual(resp.get("status", 0), 200)
        for key in state.USER1_ACCOUNTS[-1]:
            self.assertEqual(resp["info"][key], state.USER1_ACCOUNTS[-1][key])

    def test4_user_info(self):
        print_header("test /account/user_info/")
        resp = make_request(
            API_ROOT_v2 + self.account + "user_info/",
            data={
                "token": state.TOKEN1,
                "account_number": state.USER1_ACCOUNTS[-1]["number"]
            }
        )

        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("info" in resp)
        self.assertEqual(resp["info"]["email"], USER1["email"])
        self.assertEqual(resp["info"]["name"], USER1["name"])
        self.assertEqual(resp["info"]["type"], USER1["type"])

