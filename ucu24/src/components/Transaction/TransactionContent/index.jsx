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
import { useSelector, useDispatch } from 'react-redux'
import { getTransactions } from '../../../store/slices/TransactionSlice'
import { getUserAccounts } from '../../../store/slices/AccountSlice'
import NewTransaction from '../NewTransaction'


const adaptAny = (smthg) => {return smthg}
const adaptAmount = (balance) => {return balance + "$"}


const Transaction = () => {
    const dispatch = useDispatch()
    const accounts = useSelector((state) => state.account.accounts)
    const logined = useSelector((state) => state.auth.logined)
    const uid = useSelector((state) => state.auth.uid)
    const last_transactions = useSelector((state) => state.transaction.last_transactions)
    const openTransactionFunc = React.useRef(null)

    React.useEffect(() => {
        if (logined) {
            dispatch(getUserAccounts({
                user_id: uid
            }))
        }
    }, [dispatch, logined, uid]);

    React.useEffect(() => {
        if (logined) {
            dispatch(getTransactions({
                account_numbers: accounts.map((account) => account["number"]),
                limit: 100,
            }))
        }
    }, [accounts, dispatch, logined]);

    const aceptedKeys = {
        "From": ["from_acc_number", adaptAny], 
        "To": ["to_acc_number", adaptAny],
        "Amount": ["amount", adaptAmount],
        "Category": ["category", adaptAny],
        "Date": ["date", adaptAny], 
        "Description": ["description", adaptAny], 
    };

    const [filteredTransactions, setFilteredTransactions] = React.useState([]);
    React.useEffect(() => {
        var tmp = [].concat.apply([], Object.keys(last_transactions).map((key) => [...last_transactions[key]]))
        tmp = tmp.filter((value, index, self) =>
            index === self.findIndex((t) => (
                t.from_acc_number === value.from_acc_number && t.to_acc_number === value.to_acc_number && t.amount === value.amount
                && t.category === value.category && t.date === value.date && t.description === value.description
            ))
        )
        setFilteredTransactions(tmp)
    }, [last_transactions]);

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
                            {
                                Object.keys(aceptedKeys).map((key, index) => ( 
                                    <TableCell align="right" key={index}>{key}</TableCell>
                                ))
                            }
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {filteredTransactions.map((transactions_from_account, idx) => (
                            <TableRow
                            key={idx}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                            >
                            {
                                Object.keys(aceptedKeys).map((kkey, iindex) => ( 
                                    <TableCell align="right" key={iindex}>{aceptedKeys[kkey][1](transactions_from_account[aceptedKeys[kkey][0]])}</TableCell>
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
            <NewTransaction openTransactionFunc={openTransactionFunc}/>
        </Box> }
    </div>
  );
}

export default Transaction;