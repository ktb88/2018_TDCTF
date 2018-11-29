FROM       ubuntu:16.04
MAINTAINER delsponn@gmail.com


RUN sed -i "s/http:\/\/archive.ubuntu.com/http:\/\/ftp.daumkakao.com/g" /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y python
RUN apt-get install -y python-pip
RUN apt-get install -y nginx-full
RUN apt-get install -y python-dev
RUN apt-get install -y netcat

RUN apt-get install -y wget
RUN wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add -
RUN echo 'deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main' | tee /etc/apt/sources.list.d/google-chrome.list
RUN apt-get update
#RUN apt-get install -y libnss3-dev
RUN apt-get install -y google-chrome-stable

ADD requirements.txt /tmp/r.txt
RUN pip install -r /tmp/r.txt && rm /tmp/r.txt
RUN ln -s /usr/local/bin/uwsgi /usr/bin/uwsgi

RUN mkdir -p /app
ADD app/ /app/

COPY chromedriver /app
RUN chmod +x /app/chromedriver

ADD uwsgi.ini /tmp
RUN rm /etc/nginx/sites-available/default
ADD nginx.conf /etc/nginx/sites-available/default

RUN rm -rf /var/lib/apt/lists/*
ADD run.sh /run.sh
RUN chmod 755 /*.sh

RUN chmod 555 /app/*

ADD U_g0t_Sh311_Th1S_i5_F1aG /app
RUN chmod 444 /app/U_g0t_Sh311_Th1S_i5_F1aG

EXPOSE 80
CMD ["/run.sh"]
