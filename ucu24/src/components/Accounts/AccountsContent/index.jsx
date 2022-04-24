import * as React from 'react';
import Paper from '@mui/material/Paper';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import { Box } from '@mui/system';
import { Button } from '@mui/material';
import { getUserAccounts } from '../../../store/slices/AccountSlice'
import { useSelector, useDispatch } from 'react-redux'

import CreateAccount from '../CreateAccount'


const adaptCVV = (cvv) => {return "***"}
const adaptBalance = (balance) => {return balance + "$"}
const adaptAny = (smthg) => {return smthg}


const AccountContent = () => {
    const dispatch = useDispatch()
    const logined = useSelector((state) => state.auth.logined)
    const uid = useSelector((state) => state.auth.uid)
    const accounts = useSelector((state) => state.account.accounts)

    React.useEffect(() => {
        if (logined) {
            dispatch(getUserAccounts({
                user_id: uid
            }))
        }
    }, [dispatch, logined, uid]);

    const openCreateAccountFunc = React.useRef(null)

    const aceptedKeys = {
        "Number": ["number", adaptAny], 
        "Opening date": ["opening_date", adaptAny],
        "Type": ["type", adaptAny],
        "CVV": ["cvv", adaptCVV],
        "Balance": ["balance", adaptBalance], 
    };

    return (
    <div>
        {logined && <Box sx={{
            mt: "3rem",
            mx: "7rem",
            height: "100vh",
        }}>
        <Grid container spacing={20}>
            <Grid item xs={2}></Grid>
            <Grid item xs>
            <Paper sx={{ width: '100%', }}>
                    <Box sx={{ mt: 1, mx: 2 }} alignItems="center">
                        <Grid container >
                        <Grid item xs sx={{ mt: 1 }}>
                            <Typography variant="h4">
                                Accounts
                            </Typography>
                        </Grid>
                        <Grid item xs={2} sx={{ mt: 1 }}>
                            <Button variant="contained" onClick={() => {
                                    openCreateAccountFunc.current();
                                }}>New Account</Button>
                        </Grid>
                        </Grid>
                    </Box>
                    <Box>
                    <TableContainer component={Paper}>
                    <Table sx={{ minWidth: 650 }} aria-label="simple table">
                        <TableHead>
                        <TableRow>
                            {
                                Object.keys(aceptedKeys).map((key, index) => ( 
                                    <TableCell align="right" key={index}>{key}</TableCell>
                                ))
                            }
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {accounts.map((row, idx) => (
                            <TableRow
                            key={idx}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                            >
                            {
                                Object.keys(aceptedKeys).map((key, index) => ( 
                                    <TableCell align="right" key={index}>{aceptedKeys[key][1](row[aceptedKeys[key][0]])}</TableCell>
                                ))
                            }
                            </TableRow>
                        ))}
                        </TableBody>
                    </Table>
                    </TableContainer>
                    </Box>
                </Paper>
            </Grid>
            <Grid item xs={2}></Grid>
            </Grid>

            <CreateAccount openCreateAccountFunc={openCreateAccountFunc}></CreateAccount>
        </Box> }
    </div>
  );
}

export default AccountContent;