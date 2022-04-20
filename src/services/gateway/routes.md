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

```json
{}
```

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

- `GET http://localhost:2020/ucubank_api/v1/user/info/`

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

- `GET http://localhost:2020/ucubank_api/v1/user/login1/`

```json
{
  "name": "Masha",
  "phone_num": "+390961234567",
  "hashed_password": "password"
}
```

If OK, response:

```json
{
  "status": 200,
  "auth_id": "abrakadabra"
}
```

If not OK, something like that:

```json
{
  "message": "MAIL_FAILED",
  "status": 400
}
```

- `GET http://localhost:2020/ucubank_api/v1/user/login2/`

```json
{
  "auth_id": "1234",
  "secret": "3214"
}
```

If OK, response:

```json
{
  "status": 200,
  "token": "abrakadabra"
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