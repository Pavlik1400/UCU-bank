rs.initiate();
cfg = rs.conf();
cfg.members[0].host="mongo-db:27017";
rs.reconfig(cfg);