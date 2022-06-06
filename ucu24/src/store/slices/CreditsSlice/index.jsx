import { createSlice, createAsyncThunk } from '@reduxjs/toolkit'

import fetchWithTimeout from '../fetcher'
import { BASIC_ROOT } from '../../../constants';


export const createCredit = createAsyncThunk('credit/createCredit', async (data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data)
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/credit/create/', requestOptions)
    return response
})

export const getCredits = createAsyncThunk('credit/getCredits', async (data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data)
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/credit/get/', requestOptions)
    return response
})

export const finishCredit = createAsyncThunk('credit/finishCredit', async (data) => {
    const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(data),
    };
    const response = await fetchWithTimeout(BASIC_ROOT + '/credit/finish/', requestOptions)
    return response
})


export const creditSlice = createSlice({
  name: 'credit',
  initialState: {
    status: "idle",
    error: "",

    credits: [],
  },
  reducers: {
    clearStatus: (state) => {
        state.status = "idle"
        state.error = ""
    },
  },

extraReducers(builder) {
    builder
      .addCase(createCredit.pending, (state, action) => {
        state.status = 'loading'
      })
      .addCase(createCredit.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
        }
      })
      .addCase(createCredit.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
      })

      .addCase(getCredits.pending, (state, action) => {
        state.status = 'loading'
        state.credits = []
      })
      .addCase(getCredits.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
          state.credits = action.payload["credits"]
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
          state.credits = []
        }
      })
      .addCase(getCredits.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
        state.credits = []
      })

      .addCase(finishCredit.pending, (state, action) => {
        state.status = 'loading'
        state.credits = []
      })
      .addCase(finishCredit.fulfilled, (state, action) => {
        if (action.payload["status"] === 200) {
          state.status = 'succeeded'
        } else {
          state.status = 'failed'
          state.error = action.payload["message"]
        }
      })
      .addCase(finishCredit.rejected, (state, action) => {
        state.status = 'failed'
        state.error = action.error.message
      })
  }

})

// Action creators are generated for each case reducer function
export const { clearStatus } = creditSlice.actions

export default creditSlice.reducer