# API Routes

## Account API

- `POST http://localhost:2020/ucubank_api/v1/account/create/`

```json
{
  "token": "123",
  "user_id": "6255cbdb2890ea6b33749a52",
  "account_type": "sexy"
}
```

Reponse:

```json
{
  "status": 200
}
```

- `POST http://localhost:2020/ucubank_api/v1/account/info/{number}`

```json
{
  "token": "123"
}
```

Reponse if user is owner of account:

```json
{
  "info": {
    "active": true,
    "balance": 0.0,
    "cvv": "068",
    "id": "",
    "number": "2941348868703448",
    "opening_date": "16-04-2022 12-34-39",
    "type": "sexy",
    "user_id": "6255cbdb2890ea6b33749a53"
  },
  "status": 200
}
```

Response if user is not a owner of an account:

```json
{
    "info": {
        "active": true,
        "balance": 0.0,
        "number": "6744440301848953"
    },
    "status": 200
}
```


- `DELETE http://localhost:2020/ucubank_api/v1/account/remove/{number}`

```json
{
  "token": "123"
}
```

  if number exists, response, and user is SUPER:

```json
{
  "status": 200
}
```

- `POST http://localhost:2020/ucubank_api/v1/account/get_accounts/{user_id}`

```json
{
  "token": "token"
}
```

Response if user is an owner of the account: 

```json
{
  "accounts": [
    {
      "active": true,
      "balance": 0.0,
      "number": "5637677951177198",
      "opening_date": "02-06-2022 22-31-19",
      "type": "sexy",
      "user_id": "629902cebe1eb222c26ef0c2"
    },
    {
      "active": true,
      "balance": 3029.3200000000002,
      "number": "0588093921849362",
      "opening_date": "02-06-2022 22-56-20",
      "type": "sexy2",
      "user_id": "629902cebe1eb222c26ef0c2"
    }
  ],
  "status": 200
}
```

Response if user is not an owner of an account:

```json
{
    "accounts": [
        {
            "active": true,
            "balance": 0.0,
            "number": "6744440301848953"
        }
    ],
    "status": 200
}
```
## User API

- `POST http://localhost:2020/ucubank_api/v1/user/info/`

```json
{
  "token": "token",
  "phone_num": "+390961234567"
}
```

Response if user is asking info about him/her/it self:

```json
{
  "info": {
    "address": "home",
    "date_of_birth": "2002-02-02",
    "email": "pasha@gmail.com",
    "gender": "airbus 777",
    "id": "629902cebe1eb222c26ef0c2",
    "joining_date": "02-06-2022 21-34-54",
    "name": "pasha",
    "phoneNo": "123",
    "type": "regular"
  },
  "status": 200
}
```

Response if user is asking info about other user:

```json
{
    "info": {
        "email": "pasha@gmail.com",
        "name": "pasha",
        "type": "super"
    },
    "status": 200
}
```

- `POST http://localhost:2020/ucubank_api/v1/user/login1/`

```json
{
  "phone_num": "+390961234567",
  "password": "password"
}
```

Response:

**NOTE**: one_time_passwd should come to email, only in a mock mode it is returned
```json
{
  "one_time_passwd": "820de4fd-55c9-4dc9-a54b-1234c9b98d99",
  "otp_key": "3cd8180b-4abf-47cb-b79d-4fd6f2b94373",
  "status": 200
}
```

- `POST http://localhost:2020/ucubank_api/v1/user/login2/`

```json
{
  "one_time_passwd": "820de4fd-55c9-4dc9-a54b-1234c9b98d99",
  "otp_key": "3cd8180b-4abf-47cb-b79d-4fd6f2b94373"
}
```

Response:

```json
{
  "status": 200,
  "token": "3b17e871-6fe3-47c2-8b29-7be87ec9a426",
  "uid": "6255cbdb2890ea6b33749a53"
}
```

- `POST http://localhost:2020/ucubank_api/v1/user/register/`

```json
{
  "type": "1",
  "name": "Kashaa",
  "password": "123",
  "date_of_birth": "2001-01-01",
  "phoneNo": "+381235431256",
  "email": "kasha@gmail.com",
  "address": "11",
  "gender": "helicopter"
}
```

Response:

```json
{
  "status": 200
}
```

- `DELETE http://localhost:2020/ucubank_api/v1/user/remove/`

*Only super can remove users*
```json
{
    "phoneNo": "+381235431256",
    "password": "123",
    "token": "123"
}
```

Response: 

```json
{
    "status": 200
}
```

## Transaction API

- `POST http://localhost:2020/ucubank_api/v1/transaction/create/`

```json
{
  "user_id": "62607d5616a90a56c374e652",
  "from_acc_number": "2941348868703448",
  "to_acc_number": "0344745254739653",
  "description": "pizza2",
  "amount": 20.0,
  "category": 9,
  "token": "123"
}
```

Reponse:

```json
{
  "status": 200
}
```

- `POST http://localhost:2020/ucubank_api/v1/transaction/get/{account_number}`
  
**Required only 'account_number' and 'limit'**

```json
{
  "min_amount": 0.0,
  "max_amount": 30.0,
  "description": "pizza",
  "category": 0,
  "from_date": "2022-01-01",
  "to_date": "2022-04-22",
  "limit": 100,
  "token": "123"
}
```

Reponse

```json
{
  "status": 200,
  "transactions": [
    {
      "amount": 20.0,
      "category": 0,
      "date": "2022-04-21 01:07:41.403",
      "description": "pizza",
      "from_acc_number": "2941348868703448",
      "to_acc_number": "344745254739653"
    },
    {
      "amount": 20.0,
      "category": 0,
      "date": "2022-04-21 01:08:17.528",
      "description": "pizza1",
      "from_acc_number": "2941348868703448",
      "to_acc_number": "344745254739653"
    }
  ]
}
```