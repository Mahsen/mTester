docker import http://downloads.openwrt.org/attitude_adjustment/12.09/x86/generic/openwrt-x86-generic-rootfs.tar.gz openwrt-x86-generic-rootfs
docker images
docker run -i -t openwrt-x86-generic-rootfs /bin/ash
docker ps -a
docker start 2c750d76098f
docker exec -it 2c750d76098f "/bin/ash"

mkdir -p /var/lock
vi /etc/opkg.conf
change https to http
opkg update
 

/etc/init.d/uhttpd start
/etc/init.d/sshd start

docker export 2c750d76098f > App.tar

docker import App.tar mTester
docker run -t -i app /bin/bash
