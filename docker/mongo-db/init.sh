#! bin/bash

sleep 3 && mongosh -f /my-init/init.js && cat /my-init/init.js &
mongosh -f /my-init/init.js
docker-entrypoint.sh "${@}"