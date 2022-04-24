import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import { Container } from '@mui/material';
import { useDispatch } from 'react-redux'

import Register from '../Register'
import DuoFactor from '../DuoFactor'
import { login1, setPhoneNum } from '../../../store/slices/AuthSlice'


const Login = ({ openLoginFunc }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    const openRegisterFunc = React.useRef(null)
    const openDuoFactorFunc = React.useRef(null)

    const phoneRef = React.useRef('')
    const passwordRef = React.useRef('')

    React.useEffect(() => { openLoginFunc.current = handleClickOpen }, [openLoginFunc])

    return (
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>Login</DialogTitle>
        <DialogContent>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="phone"
                label="Phone"
                type="number"
                variant="filled"
                inputRef={phoneRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="password"
                label="Password"
                type="password"
                variant="filled"
                inputRef={passwordRef}
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(setPhoneNum({
                "phone_num": phoneRef.current.value
              }))
              dispatch(login1({
                phone_num: phoneRef.current.value, 
                hashed_password: passwordRef.current.value
              }));
              openDuoFactorFunc.current();
          }}>Login</Button>
          <Button onClick={() => {
              openRegisterFunc.current();
          }}>Register</Button>
        </DialogActions>

        <Register openRegisterFunc={openRegisterFunc} closeParent={handleClose} />
        <DuoFactor openDuoFactorFunc={openDuoFactorFunc} closeParent={handleClose} />
      </Dialog>
    );
}

export default Login;