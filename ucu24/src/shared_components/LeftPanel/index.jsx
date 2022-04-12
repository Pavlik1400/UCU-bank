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
import ListItemText from '@mui/material/ListItemText';
import DashboardIcon from '@mui/icons-material/Dashboard';
import ShoppingCartIcon from '@mui/icons-material/ShoppingCart';
import PeopleIcon from '@mui/icons-material/People';
import BarChartIcon from '@mui/icons-material/BarChart';
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
                    <ListItemButton>
                    <ListItemIcon>
                        <DashboardIcon />
                    </ListItemIcon>
                    <ListItemText primary="Account" />
                    </ListItemButton>
                    <ListItemButton>
                    <ListItemIcon>
                        <ShoppingCartIcon />
                    </ListItemIcon>
                    <ListItemText primary="Credits" />
                    </ListItemButton>
                    <ListItemButton>
                    <ListItemIcon>
                        <PeopleIcon />
                    </ListItemIcon>
                    <ListItemText primary="Deposits" />
                    </ListItemButton>
                    <ListItemButton>
                    <ListItemIcon>
                        <BarChartIcon />
                    </ListItemIcon>
                    <ListItemText primary="Transactions" />
                    </ListItemButton>
                </List>
            </Drawer>
    );
}

export default LeftPanel;