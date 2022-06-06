import { BASIC_ROOT } from "../../../constants"

const Logout = async (sessionToken) => {
    await fetch(BASIC_ROOT + "/user/logout/", {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            token: sessionToken
        })
    })
}


const getDataAboutUserFromAccount = async (sessionToken, account_number) => {
    const resp = await fetch(BASIC_ROOT + "/account/user_info/", {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            token: sessionToken,
            account_number: account_number
        })
    })
    return resp
}


const closeCredit = async (sessionToken, credit_id) => {
    const resp = await fetch(BASIC_ROOT + "/credit/finish/", {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            token: sessionToken,
            id: credit_id
        })
    })
    return resp
}


export { Logout, getDataAboutUserFromAccount, closeCredit }