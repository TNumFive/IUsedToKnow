> 以目前使用的TencentCloud轻量服务器为例
1. 选择Ubuntu lts版本的镜像（相对而言比较熟悉，但非必须）
2. 直接使用lighthouse登入
3. 切换至root用户，安装docker和nginx，可以参考官方手册安装最新版
4. 创建新的docker网络static，后续的所有容器都直接挂载到这个网络上
5. 拉取`mzz2017/v2raya`镜像并启动容器，不需要设置端口映射和目录映射
6. 使用nginx的stream模块，配置端口转发2017到v2raya容器
7. 访问v2raya容器，设置节点订阅，并开启局域网代理分享
8. 取消nginx对v2raya容器的反向代理
9. 拉取ubuntu镜像
10. 参照如下命令配置镜像
```bash
# 使用unminimize命令解除镜像最小化
unminimize
# 更新apt
apt update
# 安装正常运行需要的环境包和语言
apt install dialog apt-utils locale
localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
# 安装openssh
apt install openssh-server
# 配置公钥
mkdir -p ~/.ssh
echo 'ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABgQCeP/TTknmYhljBVcOheq07+HCDdAXDi8/Umfi/r2bnnTFG0j0u7hwa4PGaEZypn+TUv4czOwqmU9L/ppfEjZz165gFlHAJWlIcpBtrOqigcSCde4ihFBod6uIA+wSCOicg1wLFb0g52a1mVEIVo3dz151bjZdbjE3Yn2DoFSIjnSLK58hh3xdUHrnP5cld2h/xAXx48PLrsLZ6l8cwpL/gQJX2/W5eyKQr5Qxrem8DbPtVv+OZj0v0jgtFZdALKJLXIdNbLbZ/m6DI1nKMvlzvSoWDNlQTuV3rI4Ftl3sjq/2VgAgOUrwXh4N1j2mC2jq38taz33mYviAbjuHbIGX4UuM3VG7eBTbyTULt10Ng8hX8m9QZd1JEHfeAFNCfyFQY0mzjr0ANEZEM4UVZGXHWmKLYXzxHWutV2KH6zqgK19uV+7IUTXtCVrYnynPjWljVXT0S2jcojW7whWOD713HcMluay06gll2HAsJJX2BCn6/FhIHVIaXTT6sxOapXC8= fangxw@NITRO5' > ~/.ssh/authorized_keys
# 容器无法使用systemd，需要使用命令来启动sshd服务
/etc/init.d/ssh restart
# 安装开发环境
apt install vim build-essential git
# 配置vim 参考../Misc/vimrc来配置vim
# 参考IDon'tKnow进行git配置
```
11. 设置nginx端口转发host端口到容器22端口，实现ssh远程连接容器，如果端口之前已经使用过了，还需要去known_hosts文件中清理过去的记录