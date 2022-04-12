import { configureStore } from '@reduxjs/toolkit'
import authReducer from '../slices/AuthSlice'
import transactionReducer from '../slices/TransactionSlice'
import accountReducer from '../slices/AccountSlice'

export default configureStore({
  reducer: {
    auth: authReducer,
    transaction: transactionReducer,
    account: accountReducer,
  },
})
