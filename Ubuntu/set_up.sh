#!/bin/bash
echo 'please use bash instead of sh' &&
# script for scratch
# set time zone to Shanghai
echo 'set time zone Asia/Shanghai' &&
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime &&
echo 'start update and install openssh-server, vim, iproute2' &&
apt update &&
# set apt non-interactive
# export DEBIAN_FRONTEND=noninteractive &&
apt install -y openssh-server vim iproute2 &&
# backup sshd config
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak &&
# set sshd config
echo 'curl sshd config'&&
curl -o /etc/ssh/sshd_config https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Ubuntu/sshd_config &&
# create pubkey dir
mkdir ~/.ssh >
# set pubkey
echo 'ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQCeP/TTknmYhljBVcOheq07+HCDdAXDi8/Umfi/r2bnnTFG0j0u7hwa4PGaEZypn+TUv4czOwqmU9L/ppfEjZz165gFlHAJWlIcpBtrOqigcSCde4ihFBod6uIA+wSCOicg1wLFb0g52a1mVEIVo3dz151bjZdbjE3Yn2DoFSIjnSLK58hh3xdUHrnP5cld2h/xAXx48PLrsLZ6l8cwpL/gQJX2/W5eyKQr5Qxrem8DbPtVv+OZj0v0jgtFZdALKJLXIdNbLbZ/m6DI1nKMvlzvSoWDNlQTuV3rI4Ftl3sjq/2VgAgOUrwXh4N1j2mC2jq38taz33mYviAbjuHbIGX4UuM3VG7eBTbyTULt10Ng8hX8m9QZd1JEHfeAFNCfyFQY0mzjr0ANEZEM4UVZGXHWmKLYXzxHWutV2KH6zqgK19uV+7IUTXtCVrYnynPjWljVXT0S2jcojW7whWOD713HcMluay06gll2HAsJJX2BCn6/FhIHVIaXTT6sxOapXC8= fangxw@NITRO5' > ~/.ssh/authorized_keys &&
# restart sshd
systemctl restart sshd &&
# backup default vimrc
cp /etc/vim/vimrc /etc/vim/vimrc.bak &&
# set vimrc
echo 'curl vimrc' &&
curl -o /etc/vim/vimrc https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Ubuntu/vimrc &&
echo 'done!'