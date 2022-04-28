#! bin/bash

inti_mongo() {
    x=1
    while [[ x -ne 0 ]]; do 
        mongosh -f /my-init/init.js
        x=${?}
        sleep 0.5
    done
}

inti_mongo &
mongosh -f /my-init/init.js
docker-entrypoint.sh "${@}"