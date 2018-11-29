FROM ubuntu:16.04
MAINTAINER Ethan TB Kim <hackability@naver.com>

# Environment
ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data

# update && install packages
RUN apt-get update
RUN apt-get install -qq -y apache2 php7.0 libapache2-mod-php7.0

COPY ./src/ /var/www/html/
RUN chown -R $APACHE_RUN_USER:$APACHE_RUN_GROUP /var/www
RUN rm /var/www/html/index.html
COPY run.sh /
RUN chmod +x /run.sh
 
# EXPOSE
EXPOSE 10101

# CMD

#CMD ["/usr/sbin/apache2", "-D", "FOREGROUND"]
CMD ["/run.sh"]
