import { createSlice } from '@reduxjs/toolkit'

function makeid(length) {
    var result           = '';
    var characters       = '0123456789';
    var charactersLength = characters.length;
    for ( var i = 0; i < length; i++ ) {
      result += characters.charAt(Math.floor(Math.random() * 
 charactersLength));
   }
   return result;
}

export const accountSlice = createSlice({
  name: 'account',
  initialState: {
    accounts: [
        {
            "number": "1234567812345678",
            "amount": 1000
        },
        {
            "number": "0987654312345123",
            "amount": 5000
        },
    ],
  },
  reducers: {
    addAccount: (state, action) => {
        const newAcc = makeid(16);
        state.accounts.push({
            "number": newAcc,
            "amount": 0
        })
    },

    makeAccoutTransaction: (state, action) => {
        let flag_from = false;
        let elem_from = 0;
        let flag_to = false;
        let elem_to = 0;

        for (let index = 0; index < state.accounts.length; index++) {
            if (state.accounts[index]["number"] === action.payload["from"]) {
                flag_from = true;
                elem_from = index;
            }
            if (state.accounts[index]["number"] === action.payload["to"]) {
                flag_to = true;
                elem_to = index;
            }
        }

        if (flag_from && flag_to) {
            state.accounts[elem_from]["amount"] -= parseInt(action.payload["amount"]);
            state.accounts[elem_to]["amount"] += parseInt(action.payload["amount"]);
        }
    },
  },
})

// Action creators are generated for each case reducer function
export const { makeAccoutTransaction, addAccount } = accountSlice.actions

export default accountSlice.reducer