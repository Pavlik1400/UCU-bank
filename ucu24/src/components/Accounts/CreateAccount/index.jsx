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
import { createAccount, getUserAccounts, clearStatus } from '../../../store/slices/AccountSlice'
import { Container } from '@mui/material';


const CreateAccount = ({openCreateAccountFunc}) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const uid = useSelector((state) => state.auth.uid)
    const error = useSelector((state) => state.account.error)
    const status = useSelector((state) => state.account.status)

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
    React.useEffect(() => { openCreateAccountFunc.current = handleClickOpen }, [openCreateAccountFunc])

    React.useEffect(() => {
      if (status !== "loading" && operationStarted) {
        dispatch(getUserAccounts({
          user_id: uid
        }))
        handleClose()
        clearSetOperationStarted()
      }
    // eslint-disable-next-line react-hooks/exhaustive-deps
    }, [status, operationStarted]);

    const [accountType, setAccountType] = React.useState('');
    const handleAccountTypeChange = (event) => {
      setAccountType(event.target.value);
    };

    return (
      <Dialog open={open} onClose={handleClose}>
        {status === "loading" && error === "" &&
        <Box>
          <CircularProgress />
        </Box>}
        {error !== "" && <Alert severity="error">{error}</Alert>}
        {status !== "loading" && error === "" && <Container><DialogTitle>Create Account</DialogTitle>
        <DialogContent>
            <Container>
            <FormControl fullWidth sx={{
              mt: "8px",
              mb: "4px",
            }}>
              <InputLabel id="account-type-label">Account type</InputLabel>
              <Select
                labelId="account-type-label"
                id="account-type"
                value={accountType}
                label="Account Type"
                onChange={handleAccountTypeChange}
              >
                <MenuItem value={"Type1"}>Type 1</MenuItem>
                <MenuItem value={"Type2"}>Type 2</MenuItem>
                <MenuItem value={"Type3"}>Type 3</MenuItem>
              </Select>
            </FormControl>
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(createAccount({
                "user_id": uid,
                "account_type": accountType
              }));
              handleSetOperationStarted()
          }}>Create Account</Button>
        </DialogActions>
        </Container>}

      </Dialog>
    );
}

export default CreateAccount;