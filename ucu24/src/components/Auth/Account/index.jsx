import * as React from 'react';
import Button from '@mui/material/Button';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import Avatar from '@mui/material/Avatar';
import Card from '@mui/material/Card';
import CardContent from '@mui/material/CardContent';
import CardHeader from '@mui/material/CardHeader';
import { useDispatch, useSelector } from 'react-redux'
import { exit, getUserData } from '../../../store/slices/AuthSlice'
import { Container, Typography } from '@mui/material';
import { Logout } from '../../../store/slices/AllOtherAPI';


const adaptAny = (smthg) => {return smthg}
const adaptDate = (str_date) => {
    if (str_date) return str_date.split("T")[0]
    return str_date
}


const Account = ({ openAccountFunc }) => {
    const dispatch = useDispatch()

    const account_data = useSelector((state) => state.auth.account)
    const logined = useSelector((state) => state.auth.logined)
    const sessionToken = useSelector((state) => state.auth.sessionToken)
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
            dispatch(getUserData({"phone_num": phone_num, token: sessionToken}))
        }
    }, [logined, phone_num, dispatch, sessionToken]);


    const aceptedKeys = {
        "Name": ["name", adaptAny], 
        "Birthday": ["date_of_birth", adaptDate],
        "Email": ["email", adaptAny],
        "Gender": ["gender", adaptAny],
        "Phone": ["phone_num", adaptAny], 
    };

    return (
      <Dialog open={open} onClose={handleClose}>
        <Card sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center', minWidth: '300px' }}>
            <CardHeader avatar={<Avatar src="/broken-image.jpg" sx={{ marginRight: 0 }} />}/>
            <Typography variant="h6">User Profile</Typography>
            <CardContent sx={{ minWidth: '280px' }}>
                {
                    Object.keys(aceptedKeys).map((key, index) => (
                        <Container key={index} sx={{ display: 'flex', alignItems: 'center', justifyContent: "space-between" }}>
                            <Typography variant="body1">
                                {key}
                            </Typography>
                            <Typography variant="body2" color="text.secondary">
                                {aceptedKeys[key][1](account_data[aceptedKeys[key][0]])}
                            </Typography>
                        </Container>
                    ))
                }
            </CardContent>
        </Card>

        <DialogActions>
          <Button onClick={() => {
              dispatch(exit());
              Logout(sessionToken);
              handleClose();
          }}>Exit</Button>
        </DialogActions>
      </Dialog>
    );
}

export default Account;