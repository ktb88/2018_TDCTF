# Information
- Name : im\_blind\_not\_deaf
- Environment : 
	- any os
	- phpmyadmin 4.8.x < 4.8.2
	- mysql 5.7
	- php 7.2


# Setting

You just input command 'docker-compose up', and input below commnads.

```
docker exec -it im_blind_not_deaf_db_1 mysql -uroot -p
@1@2@3@4qwerasdf
use tdf;
CREATE TABLE tdf (id varchar(10) not null primary key,pw varchar(20) not null);
INSERT INTO tdf VALUES('root','70801f6a');
quit

docker exec -it php_web /bin/bash
echo "TDCTF{F_cong_L_gra_A_tu_G_ration}" > /flag
/usr/local/bin/docker-php-ext-install mysqli
exit
docker exec php_web "/usr/local/bin/docker-php-ext-install mysqli"
docker stop php_web
docker start php_web
```

host change database configure in phpmyadmin and src/config.php. (check your docker name)


finally, enjoy hacking :)

