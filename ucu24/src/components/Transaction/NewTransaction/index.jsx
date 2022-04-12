import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import { useDispatch } from 'react-redux'
import { addTransaction } from '../../../store/slices/TransactionSlice'
import { makeAccoutTransaction } from '../../../store/slices/AccountSlice'
import { Container } from '@mui/material';

function getCurrentDate(){

    let newDate = new Date()
    let date = newDate.getDate();
    let month = newDate.getMonth() + 1;
    let year = newDate.getFullYear();
    
    return `${date}.${month<10?`0${month}`:`${month}`}.${year}`
}

function getCurrentTime(){

    let newDate = new Date()
    let hours = newDate.getHours();
    let minutes = newDate.getMinutes();
    
    return `${hours}:${minutes}`
}
    

const NewTransaction = ({ openTransactionFunc }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
        setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openTransactionFunc.current = handleClickOpen }, [])

    const fromRef = React.useRef('')
    const toRef = React.useRef('')
    const amountRef = React.useRef(0)

    return (
      <Dialog open={open} onClose={handleClose}>
        <DialogTitle>New transaction</DialogTitle>
        <DialogContent>
            <Container>
            <TextField
                autoFocus
                fullWidth
                margin="dense"
                id="fromAccount"
                label="From"
                type="number"
                variant="filled"
                inputRef={fromRef}
            />
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
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
                dispatch(addTransaction({
                    "from": fromRef.current.value,
                    "to": toRef.current.value,
                    "amount": amountRef.current.value,
                    "date": getCurrentDate(),
                    "time": getCurrentTime(),
                }));
                dispatch(makeAccoutTransaction({
                    "from": fromRef.current.value,
                    "to": toRef.current.value,
                    "amount": amountRef.current.value,
                }));
              handleClose();
          }}>Transfer</Button>
        </DialogActions>
      </Dialog>
    );
}

export default NewTransaction;