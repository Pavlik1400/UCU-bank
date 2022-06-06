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
import CloseIcon from '@mui/icons-material/Close';
import { Box } from '@mui/system';
import { Button, IconButton } from '@mui/material';
import { getCredits } from '../../../store/slices/CreditsSlice'
import { closeCredit } from '../../../store/slices/AllOtherAPI';
import { useSelector, useDispatch } from 'react-redux'

import CreateCredit from '../CreateCredit'


const adaptBalance = (balance) => {return Math.round(balance * 100) / 100 + "$"}
const adaptActive = (active) => {
    if (active) return "active"
    return "closed"
}
const adaptAny = (smthg) => {return smthg}


const CreditsContent = () => {
    const dispatch = useDispatch()
    const logined = useSelector((state) => state.auth.logined)
    const sessionToken = useSelector((state) => state.auth.sessionToken)
    const uid = useSelector((state) => state.auth.uid)
    const credits = useSelector((state) => state.credit.credits)

    React.useEffect(() => {
        if (logined) {
            dispatch(getCredits({
                user_id: uid,
                token: sessionToken,
            }))
        }
    }, [dispatch, logined, uid, sessionToken]);

    const openCreateCreditFunc = React.useRef(null)

    const aceptedKeys = {
        "Card": ["card_number", adaptAny], 
        "Current Balance": ["current_balance", adaptBalance],
        "Original Balance": ["original_balance", adaptBalance],
        "Opening date": ["opening_date", adaptAny],
        "Period": ["period", adaptAny],
        "Percent": ["percent", adaptAny],
        "Active": ["active", adaptActive],
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
                                Credits
                            </Typography>
                        </Grid>
                        <Grid item xs={2} sx={{ mt: 1 }}>
                            <Button variant="contained" onClick={() => {
                                    openCreateCreditFunc.current();
                                }}>New Credit</Button>
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
                        <TableCell align="right">Finish credit</TableCell>
                        </TableRow>
                        </TableHead>
                        <TableBody>
                        {credits.map((row, idx) => (
                            <TableRow
                            key={idx}
                            sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                            >
                            {
                                Object.keys(aceptedKeys).map((key, index) => ( 
                                    <TableCell align="right" key={index}>{aceptedKeys[key][1](row[aceptedKeys[key][0]])}</TableCell>
                                ))
                            }
                            <TableCell align="right">
                            {row["active"] && 
                            <IconButton color="primary" aria-label="Close credit" onClick={async () => {
                                const resp = await closeCredit(sessionToken, row["id"])
                                const resp_json = await resp.json()
                                if (resp_json["status"] !== 200) {
                                    alert("Failed to cloase credit")
                                } else {
                                    dispatch(getCredits({
                                        user_id: uid,
                                        token: sessionToken,
                                    }))
                                }
                            }}>
                                <CloseIcon />
                            </IconButton>
                            }
                            </TableCell>
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

            <CreateCredit openCreateCreditFunc={openCreateCreditFunc}></CreateCredit>
        </Box> }
    </div>
  );
}

export default CreditsContent;