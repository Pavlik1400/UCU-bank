import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'

import fetchWithTimeout from '../fetcher'
import { BASIC_ROOT } from '../../../constants';


export const createAccount = createAsyncThunk('account/createAccount', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(auth_data)
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/account/create/', requestOptions)
    return response
})

export const getAccountInfo = createAsyncThunk('account/getAccountInfo', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(auth_data)
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/account/info/', requestOptions)
    return response
})

export const getUserAccounts = createAsyncThunk('account/getUserAccounts', async (auth_data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(auth_data),
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/account/get_accounts/', requestOptions)
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