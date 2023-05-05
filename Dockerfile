FROM ubuntu:22.04
WORKDIR /app
COPY . .
RUN apt-get -y update && apt-get install -y
RUN apt-get install build-essential gdb -y

ENV LANG en_US.utf8

CMD ["/bin/bash"]