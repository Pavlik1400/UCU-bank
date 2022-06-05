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


const getDataAboutUserFromAccount = async (sessionToken, number) => {
    await fetch(BASIC_ROOT + "/user/AAAAAAAAAAAAA/", {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
            token: sessionToken,
            number: number
        })
    })
}


export { Logout, getDataAboutUserFromAccount }