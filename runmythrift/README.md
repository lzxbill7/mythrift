## README

#### Purpose:
run mythrift in a docker container,without extra deployment

#### Prequiste:
* Docker Installed

[How to install docker](https://docker_practice.gitee.io/install/centos.html)

#### Steps:

build an image of mythrift:
```
tar xzf mythrift-2.1.tar.gz
cd  mythriftImage
docker build -t mythrift:2.0 .  
```

run a container based on above image
```
docker images
docker run -it --name=whatever  <imageID>  bash
```

make && make test
```
ldconfig
mongod -f /etc/mongod.conf
cmake ..  (maybe you have to delete CMakeCache.txt first)
make
make test
```