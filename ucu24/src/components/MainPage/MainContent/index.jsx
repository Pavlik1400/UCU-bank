import * as React from 'react';
import Paper from '@mui/material/Paper';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';
import AccountBalanceWalletIcon from '@mui/icons-material/AccountBalanceWallet';
import MoveDownIcon from '@mui/icons-material/MoveDown';
import Card from '@mui/material/Card';
import Divider from '@mui/material/Divider';
import CardContent from '@mui/material/CardContent';
import CardMedia from '@mui/material/CardMedia';
import { Box } from '@mui/system';
import { CardActionArea } from '@mui/material';
import { useSelector, useDispatch } from 'react-redux'

import { getUserAccounts } from '../../../store/slices/AccountSlice'
import { getTransactions } from '../../../store/slices/TransactionSlice'


const MainContent = () => {
    const dispatch = useDispatch()
    const logined = useSelector((state) => state.auth.logined)
    const uid = useSelector((state) => state.auth.uid)
    const sessionToken = useSelector((state) => state.auth.sessionToken)
    const last_transactions = useSelector((state) => state.transaction.last_transactions)
    const accounts = useSelector((state) => state.account.accounts)

    React.useEffect(() => {
        if (logined) {
            dispatch(getUserAccounts({
                user_id: uid,
                token: sessionToken
            }))
        }
    }, [dispatch, logined, uid, sessionToken]);

    React.useEffect(() => {
        if (logined) {
            dispatch(getTransactions({
                account_numbers: accounts.map((account) => account["number"]),
                limit: 100,
                token: sessionToken
            }))
        }
    }, [accounts, dispatch, logined, sessionToken]);

    const [filteredTransactions, setFilteredTransactions] = React.useState([]);
    React.useEffect(() => {
        var tmp = [].concat.apply([], Object.keys(last_transactions).map((key) => [...last_transactions[key]]))
        tmp = tmp.filter((value, index, self) =>
            index === self.findIndex((t) => (
                t.from_acc_number === value.from_acc_number && t.to_acc_number === value.to_acc_number && t.amount === value.amount
                && t.category === value.category && t.date === value.date && t.description === value.description
            ))
        )
        tmp.sort(function(a, b) {
            var keyA = new Date(a.date),
              keyB = new Date(b.date);
            if (keyA < keyB) return 1;
            if (keyA > keyB) return -1;
            return 0;
          });
        setFilteredTransactions(tmp)
    }, [last_transactions]);



    return (
    <div>
        {logined && <Box sx={{
            mt: "3rem",
            mx: "7rem",
            height: "100vh",
        }}>
        <Grid container spacing={10}>
            <Grid item xs={2}></Grid>
            <Grid item xs>
                <Paper sx={{ width: '100%', }}>
                    <Box sx={{ mt: 1, mx: 2 }} alignItems="center">
                        <Grid container >
                        <Grid item xs={2} sx={{ mt: 1 }}>
                            <AccountBalanceWalletIcon sx={{ fontSize: 24, mt: 0.5 }} />
                        </Grid>
                        <Grid item xs sx={{ mt: 1 }}>
                            <Typography variant="h5">
                                Accounts
                            </Typography>
                        </Grid>
                        </Grid>
                    </Box>
                    <Box sx={{ m: 2 }}>
                        {accounts.slice(-3).map((value, idx) => {
                            return (
                                <Box sx={{ mt: 2.5, pb: 2.5 }} key={idx}>
                                    <Card sx={{ padding: "1rem" }}>
                                    <CardActionArea sx={{ display: 'flex', justifyContent: "space-around"  }}>
                                        <Box sx={{ display: 'flex' }}>
                                            <CardContent sx={{ flex: '1 0 auto' }}>
                                                <Typography component="div" variant="h6">
                                                    *{value["number"].substring(12, 16)}
                                                </Typography>
                                                <Typography variant="subtitle2" color="text.secondary" component="div">
                                                {Math.round(value["balance"] * 100) / 100}$
                                                </Typography>
                                            </CardContent>
                                        </Box>
                                        <CardMedia
                                            component="img"
                                            sx={{ width: 60 }}
                                            image="https://d1nhio0ox7pgb.cloudfront.net/_img/g_collection_png/standard/512x512/credit_card.png"
                                            alt="credit_card"
                                        />
                                    </CardActionArea>
                                    </Card>
                                </Box>
                            );
                        })}
                    </Box>
                </Paper>
            </Grid>
            <Grid item xs>
            <Paper sx={{ width: '100%', }}>
                    <Box sx={{ mt: 1, mx: 2 }} alignItems="center">
                        <Grid container >
                        <Grid item xs={2} sx={{ mt: 1 }}>
                            <MoveDownIcon sx={{ fontSize: 24, mt: 0.5 }} />
                        </Grid>
                        <Grid item xs sx={{ mt: 1 }}>
                            <Typography variant="h5">
                                Last Transactions
                            </Typography>
                        </Grid>
                        </Grid>
                    </Box>
                    <Box>
                    {filteredTransactions.slice(-3).map((value, idx) => {
                        return (
                            <Box key={idx}>
                            <Divider variant="middle" />
                            <Card>
                            <CardActionArea sx={{ display: 'flex', justifyContent: "space-around"  }}>
                                <CardMedia
                                    component="img"
                                    sx={{ width: 60 }}
                                    image="https://icons-for-free.com/download-icon-money+payment+successful+purchase+successful+transaction+transaction-1320166001861616386_512.png"
                                    alt="credit_card"
                                />
                                <Box sx={{ display: 'flex', flexDirection: 'column' }}>
                                    <CardContent>
                                        <Typography component="div" variant="h6">
                                            {Math.round(value["amount"] * 100) / 100}$
                                        </Typography>
                                        <Typography variant="subtitle2" color="text.secondary" component="div">
                                        From: *{value["from_acc_number"].substring(12,16)}
                                        </Typography>
                                        <Typography variant="subtitle2" color="text.secondary" component="div">
                                        To: *{value["to_acc_number"].substring(12,16)}
                                        </Typography>
                                    </CardContent>
                                </Box>
                                <Box sx={{ display: 'flex', flexDirection: 'column' }}>
                                        <Typography variant="subtitle2" color="text.secondary" component="div">
                                        {value["date"].split(' ')[0]}
                                        </Typography>
                                        <Typography variant="subtitle2" color="text.secondary" component="div">
                                        {value["date"].split(' ')[1]}
                                        </Typography>
                                </Box>
                            </CardActionArea>
                            </Card>
                        </Box>
                        );
                    })}
                    </Box>
                </Paper>
            </Grid>
            <Grid item xs={2}></Grid>
            </Grid>
        </Box> }
    </div>
  );
}

export default MainContent;