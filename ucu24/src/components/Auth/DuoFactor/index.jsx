import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import Alert from '@mui/material/Alert';
import CircularProgress from '@mui/material/CircularProgress';
import Box from '@mui/material/Box';
import { useDispatch, useSelector } from 'react-redux'
import { login2 } from '../../../store/slices/AuthSlice'
import { Container } from '@mui/material';


const DuoFactor = ({ openDuoFactorFunc, closeParent }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const otp_key = useSelector((state) => state.auth.otp_key)
    const error = useSelector((state) => state.auth.error)
    const logined = useSelector((state) => state.auth.logined)

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openDuoFactorFunc.current = handleClickOpen }, [openDuoFactorFunc])

    React.useEffect(() => {
      if (logined) {
        closeParent()
      }
    }, [logined, closeParent]);

    const secretRef = React.useRef('')

    return (
      <Dialog open={open} onClose={handleClose}>
        {otp_key === "" && error === "" &&
        <Box>
          <CircularProgress />
        </Box>}
        {error !== "" && <Alert severity="error">{error}</Alert>}
        {otp_key !== "" && <Container><DialogTitle>Login</DialogTitle>
        <DialogContent>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="DuoFactorCode"
                label="DuoFactor code"
                type="password"
                variant="filled"
                inputRef={secretRef}
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(login2({
                otp_key: otp_key, 
                one_time_passwd: secretRef.current.value
              }));
          }}>Validate Code</Button>
        </DialogActions>
        </Container>}

      </Dialog>
    );
}

export default DuoFactor;