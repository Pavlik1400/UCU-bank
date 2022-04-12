import Grid from '@mui/material/Grid';
import Header from '../../shared_components/Header'
import LeftPanel from '../../shared_components/LeftPanel'
import AccountContent from '../../components/Accounts/AccountsContent'

const AccountView = () => {
  return (
    <Grid container height="100vh">
      <Grid item>
        <LeftPanel />
      </Grid>
      <Grid item xs>
        <Header />
        <AccountContent />
      </Grid>
    </Grid>
  )
}

export default AccountView