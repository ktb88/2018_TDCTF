docker stop xss
docker rm xss
docker build -t xss .
docker run -d --name xss -p 80:80 xss
