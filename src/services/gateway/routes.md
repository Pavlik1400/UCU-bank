# API Routes
## Users API
- `POST http://localhost:2020/ucubank_api/v1/account/create/` 
```json
{
  "user_id": "6255cbdb2890ea6b33749a52",
  "account_type": "sexy"
}
```
if user_id exists, response: 
```json
{ "status": 200 }
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
{
  "detailed": true
}
```
(detailed allowed when authorized user gets info about (him/her/it/)self)

if number exists and `detailed=true`, response:
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
if number exists and `detailed=false`, responnse:
```json
{
    "info": {
        "active": true,
        "number": "2941348868703448",
        "user_id": "6255cbdb2890ea6b33749a53"
    },
    "status": 200
}
```
if number exists and user is not allowed to use detailed:
```json
{
  "message": "DETAILED_FORBIDDEN",
  "status": 403
}
```

else something like that:
```json
{
  "message": "INVALID_CARD_NUMBER",
  "status": 400
}
```

- `DELETE http://localhost:2020/ucubank_api/v1/account/remove/{number}`
if number exists, response:
```json
{ "status": 200 }
```
else something like that (**doesn't work yet**):
```json
{
  "message": "INVALID_CARD_NUMBER",
  "status": 400
}
```
