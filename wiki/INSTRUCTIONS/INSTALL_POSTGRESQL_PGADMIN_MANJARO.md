## How to install postgres + pgadmin4
1) `yay` - update
2) `yay -S postgresql` - install postgresql - user 'postgres' will be automatically created
3) `sudo passwd postgres` - set password for user postgres (desirably 'postgres')

### Login to the user and try execute psql
1) `su postgres && cd && psql`
2) Verify that $HOME is `/var/lib/postgres`
3) In case you don't have permission to this directory (was in my case): `sudo chown -R postgres:postgres /var/lib/postgres/`

### Install pgadmin4
**DONT INSTALL FROM PACKET MANAGER (WITH yay/pacman)**

Instead create python virtual enviroment with python=3.8
- conda: `conda create --name -y ucubank python=3.8 `