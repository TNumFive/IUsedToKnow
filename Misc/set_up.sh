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
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.`date '+%Y%m%d%H%M%S'` &&
# set sshd config
echo 'curl sshd config'&&
curl -o /etc/ssh/sshd_config https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Misc/sshd_config &&
# create pubkey dir
mkdir ~/.ssh 
# set pubkey
echo 'ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIFHlocs+T7ncEiSQpc/up3A03B46hKD+iLBfmpCT2MDA fangx@Nitro5' > ~/.ssh/authorized_keys &&
# restart sshd
systemctl restart sshd &&
# backup default vimrc
cp /etc/vim/vimrc /etc/vim/vimrc.`date '+%Y%m%d%H%M%S'` &&
# set vimrc
echo 'curl vimrc' &&
curl -o /etc/vim/vimrc https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Misc/vimrc &&
echo 'done!'
