import unittest

from constants import *
from utils import *

unittest.TestLoader.sortTestMethodsUsing = None


class Test4TransactionAPI(unittest.TestCase):
    def setUp(self) -> None:
        self.transaction = "transaction/"

    def test1create(self):
        print_header("test /transaction/create")
        resp = make_request(
            API_ROOT_v2 + self.transaction + "create/",
            data={
                "user_id": state.UID1,
                "from_acc_number": state.USER1_ACCOUNTS[-1]["number"],
                "to_acc_number": state.USER2_ACCOUNTS[-1]["number"],
                "description": "pivo",
                "amount": 20.0,
                "category": 9,
                "token": state.TOKEN1
            }
        )

        self.assertEqual(resp.get("status", 0), 200)

    def test2get(self):
        print_header("test /transaction/get/")
        resp = make_request(
            API_ROOT_v2 + self.transaction + "get/",
            data={
                "account_number": state.USER1_ACCOUNTS[-1]["number"],
                "limit": 100,
                "token": state.TOKEN1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("transactions" in resp)
        for tran in resp["transactions"]:
            if tran["description"] == "pivo":
                self.assertEqual(tran["amount"], 20.0)
                self.assertEqual(tran["from_acc_number"], state.USER1_ACCOUNTS[-1]["number"])
                self.assertEqual(tran["to_acc_number"], state.USER2_ACCOUNTS[-1]["number"])
