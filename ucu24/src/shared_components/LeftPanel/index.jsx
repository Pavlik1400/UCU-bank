import * as React from 'react';
import { styled } from '@mui/material/styles';
import MuiDrawer from '@mui/material/Drawer';
import Toolbar from '@mui/material/Toolbar';
import List from '@mui/material/List';
import Divider from '@mui/material/Divider';
import IconButton from '@mui/material/IconButton';
import MenuIcon from '@mui/icons-material/Menu';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemIcon from '@mui/material/ListItemIcon';
import AccountBalanceWalletIcon from '@mui/icons-material/AccountBalanceWallet';
import ListItemText from '@mui/material/ListItemText';
import DashboardIcon from '@mui/icons-material/Dashboard';
import {useNavigate} from 'react-router-dom';
import BarChartIcon from '@mui/icons-material/BarChart';
import PaymentIcon from '@mui/icons-material/Payment';
import ChevronLeftIcon from '@mui/icons-material/ChevronLeft';

  
const drawerWidth = 250;

const Drawer = styled(MuiDrawer, { shouldForwardProp: (prop) => prop !== 'open' })(
({ theme, open }) => ({
    '& .MuiDrawer-paper': {
    position: 'relative',
    whiteSpace: 'nowrap',
    width: drawerWidth,
    height: '100vh',
    transition: theme.transitions.create('width', {
        easing: theme.transitions.easing.sharp,
        duration: theme.transitions.duration.enteringScreen,
    }),
    boxSizing: 'border-box',
    ...(!open && {
        overflowX: 'hidden',
        transition: theme.transitions.create('width', {
        easing: theme.transitions.easing.sharp,
        duration: theme.transitions.duration.leavingScreen,
        }),
        width: theme.spacing(7),
        [theme.breakpoints.up('sm')]: {
        width: theme.spacing(9),
        },
    }),
    },
}),
);

const LeftPanel = () => {
    const navigate = useNavigate();
    const navigateTransactions = React.useCallback(() => navigate('/transactions', {replace: true}), [navigate]);
    const navigateHome = React.useCallback(() => navigate('/', {replace: true}), [navigate]);
    const navigateAccounts = React.useCallback(() => navigate('/accounts', {replace: true}), [navigate]);
    const navigateCredits = React.useCallback(() => navigate('/credits', {replace: true}), [navigate]);
  

    const [open, setOpen] = React.useState(true);
    const toggleDrawer = () => {
      setOpen(!open);
    };

    return (
            <Drawer variant="permanent" open={open}>
                <Toolbar
                sx={{
                    display: 'flex',
                    alignItems: 'center',
                    justifyContent: 'flex-start',
                    px: [1],
                }}
                >
                <IconButton onClick={toggleDrawer}>
                    {open && <ChevronLeftIcon />}
                    {!open && <MenuIcon />}
                </IconButton>
                </Toolbar>
                <Divider />
                <List component="nav">
                    <ListItemButton onClick={navigateHome}>
                    <ListItemIcon>
                        <DashboardIcon />
                    </ListItemIcon>
                    <ListItemText primary="Home" />
                    </ListItemButton>
                    <ListItemButton onClick={navigateTransactions}>
                    <ListItemIcon>
                        <BarChartIcon />
                    </ListItemIcon>
                    <ListItemText primary="Transactions" />
                    </ListItemButton>
                    <ListItemButton onClick={navigateAccounts}>
                    <ListItemIcon>
                        <AccountBalanceWalletIcon />
                    </ListItemIcon>
                    <ListItemText primary="Accounts" />
                    </ListItemButton>
                    <ListItemButton onClick={navigateCredits}>
                    <ListItemIcon>
                        <PaymentIcon />
                    </ListItemIcon>
                    <ListItemText primary="Credits" />
                    </ListItemButton>
                </List>
            </Drawer>
    );
}

export default LeftPanel;