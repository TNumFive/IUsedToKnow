>为了实现在不同网络环境下可以不修改配置使用ssh连接虚拟机及虚拟机配置运行在主机上的proxy 
>（适用Ubuntu20.04及VirtualBox）
0. 基本思路
    1. 配置桥接/NAT用于访问外网的同时配置Host-only并固定ip
    2. 将ssh连接配置及proxy配置修改为host-only下ip
1. 为虚拟机添加host-only网卡
2. 启动虚拟机，利用dhcp服务分配ip
3. 取消网卡的dhcp服务，防止后续ip变动
4. gui下使用NetworkManager修改网络设置，cli下修改/etc/netplan目录下配置文件
    >从17.10版本开始，Ubuntu放弃在/etc/network/interfaces里固定IP的配置，改为使用netplan  
    >具体修改方式可以参考这个[链接](https://linuxconfig.org/how-to-configure-static-ip-address-on-ubuntu-18-10-cosmic-cuttlefish-linux)