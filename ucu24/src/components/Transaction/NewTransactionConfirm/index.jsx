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
import { Container } from '@mui/material';
import { useDispatch, useSelector } from 'react-redux'

import { createTransaction } from '../../../store/slices/TransactionSlice'
import { getDataAboutUserFromAccount } from '../../../store/slices/AllOtherAPI'
import './style.css'


const NewTransactionConfirm = ({ openNewTransactionConfirmFunc, closeParent }) => {
    const dispatch = useDispatch()
    const sessionToken = useSelector((state) => state.auth.sessionToken)

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

    const handleClickOpen = async (transaction_data) => {
      setAccountDataGot(false);
      setTransactionData(transaction_data);
      setOpen(true);

      /// Here fetch data
      const response1 = await getDataAboutUserFromAccount(sessionToken, transaction_data["from_acc_number"])
      const response_json1 = await response1.json();
      setAccountDataFirst(response_json1["info"]);

      const response2 = await getDataAboutUserFromAccount(sessionToken, transaction_data["to_acc_number"])
      const response_json2 = await response2.json();
      setAccountDataSecond(response_json2["info"]);
      ///

      setAccountDataGot(true);
    };
  
    const handleClose = () => {
      setOpen(false);
    };

    // eslint-disable-next-line react-hooks/exhaustive-deps
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
              <CardHeader avatar={<Avatar src="/broken-image.jpg" sx={{ marginRight: 0 }} />} className="accountIcon"/>
              <CardContent sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                <Typography gutterBottom variant="h5" component="div">
                  {accountDataFirst["name"]}
                </Typography>
                <Typography variant="body2" color="text.secondary">
                  {accountDataFirst["email"]}
                </Typography>
                <Typography variant="body2" color="text.secondary">
                  {transactionData["from_acc_number"]}
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
                <Typography variant="body2" color="text.secondary">
                  {transactionData["to_acc_number"]}
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