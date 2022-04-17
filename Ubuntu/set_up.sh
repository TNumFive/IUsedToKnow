#!/bin/bash
echo 'use bash instead of sh' &&
# script for scratch
# set time zone to Shanghai
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime &&
if [[ $* == *'replace_sources'* ]]
then 
    # backup apt source.list
    cp /etc/apt/sources.list /etc/apt/sources.list &&
    # replace source.list with tencent version
    curl -o /etc/apt/sources.list https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Ubuntu/sources.list 
fi
# update and install
apt update &&
# set apt non-interactive
# export DEBIAN_FRONTEND=noninteractive &&
apt install -y openssh-server vim iproute2 &&
# backup sshd config
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak &&
# set sshd config
curl -o /etc/ssh/sshd_config https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Ubuntu/sshd_config &&
# backup default vimrc
cp /etc/vim/vimrc /etc/vim/vimrc.bak &&
# set vimrc
curl -o /etc/vim/vimrc https://raw.githubusercontent.com/TNumFive/IUsedToKnow/master/Ubuntu/vimrc &&
echo 'done!'