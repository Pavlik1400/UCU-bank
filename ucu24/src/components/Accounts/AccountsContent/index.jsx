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
import { addAccount } from '../../../store/slices/AccountSlice'
import { useSelector, useDispatch } from 'react-redux'


const AccountContent = () => {
    const dispatch = useDispatch()
    const logined = useSelector((state) => state.auth.logined)
    const accounts = useSelector((state) => state.account.accounts)

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
                                dispatch(addAccount());
                                }}>New Account</Button>
                        </Grid>
                        </Grid>
                    </Box>
                    <Box>
                    <TableContainer component={Paper}>
                    <Table sx={{ minWidth: 650 }} aria-label="simple table">
                        <TableHead>
                        <TableRow>
                            <TableCell>Idx</TableCell>
                            <TableCell align="right">Number</TableCell>
                            <TableCell align="right">Amount</TableCell>
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {accounts.map((row, idx) => (
                            <TableRow
                            key={idx}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                            >
                            <TableCell component="th" scope="row">{idx}</TableCell>
                            <TableCell align="right">{row["number"]}</TableCell>
                            <TableCell align="right">{row["amount"]}$</TableCell>
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
        </Box> }
    </div>
  );
}

export default AccountContent;