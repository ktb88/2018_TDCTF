#!/usr/bash

phpenmod kou
service apache2 restart
/usr/sbin/apache2 -D FOREGOUND
