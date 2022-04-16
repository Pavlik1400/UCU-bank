import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import { useDispatch } from 'react-redux'
import { login } from '../../../store/slices/AuthSlice'
import { Container } from '@mui/material';


const DuoFactor = ({ openDuoFactorFunc, closeParent }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openDuoFactorFunc.current = handleClickOpen }, [])

    return (
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>Login</DialogTitle>
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
            />
            </Container>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(login());
              closeParent();
          }}>Validate Code</Button>
        </DialogActions>

      </Dialog>
    );
}

export default DuoFactor;