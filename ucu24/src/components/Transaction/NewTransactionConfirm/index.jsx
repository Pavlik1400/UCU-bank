import * as React from 'react';
import Button from '@mui/material/Button';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogTitle from '@mui/material/DialogTitle';
import CircularProgress from '@mui/material/CircularProgress';
import Card from '@mui/material/Card';
import CardContent from '@mui/material/CardContent';
import CardHeader from '@mui/material/CardHeader';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Avatar from '@mui/material/Avatar';
import Stack from '@mui/material/Stack';
import { useDispatch } from 'react-redux'
import { createTransaction } from '../../../store/slices/TransactionSlice'
import { Container } from '@mui/material';
import './style.css'


const NewTransactionConfirm = ({ openNewTransactionConfirmFunc, closeParent }) => {
    const dispatch = useDispatch()

    const [open, setOpen] = React.useState(false);
    const [accountDataGot, setAccountDataGot] = React.useState(false);
    const [transactionData, setTransactionData] = React.useState({});
    const [accountDataFirst, setAccountDataFirst] = React.useState({
      "email": "",
      "name": "",
      "type": ""
    });
    const [accountDataSecond, setAccountDataSecond] = React.useState({
      "email": "",
      "name": "",
      "type": ""
    });

    const handleClickOpen = (transaction_data) => {
      setAccountDataGot(false);
      setTransactionData(transaction_data);
      setOpen(true);

      /// Here fetch data
      setAccountDataFirst({
        "email": "pasha@gmail.com",
        "name": "pasha",
        "type": "super"
      });

      setAccountDataSecond({
        "email": "yp@gmail.com",
        "name": "yp",
        "type": "super"
      });
      ///

      setAccountDataGot(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    React.useEffect(() => { openNewTransactionConfirmFunc.current = handleClickOpen }, [openNewTransactionConfirmFunc])

    return (
      <Dialog open={open} onClose={handleClose}>
        {!accountDataGot &&
        <Box>
          <CircularProgress />
        </Box>}
        {accountDataGot && <Container><DialogTitle>Comfirm transaction</DialogTitle>
        <DialogContent>
          <Stack direction="row" spacing={2}>
            <Card sx={{ minWidth: 100, display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
              <CardHeader avatar={<Avatar src="/broken-image.jpg" sx={{ marginRight: 0 }} />}/>
              <CardContent sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                <Typography gutterBottom variant="h5" component="div">
                  {accountDataFirst["name"]}
                </Typography>
                <Typography variant="body2" color="text.secondary">
                  {accountDataFirst["email"]}
                </Typography>
              </CardContent>
            </Card>

            <Box sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center', alignSelf: 'center' }}>
              <Typography gutterBottom variant="h5" component="div">
                {transactionData["amount"]}$
              </Typography>
              <Typography variant="body2" color="text.secondary">
                Description: {transactionData["description"]}
              </Typography>
            </Box>

            <Card variant="outlined" sx={{ minWidth: 100, display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
              <CardHeader avatar={<Avatar src="/broken-image.jpg" sx={{ marginRight: 0 }} />}/>
              <CardContent sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                <Typography gutterBottom variant="h5" component="div">
                  {accountDataSecond["name"]}
                </Typography>
                <Typography variant="body2" color="text.secondary">
                  {accountDataSecond["email"]}
                </Typography>
              </CardContent>
            </Card>
          </Stack>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={() => {
              dispatch(createTransaction(transactionData));
              handleClose();
              closeParent();
          }}>Confirm</Button>
        </DialogActions>
        </Container>}

      </Dialog>
    );
}

export default NewTransactionConfirm;