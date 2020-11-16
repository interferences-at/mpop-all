#!/bin/bash
#
# Starts the MPOP Service
#

CONFIG_MYSQL_PORT=3306 \
    CONFIG_MYSQL_HOST=localhost \
    CONFIG_MYSQL_USER=root \
    CONFIG_MYSQL_DATABASE=mpop_database \
    CONFIG_MYSQL_PASSWORD=secret \
    ~/src/mpop/mpop_service/mpop_service

