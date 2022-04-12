import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import { useDispatch } from 'react-redux'
import { register } from '../../../store/slices/AuthSlice'
import { Container } from '@mui/material';


const Register = ({ openRegisterFunc, closeParent }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openRegisterFunc.current = handleClickOpen }, [])

    const emailRef = React.useRef('')
    const passwordRef = React.useRef('')
    const nameRef = React.useRef('')
    const surnameRef = React.useRef('')
    const phoneRef = React.useRef('')
    const addressRef = React.useRef('')

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
                inputRef={emailRef}
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
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="name"
                label="Name"
                type="text"
                variant="filled"
                inputRef={nameRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="surname"
                label="Surname"
                type="text"
                variant="filled"
                inputRef={surnameRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="phone"
                label="Phone"
                type="text"
                variant="filled"
                inputRef={phoneRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="address"
                label="Address"
                type="text"
                variant="filled"
                inputRef={addressRef}
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(register({
                "name": nameRef.current.value,
                "surname": surnameRef.current.value,
                "phone": phoneRef.current.value,
                "address": addressRef.current.value,
                "password": passwordRef.current.value,
                "email": emailRef.current.value,
              }));
              // handleClose();
              closeParent();
          }}>Register</Button>
        </DialogActions>
      </Dialog>
    );
}

export default Register;