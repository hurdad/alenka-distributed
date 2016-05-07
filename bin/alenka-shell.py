#!/usr/bin/env python

import logging
logging.basicConfig()

from kazoo.client import KazooClient

zk = KazooClient(hosts='127.0.0.1:2181')
zk.start()
