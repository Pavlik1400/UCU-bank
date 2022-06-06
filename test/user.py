import unittest

from constants import *
from utils import *

unittest.TestLoader.sortTestMethodsUsing = None

USER1 = {
    "type": "regular",
    "name": "user1",
    "password": gen_random_string(20),
    "date_of_birth": "2001-01-01",
    "phone_num": gen_random_string(20),
    "email": "user1@gmail.com",
    "address": "1",
    "gender": "user1"
}

USER2 = {
    "type": "super",
    "name": "user2",
    "password": gen_random_string(20),
    "date_of_birth": "2002-02-02",
    "phone_num": gen_random_string(20),
    "email": "user2@gmail.com",
    "address": "2",
    "gender": "user2",
    "super-duper-secret": "4694944920569279849376435242991721996950851627475313791297870890"
}


class Test1UserAPI(unittest.TestCase):
    def setUp(self) -> None:
        self.user = "user/"

    def test1_register(self):
        print_header("test /user/register/")
        # register first user
        resp = make_request(API_ROOT_v2 + self.user + "register/",
                            data=USER1)
        self.assertEqual(resp.get("status", 0), 200)

        # register second user
        resp = make_request(API_ROOT_v2 + self.user + "register/",
                            data=USER2)
        self.assertEqual(resp.get("status", 0), 200)

    def test2_login1(self):
        print_header("test /user/login1/")
        # login first user
        resp = make_request(API_ROOT_v2 + self.user + "login1/",
                            data={
                                "phone_num": USER1["phone_num"],
                                "password": USER1["password"]
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("otp_key" in resp)
        self.assertTrue("one_time_passwd" in resp)
        state.OTP_KEY1 = resp.get("otp_key", "")
        state.OTP1 = resp.get("one_time_passwd", "")

        # login second user
        resp = make_request(API_ROOT_v2 + self.user + "login1/",
                            data={
                                "phone_num": USER2["phone_num"],
                                "password": USER2["password"],
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("otp_key" in resp)
        self.assertTrue("one_time_passwd" in resp)
        state.OTP_KEY2 = resp.get("otp_key", "")
        state.OTP2 = resp.get("one_time_passwd", "")

    def test3_login2(self):
        print_header("test /user/login2/")

        # login first user
        resp = make_request(API_ROOT_v2 + self.user + "login2/",
                            data={
                                "one_time_passwd": state.OTP1,
                                "otp_key": state.OTP_KEY1,
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("token" in resp)
        self.assertTrue("uid" in resp)
        state.TOKEN1 = resp.get("token", "")
        state.UID1 = resp.get("uid", "")

        # login second user
        resp = make_request(API_ROOT_v2 + self.user + "login2/",
                            data={
                                "one_time_passwd": state.OTP2,
                                "otp_key": state.OTP_KEY2,
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("token" in resp)
        self.assertTrue("uid" in resp)
        state.TOKEN2 = resp.get("token", "")
        state.UID2 = resp.get("uid", "")

    def test4_info(self):
        print_header("test /user/info/")
        # regular user find information about himself
        resp = make_request(API_ROOT_v2 + self.user + "info/",
                            data={
                                "token": state.TOKEN1,
                                "phone_num": USER1["phone_num"]
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("info" in resp)
        for key in SAMPLE_INFO_FULL_RESPONSE["info"]:
            self.assertTrue(key in resp["info"])
            if key in USER1:
                self.assertEqual(resp["info"][key], USER1[key])

        # regular user find information about other user
        resp = make_request(API_ROOT_v2 + self.user + "info/",
                            data={
                                "token": state.TOKEN1,
                                "phone_num": USER2["phone_num"]
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("info" in resp)
        for key in SAMPLE_INFO_PARTIAL_RESPONSE["info"]:
            self.assertTrue(key in resp["info"])
            if key in USER2:
                self.assertEqual(resp["info"][key], USER2[key])

    def test5_logout(self):
        print_header("test /user/logout/")
        # logout
        resp = make_request(API_ROOT_v2 + self.user + "logout/",
                            data={
                                "token": state.TOKEN1
                            })
        self.assertEqual(resp.get("status", 0), 200)

        # info should fail
        resp = make_request(API_ROOT_v2 + self.user + "info/",
                            data={"token": state.TOKEN1, "phone_num": USER1["phone_num"]})
        self.assertEqual(resp.get("status", 0), 403)

        # login1
        resp = make_request(API_ROOT_v2 + self.user + "login1/",
                            data={
                                "phone_num": USER1["phone_num"],
                                "password": USER1["password"]
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("otp_key" in resp)
        self.assertTrue("one_time_passwd" in resp)
        state.OTP_KEY1 = resp.get("otp_key", "")
        state.OTP1 = resp.get("one_time_passwd", "")

        # login2
        resp = make_request(API_ROOT_v2 + self.user + "login2/",
                            data={
                                "one_time_passwd": state.OTP1,
                                "otp_key": state.OTP_KEY1,
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("token" in resp)
        self.assertTrue("uid" in resp)
        state.TOKEN1 = resp.get("token", "")
        state.UID1 = resp.get("uid", "")

        # info after relogined
        resp = make_request(API_ROOT_v2 + self.user + "info/",
                            data={
                                "token": state.TOKEN1,
                                "phone_num": USER1["phone_num"]
                            })
        self.assertEqual(resp.get("status", 0), 200)
        self.assertTrue("info" in resp)
        for key in SAMPLE_INFO_FULL_RESPONSE["info"]:
            self.assertTrue(key in resp["info"])
            if key in USER1:
                self.assertEqual(resp["info"][key], USER1[key])
