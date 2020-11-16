#!/usr/bin/env python3

"""
Lunch script for every computer
"""

import socket

# Global configuration:
DATAVIZ_HOST_A = '192.200.200.57'
DATAVIZ_HOST_B = '192.200.200.58'
DATAVIZ_PORT_LEFT = 31337
DATAVIZ_PORT_RIGHT = 31338
SERVICE_HOST = DATAVIZ_HOST_A
START_SERVICE_ON_DATAVIZ_A = True


# Configuration for this instance only:
KIOSK_MODE = "central"
DATAVIZ_HOST = DATAVIZ_HOST_A # default
DATAVIZ_PORT = DATAVIZ_PORT_LEFT # default
start_kiosk = True
start_service = False


def get_hostname():
    return socket.gethostname()

my_hostname = get_hostname()

# According to the hostname for this computer
# set the different options to use
if my_hostname == 'kiosk-entrance':
    KIOSK_MODE = 'entrance'

elif my_hostname == 'kiosk-exit':
    KIOSK_MODE = 'exit'

elif my_hostname == 'kiosk-central-1':
    KIOSK_MODE = 'central'
    DATAVIZ_HOST = DATAVIZ_HOST_A
    DATAVIZ_PORT = DATAVIZ_PORT_LEFT

elif my_hostname == 'kiosk-central-2':
    KIOSK_MODE = 'central'
    DATAVIZ_HOST = DATAVIZ_HOST_A
    DATAVIZ_PORT = DATAVIZ_PORT_RIGHT

elif my_hostname == 'kiosk-central-3':
    KIOSK_MODE = 'central'
    DATAVIZ_HOST = DATAVIZ_HOST_B
    DATAVIZ_PORT = DATAVIZ_PORT_LEFT

elif my_hostname == 'kiosk-central-4':
    KIOSK_MODE = 'central'
    DATAVIZ_HOST = DATAVIZ_HOST_B
    DATAVIZ_PORT = DATAVIZ_PORT_RIGHT

elif my_hostname == 'dataviz-a':
    start_kiosk = False
    if START_SERVICE_ON_DATAVIZ_A:
        start_service = True

elif my_hostname == 'dataviz-b':
    start_kiosk = False


# Add the commands to Lunch
if start_kiosk: # Kiosk:
    add_command("~/src/mpop/mpop_kiosk/mpop_kiosk --kiosk-mode {kiosk_mode} --service-host {service_host} --dataviz-host {dataviz_host} --dataviz-port {dataviz_port} --fullscreen".format(
        kiosk_mode=KIOSK_MODE,
        service_host=SERVICE_HOST,
        dataviz_host=DATAVIZ_HOST,
        dataviz_port=DATAVIZ_PORT), identifier='kiosk')
else: # Dataviz:
    add_command("~/src/mpop/mpop_dataviz/mpop_dataviz --port 31337 --x-position 1280 --align-right", identifier='dataviz-left')
    add_command("~/src/mpop/mpop_dataviz/mpop_dataviz --port 31338 --x-position 3200", identifier='dataviz-right')

# Service:
if start_service:
    # XXX We run the DB directly on this host, now.
    # add_command("docker-compose --file ~/src/mpop/docker-compose.yml up", identifier='database')
    add_command("~/src/mpop/scripts/sh_start_service_without_docker.sh", identifier='service')

