import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import InputLabel from '@mui/material/InputLabel';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Select from '@mui/material/Select';
import { AdapterDateFns } from '@mui/x-date-pickers/AdapterDateFns';
import { LocalizationProvider } from '@mui/x-date-pickers/LocalizationProvider';
import { DesktopDatePicker } from '@mui/x-date-pickers/DesktopDatePicker';
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

    React.useEffect(() => { openRegisterFunc.current = handleClickOpen }, [openRegisterFunc])

    const nameRef = React.useRef('')
    const passwordRef = React.useRef('')
    const phoneRef = React.useRef('')
    const emailRef = React.useRef('')
    const addressRef = React.useRef('')
  
    const [birth, setBirth] = React.useState(new Date('2000-08-18T21:11:54'));
    const handleBirthChange = (newValue) => {
      setBirth(newValue);
    };
    const [gender, setGender] = React.useState('');
    const handleGenderChange = (event) => {
      setGender(event.target.value);
    };

    return (
      <LocalizationProvider dateAdapter={AdapterDateFns}>
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
                inputRef={passwordRef}
            />
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="name"
                label="Name and Surname"
                type="text"
                inputRef={nameRef}
            />
            </Container>
            <Container>
            </Container>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="phone"
                label="Phone"
                type="text"
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
                inputRef={addressRef}
            />
            </Container>
            <Container
            sx={{
              marginTop: "8px",
              marginBottom: "4px",
            }}>
                <DesktopDatePicker
                  label="Birth Date"
                  inputFormat="dd/MM/yyyy"
                  value={birth}
                  onChange={handleBirthChange}
                  renderInput={(params) => <TextField {...params} />}
                />
            </Container>
            <Container>
            <FormControl fullWidth sx={{
              mt: "8px",
              mb: "4px",
            }}>
              <InputLabel id="gender-label">Gender</InputLabel>
              <Select
                labelId="gender-label"
                id="gender"
                value={gender}
                label="Gender"
                onChange={handleGenderChange}
              >
                <MenuItem value={"ucu"}>Student of UCU</MenuItem>
                <MenuItem value={"softserve"}>SoftServe worker</MenuItem>
                <MenuItem value={"global"}>GlobalLogic slave</MenuItem>
              </Select>
            </FormControl>
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(register({
                "type": "1",
                "name": nameRef.current.value,
                "password": passwordRef.current.value,
                "date_of_birth": birth,
                "phoneNo": phoneRef.current.value,
                "email": emailRef.current.value,
                "address": addressRef.current.value,
                "gender": gender
              }));
              closeParent();
          }}>Register</Button>
        </DialogActions>
      </Dialog>
      </LocalizationProvider>
    );
}

export default Register;