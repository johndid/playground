#!/bin/bash

gconftool -s /system/http_proxy/use_http_proxy -t bool true
gconftool -s /system/http_proxy/host -t int 127.0.0.1
gconftool -s /system/http_proxy/port -t int 80
gconftool -s /system/http_proxy/use_same_proxy -t bool true
gconf -s /system/proxy/mode -t string manual