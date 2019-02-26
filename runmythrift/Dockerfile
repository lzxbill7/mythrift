FROM centos:7
RUN buildDeps='epel-release mongodb-org cppunit-devel gcc gcc-c++ automake pkg-config libc6-dev make wget libtool flex bison pkgconfig boost-devel libevent-devel zlib-devel python-devel ruby-devel openssl-devel crypto-utils openssl libevent byacc libquadmath libquadmath-devel cyrus-sasl-devel cmake vim git tig htop' \
&& yum install -y $buildDeps \
&& yum install -y mongo-cxx-driver-devel thrift-devel libconfig-devel mongodb-server \
# /root/install
&& INSTALL=~/install/ \
# log4cplus
&& wget https://sourceforge.net/projects/log4cplus/files/log4cplus-stable/2.0.0/log4cplus-2.0.0-rc2.tar.gz -P $INSTALL \
&& tar xvf $INSTALL/log4cplus-2.0.0-rc2.tar.gz -C $INSTALL \
&& cd $INSTALL/log4cplus-2.0.0-rc2 \
&& ./configure CXXFLAGS="-std=c++0x" \
&& make && make install \
