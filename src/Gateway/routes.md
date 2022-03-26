# API Routes
## Users API

- `GET /user/info/{login}`- get user info. Required json fields: 
```json
{
  "id": "Optional[u64]"
}
```
->
```json
[
  "fname", "lname", "balance"
]
```
- `GET /user/login/{login}` - login user
```json
{
  "hash": "str"
}
```
- `POST /user/register/{login}` - register user
```json
{
  "login": "str",
  "fname": "str",
  "lname": "str",
  "password": "hash(str)",
  "email": "str.email",
  "phone": "str.phone",
  "passport_id": "u64"
}
```

