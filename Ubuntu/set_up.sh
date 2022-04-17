# script for scratch
apt update &&
# set apt non-interactive
# export DEBIAN_FRONTEND=noninteractive &&
apt install openssh-server -y &&
apt install vim -y &&
apt install iproute2 -y &&
# set time zone to Shanghai
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime 