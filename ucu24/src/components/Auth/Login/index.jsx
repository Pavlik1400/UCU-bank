import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import { Container } from '@mui/material';

import Register from '../Register'
import DuoFactor from '../DuoFactor'


const Login = ({ openLoginFunc }) => {

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    const openRegisterFunc = React.useRef(null)
    const openDuoFactorFunc = React.useRef(null)

    React.useEffect(() => { openLoginFunc.current = handleClickOpen }, [])

    return (
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>Login</DialogTitle>
        <DialogContent>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="email"
                label="Email Address"
                type="email"
                variant="filled"
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
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
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