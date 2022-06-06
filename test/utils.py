import json
import random
import string
from dataclasses import dataclass
from pprint import pprint
from typing import List, Dict

import requests

ALLOWED_CHARS = string.ascii_uppercase + string.ascii_lowercase + string.digits

HEADERS = {
    'Content-Type': 'application/json'
}


class Colors:
    CEND = '\33[0m'
    CBOLD = '\33[1m'
    CITALIC = '\33[3m'
    CURL = '\33[4m'
    CBLINK = '\33[5m'
    CBLINK2 = '\33[6m'
    CSELECTED = '\33[7m'

    CBLACK = '\33[30m'
    CRED = '\33[31m'
    CGREEN = '\33[32m'
    CYELLOW = '\33[33m'
    CBLUE = '\33[34m'
    CVIOLET = '\33[35m'
    CBEIGE = '\33[36m'
    CWHITE = '\33[37m'

    CBLACKBG = '\33[40m'
    CREDBG = '\33[41m'
    CGREENBG = '\33[42m'
    CYELLOWBG = '\33[43m'
    CBLUEBG = '\33[44m'
    CVIOLETBG = '\33[45m'
    CBEIGEBG = '\33[46m'
    CWHITEBG = '\33[47m'

    CGREY = '\33[90m'
    CRED2 = '\33[91m'
    CGREEN2 = '\33[92m'
    CYELLOW2 = '\33[93m'
    CBLUE2 = '\33[94m'
    CVIOLET2 = '\33[95m'
    CBEIGE2 = '\33[96m'
    CWHITE2 = '\33[97m'

    CGREYBG = '\33[100m'
    CREDBG2 = '\33[101m'
    CGREENBG2 = '\33[102m'
    CYELLOWBG2 = '\33[103m'
    CBLUEBG2 = '\33[104m'
    CVIOLETBG2 = '\33[105m'
    CBEIGEBG2 = '\33[106m'
    CWHITEBG2 = '\33[107m'


def print_header(txt: str):
    print(Colors.CBEIGE, end="")
    print("#" * 60)
    print(txt)
    print("#" * 60)
    print(Colors.CEND)


def gen_random_string(n: int):
    return ''.join(random.choice(ALLOWED_CHARS) for _ in range(n))


def make_request(route: str, headers=None, data="", method="post"):
    if headers is None:
        headers = HEADERS

    if method == "post":
        req = requests.post
    elif method == "delete":
        req = requests.delete
    else:
        raise ValueError(f"Unknown request method: {method}")

    print(Colors.CYELLOW, end="")
    print(f">>> Making request: ")
    pprint({
        "ROUTE": route,
        "HEADERS": headers,
        "DATA": data,
        "METHOD": method,
    })

    resp = req(route, headers=headers, data=json.dumps(data))
    # print("<><><><>")
    # print(resp.text)
    resp = resp.json()

    print(Colors.CGREEN)
    print(f"<<< Reponse: ")
    pprint(resp)
    print(Colors.CEND)
    return resp


@dataclass
class GlobalState:
    TOKEN1: str = "None"
    UID1: str = "None"
    OTP1: str = "None"
    OTP_KEY1: str = "None"
    USER1_ACCOUNTS: List = None
    USER1: Dict = None
    CRED_ID1: str = None

    TOKEN2: str = "None"
    UID2: str = "None"
    OTP2: str = "None"
    OTP_KEY2: str = "None"
    USER2_ACCOUNTS: List = None
    USER2: Dict = None

    def __init__(self):
        self.USER1_ACCOUNTS = []
        self.USER2_ACCOUNTS = []

        self.USER1 = {
            "type": "regular",
            "name": "user1",
            "password": gen_random_string(20),
            "date_of_birth": "2001-01-01",
            "phone_num": gen_random_string(20),
            "email": "user1@gmail.com",
            "address": "1",
            "gender": "user1"
        }

        self.USER2 = {
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


state = GlobalState()
