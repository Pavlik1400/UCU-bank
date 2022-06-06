import Grid from '@mui/material/Grid';
import Header from '../../shared_components/Header'
import LeftPanel from '../../shared_components/LeftPanel'
import CreditsContent from '../../components/Credits/CreditsContent'

const CreditView = () => {
  return (
    <Grid container height="100vh">
      <Grid item>
        <LeftPanel />
      </Grid>
      <Grid item xs>
        <Header />
        <CreditsContent />
      </Grid>
    </Grid>
  )
}

export default CreditView