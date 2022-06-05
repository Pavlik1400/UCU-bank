import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'

import fetchWithTimeout from '../fetcher'
import { BASIC_ROOT } from '../../../constants';


export const login1 = createAsyncThunk('auth/login1', async (auth_data) => {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json;charset=utf-8' },
    body: JSON.stringify(auth_data)
  };
  const response = await fetchWithTimeout(BASIC_ROOT + '/user/login1/', requestOptions)
  return response
})


export const login2 = createAsyncThunk('auth/login2', async (auth_data) => {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(auth_data)
  };
  const response = await fetchWithTimeout(BASIC_ROOT + '/user/login2/', requestOptions)
  return response
})


export const register = createAsyncThunk('auth/register', async (account_details) => {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(account_details)
  };
  const response = await fetchWithTimeout(BASIC_ROOT + '/user/register/', requestOptions)
  return response
})


export const getUserData = createAsyncThunk('auth/getUserData', async (user_data) => {
  const requestOptions = {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(user_data)
  };
  const response = await fetchWithTimeout(BASIC_ROOT + '/user/info/', requestOptions)
  return response
})


export const authSlice = createSlice({
  name: 'auth',
  initialState: {
    status: 'idle',
    error: "",

    logined: false,

    otp_key: "",
    sessionToken: "",
    uid: "",
    phone_num: "",
    account: {}
  },
  reducers: {
    exit: (state) => {
      state.logined = false;
      state.sessionToken = "";
    },
    setPhoneNum: (state, action) => {
      state.phone_num = action.payload["phone_num"]
    },
  },

  extraReducers(builder) {
    builder
      .addCase(login1.pending, (state, action) => {
        state.status = 'loading'
        state.error = ""
        state.otp_key = ""
      })
      .addCase(login1.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
          state.otp_key = action.payload["otp_key"]
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
          state.otp_key = ""
        }
      })
      .addCase(login1.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
        state.otp_key = ""
      })

      .addCase(login2.pending, (state, action) => {
        state.status = 'loading'
        state.otp_key = ""
        state.sessionToken = ""
        state.uid = ""
        state.error = ""
      })
      .addCase(login2.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
          state.logined = true;
          state.sessionToken = action.payload["token"];
          state.uid = action.payload["uid"];
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
          state.logined = false;
          state.sessionToken = "";
          state.uid = "";
        }
      })
      .addCase(login2.rejected, (state, action) => {
        state.status = 'failed'
        state.logined = false;
        state.sessionToken = ""
        state.uid = ""
        state.error = action.error.message
      })

      .addCase(getUserData.pending, (state, action) => {
        state.status = 'loading'
        state.account = {}
      })
      .addCase(getUserData.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
          state.account = action.payload["info"]
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
          state.account = {}
        }
      })
      .addCase(getUserData.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
        state.account = {}
      })
  }
})

export const { exit, setPhoneNum } = authSlice.actions

export default authSlice.reducer