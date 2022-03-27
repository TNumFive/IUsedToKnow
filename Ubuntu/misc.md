# [digitocean tutorial for set up ssh keys on ubuntu 20.04](https://www.digitalocean.com/community/tutorials/how-to-set-up-ssh-keys-on-ubuntu-20-04)

# 修改服务器时区
```sh
cp /etc/localtime /etc/localtime.bak
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
```
# 安装nodejs和nvm
### 使用nvm进行安装并管理版本
```sh
wget https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
```  
> 无需在root用户下安装，安装路径为${HOME}/.nvm，使用root用户将导致非root用户不可用（默认在用户home目录下安装，而root用户home目录其它用户不可访问）  
> 如果无法拉取到git文件，可以手动下载，拷入虚拟机后再执行，sh执行本身并不会被拦截
### 安装lts版本的nodejs和npm
```sh
nvm install --lts
```

# 安装JDK环境
### 从 jdk.java.net 下载指定版本的jdk
```sh
#解压
tar zxvf ${openjdk-filename}
#配置到用户目录下
mv ${jdk-dir} ~/.jvm/ 
```
### 配置环境变量 JAVA_HOME PATH CLASSPATH
```sh
#可以将配置修改在~/.bashrc中，这样只影响当前用户
JAVA_HOME=$HOME/.jvm/${jdk-dir}
PATH=$JAVA_HOME/bin:$PATH
CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export JAVA_HOME
export PATH
export CLASSPATH
```

# Ubuntu下安装[nginx]
[nginx]:https://nginx.org/en/linux_packages.html#Ubuntu
```sh
sudo apt install curl gnupg2 ca-certificates lsb-release

echo "deb http://nginx.org/packages/ubuntu `lsb_release -cs` nginx" | sudo tee /etc/apt/sources.list.d/nginx.list

echo -e "Package: *\nPin: origin nginx.org\nPin: release o=nginx\nPin-Priority: 900\n" | sudo tee /etc/apt/preferences.d/99nginx

curl -o /tmp/nginx_signing.key https://nginx.org/keys/nginx_signing.key

gpg --dry-run --quiet --import --import-options show-only /tmp/nginx_signing.key

sudo mv /tmp/nginx_signing.key /etc/apt/trusted.gpg.d/nginx_signing.asc

sudo apt update

# 提示 N: Skipping acquire of configured file 'nginx/binary-i386/Packages' as repository 'http://nginx.org/packages/ubuntu focal InRelease' doesn't support architecture 'i386'
# sudo vim /etc/apt/sources.list.d/nginx.list
# 添加正确的架构
# - deb http://nginx.org/packages/ubuntu focal nginx
# + deb [arch=amd64] http://nginx.org/packages/ubuntu focal nginx

sudo apt install nginx
```

# [Ubuntu18.10配置静态ip地址](https://linuxconfig.org/how-to-configure-static-ip-address-on-ubuntu-18-10-cosmic-cuttlefish-linux)
> 虚拟机除去配置静态ip，也可以通过使用host-only网络来实现稳定的主机访问
> 注意从17.10版本开始，Ubuntu放弃在/etc/network/interfaces里固定IP的配置，改为使用netplan

# A start job is running for wait for network to be Configured...
### reason
给一个无法获得网络配置的网卡配置了dhcp，导致系统一直在等待dhcp回报
### solution
```sh
cd /etc/systemd/system/network-online.target.wants/
sudo vim systemd-networkd-wait-online.service
# 在[Service]下添加
TimeoutStartSec=2sec
```