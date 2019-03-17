## README

#### Purpose:
run mythrift in a docker container,without extra deployment

#### Prequiste:
* Docker Installed

[How to install docker](https://docker_practice.gitee.io/install/centos.html)

#### Steps:

build an image of mythrift:

```
docker build -t mythrift:1.0 .
```

run a container based on above image
```
docker images
docker run -it --name=whatever  <imageID>  bash
```

make && make test
```
mongod -f /etc/mongod.conf
# git clone project first
cd /opt/mythrift
make
make test
```
