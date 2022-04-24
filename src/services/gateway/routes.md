# API Routes

## Account API

- `POST http://localhost:2020/ucubank_api/v1/account/create/`

```json
{
  "user_id": "6255cbdb2890ea6b33749a52",
  "account_type": "sexy"
}
```

if user_id exists, response:

```json
{
  "status": 200
}
```

else something like that:

```json
{
  "message": "INVALID_USER_ID",
  "status": 400
}
```

- `GET http://localhost:2020/ucubank_api/v1/account/info/{number}`


if OK, response:

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

If not OK, response something like that:

```json
{
  "message": "INVALID_CARD_NUMBER",
  "status": 400
}
```

- `DELETE http://localhost:2020/ucubank_api/v1/account/remove/{number}`
  if number exists, response:

```json
{
  "status": 200
}
```

else something like that (**doesn't work yet**):

```json
{
  "message": "INVALID_CARD_NUMBER",
  "status": 400
}
```

## User API

- `POST http://localhost:2020/ucubank_api/v1/user/info/`

```json
{
  "phone_num": "+390961234567"
}
```

if OK, response:

```json
{
  "info": {
    "address": "toilet",
    "date_of_birth": "2945-05-08",
    "email": "m.halilei@ucu.edu.ua",
    "gender": "tractor",
    "id": "6255cbdb2890ea6b33749a53",
    "joining_date ": "12-04-2022 21-58-35",
    "name": "Masha",
    "phoneNo": "+390961234567",
    "type": "alpha female"
  },
  "status": 200
}
```

if not OK:

```json
{
  "message": "'name' field is is not present",
  "status": 400
}
```

or something like that:

```json
{
  "message": "USER_DOESNT_EXIST",
  "status": 400
}
```

- `POST http://localhost:2020/ucubank_api/v1/user/login1/`

```json
{
  "phone_num": "+390961234567",
  "hashed_password": "password"
}
```

If OK, response:

**NOTE**: one_time_passwd should come to email, only in a mock mode it is returned
```json
{
  "one_time_passwd": "820de4fd-55c9-4dc9-a54b-1234c9b98d99",
  "otp_key": "3cd8180b-4abf-47cb-b79d-4fd6f2b94373",
  "status": 200
}
```

If not OK, something like that:

```json
{
  "message": "'phone_num' field is is not present",
  "status": 400
}
```

- `POST http://localhost:2020/ucubank_api/v1/user/login2/`

```json
{
  "one_time_passwd": "820de4fd-55c9-4dc9-a54b-1234c9b98d99",
  "otp_key": "3cd8180b-4abf-47cb-b79d-4fd6f2b94373"
}
```

If OK, response:

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

if OK, response:

```json
{
  "status": 200
}
```

if not OK, something like that:

```json
{
  "message": "USER_EXISTS",
  "status": 400
}
```

- `DELETE http://localhost:2020/ucubank_api/v1/user/remove/`
```json
{
    "phoneNo": "+381235431256",
    "hashed_password": "123"
}
```

If OK, response: 

```json
{
    "status": 200
}
```

if not ok, something like that:

```json
{
    "message": "Incorrect password",
    "status": 403
}
```

Or that: 

```json
{
    "message": "USER_DOESNT_EXIST",
    "status": 400
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
  "category": 9
}
```

If OK, response is something like that:

```json
{
  "status": 200
}
```

if not OK, something like that:

```json
{
  "message": "'user_id' field is is not present",
  "status": 400
}
```

or like that:

```json
{
  "message": "FROM_ACCOUNT_DOESNT_EXISTS",
  "status": 400
}
```

- `POST http://localhost:2020/ucubank_api/v1/transaction/get/{account_number}`
  **Required only account_number and limit**

```json
{
  "min_amount": 0.0,
  "max_amount": 30.0,
  "description": "pizza",
  "category": 0,
  "from_date": "2022-01-01",
  "to_date": "2022-04-22",
  "limit": 100
}
```

if OK, resonse:

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

if not OK:

```json
{
  "message": "'limit' field is is not present",
  "status": 400
}
```

or: 

```json
{
    "message": "BAD_CATEGORY",
    "status": 400
}
```
