#!/bin/bash

FILENAME=${MYSQL_DATABASE}-$(date +%Y-%m-%d_%Hh%Mm%S).sql

set -o verbose

mysqldump \
  --host=${MYSQL_HOST} \
  --user=${MYSQL_USER} \
  --password=${MYSQL_PASSWORD} \
  --lock-tables=false \
  ${MYSQL_DATABASE} > /backups/${FILENAME}

