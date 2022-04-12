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
import { useSelector } from 'react-redux'

import NewTransaction from '../NewTransaction'

const Transaction = () => {
    const logined = useSelector((state) => state.auth.logined)
    const last_transactions = useSelector((state) => state.transaction.last_transactions)
    const openTransactionFunc = React.useRef(null)

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
                                Transactions
                            </Typography>
                        </Grid>
                        <Grid item xs={2} sx={{ mt: 1 }}>
                            <Button variant="contained" onClick={() => {
                                openTransactionFunc.current();
                                }}>New Transaction</Button>
                        </Grid>
                        </Grid>
                    </Box>
                    <Box>
                    <TableContainer component={Paper}>
                    <Table sx={{ minWidth: 650 }} aria-label="simple table">
                        <TableHead>
                        <TableRow>
                            <TableCell>Idx</TableCell>
                            <TableCell align="right">From</TableCell>
                            <TableCell align="right">To</TableCell>
                            <TableCell align="right">Amount</TableCell>
                            <TableCell align="right">Date</TableCell>
                            <TableCell align="right">Time</TableCell>
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {last_transactions.map((row, idx) => (
                            <TableRow
                            key={idx}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                            >
                            <TableCell component="th" scope="row">{idx}</TableCell>
                            <TableCell align="right">{row["from"]}</TableCell>
                            <TableCell align="right">{row["to"]}</TableCell>
                            <TableCell align="right">{row["amount"]}$</TableCell>
                            <TableCell align="right">{row["date"]}</TableCell>
                            <TableCell align="right">{row["time"]}</TableCell>
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
            <NewTransaction openTransactionFunc={openTransactionFunc}/>
        </Box> }
    </div>
  );
}

export default Transaction;