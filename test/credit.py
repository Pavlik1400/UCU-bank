import unittest

from constants import *
from utils import *

unittest.TestLoader.sortTestMethodsUsing = None


class Test3CreditAPI(unittest.TestCase):
    def setUp(self) -> None:
        self.credit = "credit/"

    def test1create(self):
        print_header("test /credit/create/")
        resp = make_request(
            API_ROOT_v2 + self.credit + "create/",
            data={
                "token": state.TOKEN1,
                "card_number": state.USER1_ACCOUNTS[-1]["number"],
                "type": 0,
                "amount": 100
            }
        )

        self.assertEqual(resp.get("status", 0), 200)

    def test2get(self):
        print_header("test /credit/get/")
        resp = make_request(
            API_ROOT_v2 + self.credit + "get/",
            data={
                "token": state.TOKEN1,
                "user_id": state.UID1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("credits" in resp)
        for cred in resp["credits"]:
            self.assertTrue(cred["active"])
            self.assertEqual(cred["card_number"],
                             state.USER1_ACCOUNTS[-1]["number"])
            self.assertEqual(cred["user_id"], state.UID1)
            state.CRED_ID1 = cred["id"]

    def test3finish(self):
        print_header("test /credit/finish/")
        # finish credit
        resp = make_request(
            API_ROOT_v2 + self.credit + "finish/",
            data={
                "token": state.TOKEN1,
                "id": state.CRED_ID1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)

        # make sure it is closed
        resp = make_request(
            API_ROOT_v2 + self.credit + "get/",
            data={
                "token": state.TOKEN1,
                "user_id": state.UID1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("credits" in resp)
        for cred in resp["credits"]:
            self.assertFalse(cred["active"])

        # reopen credit for future transactions
        resp = make_request(
            API_ROOT_v2 + self.credit + "create/",
            data={
                "token": state.TOKEN1,
                "card_number": state.USER1_ACCOUNTS[-1]["number"],
                "type": 0,
                "amount": 500
            }
        )

        self.assertEqual(resp.get("status", 0), 200)

        # save new credit ID
        resp = make_request(
            API_ROOT_v2 + self.credit + "get/",
            data={
                "token": state.TOKEN1,
                "user_id": state.UID1,
            }
        )
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("credits" in resp)
        for cred in resp["credits"]:
            if cred["active"]:
                state.CRED_ID1 = cred["id"]


