import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'

import fetchWithTimeout from '../fetcher'


export const createAccount = createAsyncThunk('account/createAccount', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(auth_data)
    };
    const response = await fetchWithTimeout('http://localhost:2020/ucubank_api/v1/account/create/', requestOptions)
    return response
})

export const getAccountInfo = createAsyncThunk('account/getAccountInfo', async (auth_data) => {
    const requestOptions = {
        method: 'GET',
        headers: { 'Content-Type': 'application/json' },
    };
    const response = await fetchWithTimeout('http://localhost:2020/ucubank_api/v1/account/info/' + auth_data["number"], requestOptions)
    return response
})

export const getUserAccounts = createAsyncThunk('account/getUserAccounts', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({}),
    };
    const response = await fetchWithTimeout('http://localhost:2020/ucubank_api/v1/account/get_accounts/' + auth_data["user_id"], requestOptions)
    return response
})


export const accountSlice = createSlice({
  name: 'account',
  initialState: {
    status: "idle",
    error: "",

    accounts: [],
  },
  reducers: {
    clearStatus: (state) => {
        state.status = "idle"
        state.error = ""
    },
  },

extraReducers(builder) {
    builder
      .addCase(createAccount.pending, (state, action) => {
        state.status = 'loading'
      })
      .addCase(createAccount.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
        }
      })
      .addCase(createAccount.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
      })

      .addCase(getUserAccounts.pending, (state, action) => {
        state.status = 'loading'
        state.accounts = []
      })
      .addCase(getUserAccounts.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
          state.accounts = action.payload["accounts"]
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
          state.accounts = []
        }
      })
      .addCase(getUserAccounts.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
        state.accounts = []
      })
  }

})

// Action creators are generated for each case reducer function
export const { clearStatus } = accountSlice.actions

export default accountSlice.reducer