FROM ubuntu:16.04
MAINTAINER shpik <shpik.korea@gmail.com>

# Environment
ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data

# update && install packages
RUN apt-get update
RUN apt-get install -qq -y apache2 php7.0 libapache2-mod-php7.0

RUN mkdir /var/www/modules
RUN mkdir /var/www/board
COPY ./src/ /var/www/html/
COPY ./board/ /var/www/board/
COPY ./modules/kou.so /var/www/modules/
RUN chown -R $APACHE_RUN_USER:$APACHE_RUN_GROUP /var/www
#RUN chmod -R  /var/www
#RUN chmod -R 777 /var/www/modules
RUN chown -R $APACHE_RUN_USER:$APACHE_RUN_GROUP /var/www/modules
RUN echo 'extension=/var/www/modules/kou.so' >> /etc/php/7.0/apache2/php.ini
COPY ./kou.ini /etc/php/7.0/mods-available/
COPY ./run.sh /run.sh
RUN chmod 777 /run.sh
RUN rm /var/www/html/index.html
# EXPOSE
EXPOSE 10101

# CMD

#CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]
CMD ["/bin/bash"]
