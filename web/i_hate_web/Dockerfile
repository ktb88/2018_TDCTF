FROM ubuntu:16.04
MAINTAINER Sehun Oh <shpik.korea@gmail.com>

# Environment
#ENV APACHE_RUN_USER www-data
#ENV APACHE_RUN_GROUP www-data
ENV NODE_ENV=production
ENV PATH=/bin:/sbin:/usr/bin/:/usr/sbin
WORKDIR /srv/

# update && install packages
RUN apt-get update
RUN apt-get install curl -y
RUN curl -sL https://deb.nodesource.com/setup_7.x | bash -
RUN apt-get update
RUN apt-get install nodejs -y
RUN apt-get install nginx -y
# COPY
COPY ./app/* /srv/

# EXPOSE
EXPOSE 37777

# CMD
CMD ["/usr/bin/nodejs","app.js"]
