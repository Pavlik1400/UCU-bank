import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'

import fetchWithTimeout from '../fetcher'
import { BASIC_ROOT } from '../../../constants';


export const createTransaction = createAsyncThunk('transaction/createTransaction', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(auth_data)
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/transaction/create/', requestOptions)
    return response
})

export const getTransactions = createAsyncThunk('transaction/getTransactions', async (auth_data) => {
    var results = await Promise.all(auth_data["account_numbers"].map(async (value) => await fetchWithTimeout(BASIC_ROOT + '/transaction/get/', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({...auth_data, account_number: value}),
      })));
    let i = 0;
    var obj = results.reduce(function(o, val) { o[auth_data["account_numbers"][i]] = val["transactions"]; i = i + 1; return o; }, {});
    i = 0;
    var statuses = results.reduce(function(o, val) { o[auth_data["account_numbers"][i]] = val["status"]; i = i + 1; return o; }, {});

    return {"transactions": obj, "status": statuses }
})


export const transactionSlice = createSlice({
  name: 'transaction',
  initialState: {
    status: "idle",
    error: "",

    last_transactions: [],
  },
  reducers: {
    clearStatus: (state) => {
        state.status = "idle"
        state.error = ""
    },
  },

  extraReducers(builder) {
    builder
      .addCase(createTransaction.pending, (state, action) => {
        state.status = 'loading'
      })
      .addCase(createTransaction.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
        }
      })
      .addCase(createTransaction.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
      })

      .addCase(getTransactions.pending, (state, action) => {
        state.status = 'loading'
        state.last_transactions = []
      })
      .addCase(getTransactions.fulfilled, (state, action) => {
        state.status = 'succeeded'
        state.last_transactions = action.payload["transactions"]
      })
      .addCase(getTransactions.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
        state.last_transactions = []
      })
  }

})

// Action creators are generated for each case reducer function
export const { addTransaction, clearStatus } = transactionSlice.actions

export default transactionSlice.reducer