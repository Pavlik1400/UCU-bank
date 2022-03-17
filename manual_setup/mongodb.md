### Enable transactions
```shell
$ mongod --replSet "rs0" --bind_ip localhost
$ mongosh (or mongo if mongosh does not exist)
$ rs.initiate()
$ rs.conf()
```
The last command should give similar output:
```yaml
{
  _id: 'rs0',
  version: 1,
  term: 36,
  members: [
    {
      _id: 0,
      host: '127.0.0.1:27017',
      arbiterOnly: false,
      buildIndexes: true,
      hidden: false,
      priority: 1,
      tags: {},
      secondaryDelaySecs: Long("0"),
      votes: 1
    }
  ],
  protocolVersion: Long("1"),
  writeConcernMajorityJournalDefault: true,
  settings: {
    chainingAllowed: true,
    heartbeatIntervalMillis: 2000,
    heartbeatTimeoutSecs: 10,
    electionTimeoutMillis: 10000,
    catchUpTimeoutMillis: -1,
    catchUpTakeoverDelayMillis: 30000,
    getLastErrorModes: {},
    getLastErrorDefaults: { w: 1, wtimeout: 0 },
    replicaSetId: ObjectId("61e01edb1fe58b0d69833497")
  }
}

```