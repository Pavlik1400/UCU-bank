import { createSlice } from '@reduxjs/toolkit'

export const authSlice = createSlice({
  name: 'auth',
  initialState: {
    logined: false,
    sessionToken: "",
    account: {
      "name": "Yevnen",
      "surname": "Pankevych",
      "phone": "+380123456789",
      "address": "Lviv, Antonovycha 256",
  }
  },
  reducers: {
    login: (state, action) => {
        state.logined = true;
        state.sessionTOken = "";
    },
    register: (state, action) => {
      state.logined = true;
      state.sessionTOken = "";
      state.account = action.payload
  },
    exit: (state) => {
        state.logined = false;
        state.sessionTOken = "";
    },
  },
})

// Action creators are generated for each case reducer function
export const { login, exit, register } = authSlice.actions

export default authSlice.reducer