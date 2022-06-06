/* eslint-disable no-undef */
/* eslint-disable no-underscore-dangle */
import React from 'react'
import ReactDOM from "react-dom/client";
import {
  BrowserRouter as Router,
  Routes,
  Route
} from "react-router-dom";
import { green, lime } from '@mui/material/colors';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline'
import { Provider } from 'react-redux'

import store from './store/redux'
import MainPageView from './views/MainPage'
import TransactionView from './views/TransactionPage'
import AccountView from './views/AccountPage'
import CreditView from './views/CreditPage'

const mainTheme = createTheme({
  palette: {
    secondary: {
      main: lime[200],
    },
    primary: {
      main: green[300],
    },
  },
  overrides: {
    MuiCssBaseline: {
      '@global': {
        html: {
          height: '100%',
        },
        body: {
          height: '100%',
          '& .rootElement': {
            height: '100%',
          },
        },
        "& .MuiCardHeader-avatar": {
          marginRight: 0
        }
      },
    },
  },
});


const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(
  <React.StrictMode>
    <Provider store={store}>
    <CssBaseline />
    <ThemeProvider theme={mainTheme}>
      <Router>
        <Routes>
          <Route path='/' element={<MainPageView/>} />
          <Route path='/transactions' element={<TransactionView/>} />
          <Route path='/accounts' element={<AccountView/>} />
          <Route path='/credits' element={<CreditView/>} />
        </Routes>
      </Router>
    </ThemeProvider>
    </Provider>
  </React.StrictMode>
)