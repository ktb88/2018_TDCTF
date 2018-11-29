#!/bin/bash
mkdir cat-proxy

docker exec cat-proxy_db_1 mysql -uroot -e "ALTER USER 'cat'@'%' IDENTIFIED BY '';"
docker exec cat-proxy_db_1 mysql -ucat -e "USE cat;CREATE TABLE users (id text, pw text, thumb text);"
docker exec cat-proxy_db_1 mysql -ucat -e "USE cat;CREATE TABLE flag (flag text);"
docker exec cat-proxy_db_1 mysql -ucat -e "USE cat;INSERT INTO flag VALUES ('TDCTF{W0W_Do_you_know_SSRF_Shiina_Mashiro_Kawaii}');"
docker exec cat-proxy_db_1 mysql -ucat -e "USE cat;INSERT INTO users VALUES ('admin','dhsmfdmsandjtdmfajrdjdigksk@@','admin.png');"
docker exec php_web "docker-php-ext-install mysqli"
docker stop php_web
docker start php_web

