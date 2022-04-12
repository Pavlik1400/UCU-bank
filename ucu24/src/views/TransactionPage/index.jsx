import Grid from '@mui/material/Grid';
import Header from '../../shared_components/Header'
import LeftPanel from '../../shared_components/LeftPanel'
import Transaction from '../../components/Transaction/TransactionContent'

const TransactionView = () => {
  return (
    <Grid container height="100vh">
      <Grid item>
        <LeftPanel />
      </Grid>
      <Grid item xs>
        <Header />
        <Transaction />
      </Grid>
    </Grid>
  )
}

export default TransactionView