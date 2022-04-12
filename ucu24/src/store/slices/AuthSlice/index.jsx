import { createSlice } from '@reduxjs/toolkit'

export const authSlice = createSlice({
  name: 'auth',
  initialState: {
    logined: false,
    sessionToken: "",
  },
  reducers: {
    login: (state, action) => {
        state.logined = true;
        state.sessionTOken = "";
    },
    exit: (state) => {
        state.logined = false;
        state.sessionTOken = "";
    },
  },
})

// Action creators are generated for each case reducer function
export const { login, exit } = authSlice.actions

export default authSlice.reducer