import { createSlice } from '@reduxjs/toolkit'

export const transactionSlice = createSlice({
  name: 'transaction',
  initialState: {
    last_transactions: [
        {
            "from": "1234567812345678",
            "to": "0987654312345123",
            "amount": 1395,
            "date": "22.06.2021",
            "time": "14:30",
        },
        {
            "from": "0987654312345123",
            "to": "1234567812345678",
            "amount": 24.9,
            "date": "22.06.2021",
            "time": "14:30",
        },
        {
            "from": "1234567812345678",
            "to": "0987654312345123",
            "amount": 1395,
            "date": "22.06.2021",
            "time": "14:30",
        },
        {
            "from": "0987654312345123",
            "to": "1234567812345678",
            "amount": 24.9,
            "date": "22.06.2021",
            "time": "14:30",
        },
        {
            "from": "1234567812345678",
            "to": "0987654312345123",
            "amount": 1395,
            "date": "22.06.2021",
            "time": "14:30",
        },
        {
            "from": "0987654312345123",
            "to": "1234567812345678",
            "amount": 24.9,
            "date": "22.06.2021",
            "time": "14:30",
        },
    ],
  },
  reducers: {
    addTransaction: (state, action) => {
        state.last_transactions.push(action.payload);
    },
  },
})

// Action creators are generated for each case reducer function
export const { addTransaction } = transactionSlice.actions

export default transactionSlice.reducer