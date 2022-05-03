> 以下配置及命令多数基于Ubuntu，其它distribution部分命令可能无法使用  

# 设置ssh公钥登入
- digitalocean基于Ubuntu20.04的[参考教程](https://www.digitalocean.com/community/tutorials/how-to-set-up-ssh-keys-on-ubuntu-20-04)
- 注意事项  
    使用命令生成密钥对时，会在公钥文件末尾附加上生成的`username@hostname`，可以用于识别公钥所属用户，因此建议在客户机上生成密钥对，并重命名私钥为服务端`username@hostname`
    ```bash
    ssh-rsa AAAAB3NzaC1yc2EAAAADAQAB ... AAAT6sxOapXC8= fangxw@NITRO5
    ```

# 修改服务器的时区
> 如果提示不存在指定文件，则可能是因为日期管理的相关组件没有安装；但一般使用systemd的系统都是已经携带这个组件的，可以看systemd是否完整（针对minimal-image），或者直接安装对应的组件如`timedatectl`
```bash
cp /etc/localtime /etc/localtime.bak
cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
```

# 安装nodejs和nvm
### 使用nvm进行安装并管理版本
> install.sh会将nvm安装到用户home目录下的.nvm目录，因而无需切换到root用户进行安装  
> 如果无法获取该目录的文件，可以手动下载到这个文件，然后上传到指定服务器，脚本内容并不会被拦截  
```bash
wget https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
```
### 安装lts版本的nodejs和npm
> 注意nvm安装完成后需要手动设置环境变量，或者直接开启一个新的terminal就行
```bash
nvm install --lts
```

# 安装jdk环境
### 从 jdk.java.net 下载指定版本的jdk
```bash
# 解压
tar zxvf ${JDK_PATH}
# 将解压内容移入用户目录下（此处为参考nvm的管理方式）
mv ${JDK_DIR} ~/.jvm/
```
### 配置环境变量JAVA_HOME、PATH、CLASSPATH
```bash
# 注意是否有.bash_profile或.bashrc
JAVA_HOME=$HOME/.jvm/${jdk-dir}
PATH=$JAVA_HOME/bin:$PATH
CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export JAVA_HOME
export PATH
export CLASSPATH
```

# 安装nginx
> 建议参考官方文档来安装  
> 如果只需要代理特定端口，则建议使用docker来部署  
> 如果用作container的主客机端口映射，则可考虑直接安装在主机上  
- [官方Linux安装文档](https://nginx.org/en/linux_packages.html#Ubuntu)
- 注意事项  
    1. 使用`nginx -t`来检查配置格式是否正确，并可确认配置文件路径
    2. 可以使用`stream`模块来做传输层代理

# 实现虚拟机和主机的相对固定ip
1. 使用bridge并配置固定ip
2. 配置多网卡，使用host-only用于主客机访问，配置nat或者bridge用于访问外部网络
# A start job is running for wait for network to be Configured...
> 在使用ubuntu-server虚拟机，且配置多网卡时发现启动很慢，且在用户登入后仍收到网络相关的提示输出
- 原因在于给连接未配置dhcp服务的网卡设置了dhcp，导致系统一直在等待dhcp回报
- 解决办法为修改对应网卡的等待时间
    ```bash
    # 注意该方法针对使用systemd的系统
    cd /etc/systemd/system/network-online.target.wants/
    # 修改网络配置
    sudo vim systemd-networkd-wait-online.service
    # 在[Service]下添加
    TimeoutStartSec=2sec
    ```

# Ubuntu 20.04 安装中文输入法
> （注）部分应用中无法使用原生的中文输入法，测试时可多试几个应用
1. 在设置中的区域与语言，点击管理已安装的语言
2. 添加中文（简体）
3. 重启系统
4. 再次打开区域与语言，选择输入源，点击汉语，点击中文（智能拼音）
5. 使用win+space切换语言

# 为nginx添加vim高亮
> 注意连接教程中的配置，默认设置高亮只针对nginx的默认配置文件位置
- [参考链接](https://www.vim.org/scripts/script.php?script_id=1886)  
    如果页面移动，可尝试Google nginx.vim