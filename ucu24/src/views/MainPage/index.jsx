import Grid from '@mui/material/Grid';
import Header from '../../shared_components/Header'
import LeftPanel from '../../shared_components/LeftPanel'
import MainContent from '../../components/MainPage/MainContent'

const MainPageView = () => {
  return (
    <Grid container height="100vh">
      <Grid item>
        <LeftPanel />
      </Grid>
      <Grid item xs>
        <Header />
        <MainContent />
      </Grid>
    </Grid>
  )
}

export default MainPageView