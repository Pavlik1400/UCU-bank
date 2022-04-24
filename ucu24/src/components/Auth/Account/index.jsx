import * as React from 'react';
import Button from '@mui/material/Button';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableRow from '@mui/material/TableRow';
import { useDispatch, useSelector } from 'react-redux'
import { exit, getUserData } from '../../../store/slices/AuthSlice'
import { Paper, Typography } from '@mui/material';
import { Box } from '@mui/system';


const Account = ({ openAccountFunc }) => {
    const dispatch = useDispatch()

    const account_data = useSelector((state) => state.auth.account)
    const logined = useSelector((state) => state.auth.logined)
    const phone_num = useSelector((state) => state.auth.phone_num)

    const [open, setOpen] = React.useState(false);

    const handleClickOpen = () => {
      setOpen(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openAccountFunc.current = handleClickOpen }, [openAccountFunc])

    React.useEffect(() => {
        if (logined) {
            dispatch(getUserData({"phone_num": phone_num}))
        }
    }, [logined, phone_num, dispatch]);

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