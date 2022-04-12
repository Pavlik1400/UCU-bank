import * as React from 'react';
import Button from '@mui/material/Button';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableRow from '@mui/material/TableRow';
import { useDispatch } from 'react-redux'
import { exit } from '../../../store/slices/AuthSlice'
import { Paper, Typography } from '@mui/material';
import { Box } from '@mui/system';

const account_data = {
    "name": "Yevnen",
    "surname": "Pankevych",
    "phone": "+380123456789",
    "address": "Lviv, Antonovycha 256",
}


const Account = ({ openAccountFunc }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openAccountFunc.current = handleClickOpen }, [])

    return (
      <Dialog open={open} onClose={handleClose}>
        
        <Box>
        <Box sx={{
            backgroundColor: 'primary.main'
        }}>
            <Typography variant="h4">
                Account
            </Typography>
        </Box>

        <Box>
            <TableContainer component={Paper}>
                <Table sx={{ minWidth: 650 }} aria-label="simple table">
                    <TableBody>
                    {
                        Object.keys(account_data).map((key, index) => ( 
                        <TableRow
                            key={index}
                        >
                        <TableCell component="th" scope="row">
                            {key}
                        </TableCell>
                        <TableCell align="left">{account_data[key]}</TableCell>
                        </TableRow>
                        ))
                    }
                    </TableBody>
                </Table>
            </TableContainer>
        </Box>
        </Box>

        <DialogActions>
          <Button onClick={() => {
              dispatch(exit());
              handleClose();
          }}>Exit</Button>
        </DialogActions>
      </Dialog>
    );
}

export default Account;