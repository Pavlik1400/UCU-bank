import * as React from 'react';
import Button from '@mui/material/Button';
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
import { createCredit, getCredits, clearStatus } from '../../../store/slices/CreditsSlice'
import { Container, TextField } from '@mui/material';


const CreateCredit = ({openCreateCreditFunc}) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const uid = useSelector((state) => state.auth.uid)
    const accounts = useSelector((state) => state.account.accounts)
    const sessionToken = useSelector((state) => state.auth.sessionToken)
    const error = useSelector((state) => state.credit.error)
    const status = useSelector((state) => state.credit.status)

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
    React.useEffect(() => { openCreateCreditFunc.current = handleClickOpen }, [openCreateCreditFunc])

    React.useEffect(() => {
      if (status !== "loading" && operationStarted) {
        dispatch(getCredits({
          user_id: uid,
          token: sessionToken
        }))
        handleClose()
        clearSetOperationStarted()
      }
    // eslint-disable-next-line react-hooks/exhaustive-deps
    }, [status, operationStarted]);

    const [creditType, setCreditType] = React.useState(0);
    const handleCreditTypeChange = (event) => {
      setCreditType(event.target.value);
    };

    const [accountNumber, setAccountNumber] = React.useState('');
    const handleAccountNumberChange = (event) => {
      setAccountNumber(event.target.value);
    };

    const amountRef = React.useRef(0)

    return (
      <Dialog open={open} onClose={handleClose}>
        {status === "loading" && error === "" &&
        <Box>
          <CircularProgress />
        </Box>}
        {error !== "" && <Alert severity="error">{error}</Alert>}
        {status !== "loading" && error === "" && <Container><DialogTitle>Create Credit</DialogTitle>
        <DialogContent>
            <Container>
            <FormControl fullWidth sx={{
              mt: "8px",
              mb: "4px",
            }}>
              <InputLabel id="account-number-label">Account</InputLabel>
              <Select
                labelId="account-number-label"
                id="account-number"
                value={accountNumber}
                label="Account"
                onChange={handleAccountNumberChange}
              >
                {accounts.map((account) => <MenuItem key={account["number"]} value={account["number"]}>{account["number"]}</MenuItem>)}
              </Select>
            </FormControl>
            <FormControl fullWidth sx={{
              mt: "8px",
              mb: "4px",
            }}>
              <InputLabel id="credit-type-label">Credit type</InputLabel>
              <Select
                labelId="credit-type-label"
                id="credit-type"
                value={creditType}
                label="Credit Type"
                onChange={handleCreditTypeChange}
              >
                <MenuItem value={0}>3 periods, 7.2%</MenuItem>
                <MenuItem value={1}>6 periods, 5.5%</MenuItem>
                <MenuItem value={2}>12 periods, 3.5%</MenuItem>
              </Select>
            </FormControl>
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
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(createCredit({
                "type": creditType,
                "card_number": accountNumber,
                "amount": parseInt(amountRef.current.value),
                "token": sessionToken
              }));
              handleSetOperationStarted()
          }}>Create Credit</Button>
        </DialogActions>
        </Container>}

      </Dialog>
    );
}

export default CreateCredit;