import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import InputLabel from '@mui/material/InputLabel';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Select from '@mui/material/Select';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import Alert from '@mui/material/Alert';
import CircularProgress from '@mui/material/CircularProgress';
import Box from '@mui/material/Box';
import { useDispatch, useSelector } from 'react-redux'
import { getTransactions, clearStatus } from '../../../store/slices/TransactionSlice'
import { Container } from '@mui/material';
import NewTransactionConfirm from '../NewTransactionConfirm';
    

const NewTransaction = ({ openTransactionFunc }) => {
    const dispatch = useDispatch()
    const uid = useSelector((state) => state.auth.uid)
    const sessionToken = useSelector((state) => state.auth.sessionToken)
    const accounts = useSelector((state) => state.account.accounts)
    const error = useSelector((state) => state.transaction.error)
    const status = useSelector((state) => state.transaction.status)

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
        dispatch(clearStatus())
        clearSetOperationStarted()
        setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    const [operationStarted, setOperationStarted] = React.useState(false);
    const handleSetOperationStarted = () => {
      setOperationStarted(true);
    };
    const clearSetOperationStarted = () => {
      setOperationStarted(false);
    };

    // eslint-disable-next-line react-hooks/exhaustive-deps
    React.useEffect(() => { openTransactionFunc.current = handleClickOpen }, [openTransactionFunc])

    const toRef = React.useRef('')
    const amountRef = React.useRef(0)
    const descriptionRef = React.useRef('')

    React.useEffect(() => {
        if (status !== "loading" && error === "" && operationStarted) {
        dispatch(getTransactions({
            account_numbers: accounts.map((account) => account["number"]),
            limit: 100,
            token: sessionToken,
        }))
        handleClose()
        clearSetOperationStarted()
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
    }, [status, operationStarted]);

    const [fromAccount, setFromAccount] = React.useState('');
    const handleFromAccountChange = (event) => {
        setFromAccount(event.target.value);
    };

    const openNewTransactionConfirmFunc = React.useRef(null)

    return (
      <Dialog open={open} onClose={handleClose}>
        {status === "loading" && error === "" &&
        <Box>
          <CircularProgress />
        </Box>}
        {error !== "" && <Alert severity="error">{error}</Alert>}
        {status !== "loading" && error === "" && <Container><DialogTitle>New transaction</DialogTitle>
        <DialogContent>
            <Container>
            <FormControl fullWidth sx={{
              mt: "8px",
              mb: "4px",
            }}>
              <InputLabel id="account-from-label">From</InputLabel>
              <Select
                labelId="account-from-label"
                id="account-from"
                value={fromAccount}
                label="From"
                onChange={handleFromAccountChange}
              >
                {accounts.map((account) => <MenuItem key={account["number"]} value={account["number"]}>{account["number"]}</MenuItem>)}
              </Select>
            </FormControl>
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="toAccount"
                label="To"
                type="number"
                variant="filled"
                inputRef={toRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="amount"
                label="Amount"
                type="number"
                variant="filled"
                inputRef={amountRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="description"
                label="Description"
                type="text"
                variant="filled"
                inputRef={descriptionRef}
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              openNewTransactionConfirmFunc.current({
                "user_id": uid,
                "from_acc_number": fromAccount,
                "to_acc_number": toRef.current.value,
                "description": descriptionRef.current.value,
                "amount": parseInt(amountRef.current.value),
                "category": 9,
                "token": sessionToken
              });
          }}>Transfer</Button>
        </DialogActions>
        <NewTransactionConfirm openNewTransactionConfirmFunc={openNewTransactionConfirmFunc} closeParent={handleSetOperationStarted} />
        </Container>}
      </Dialog>
    );
}

export default NewTransaction;