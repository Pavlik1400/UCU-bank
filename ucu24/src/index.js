/* eslint-disable no-undef */
/* eslint-disable no-underscore-dangle */
import React from 'react'
import ReactDOM from 'react-dom'
import {
  BrowserRouter as Router,
  Routes,
  Route
} from "react-router-dom";

import { green, lime } from '@mui/material/colors';
import { createTheme, ThemeProvider } from '@mui/material/styles';

import CssBaseline from '@mui/material/CssBaseline'
import MainPageView from './views/MainPage'

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
      },
    },
  },
});


ReactDOM.render(
  <React.StrictMode>
    <CssBaseline />
    <ThemeProvider theme={mainTheme}>
      <Router>
        <Routes>
          <Route path='/' element={<MainPageView/>} />
        </Routes>
      </Router>
    </ThemeProvider>
  </React.StrictMode>,

  document.getElementById('root'),
)