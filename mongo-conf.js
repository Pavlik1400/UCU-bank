
rs.initiate();
c=rs.conf();
c.members[0].host='localhost:27017';
rs.reconfig(c)