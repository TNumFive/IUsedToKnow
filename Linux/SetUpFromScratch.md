> 以目前使用的TencentCloud轻量服务器为例
1. 选择Ubuntu lts版本的镜像（相对而言比较熟悉，但非必须）
2. 关闭多余的登入方式，使用vnc登入默认用户，并配置ssh公钥登入，关闭密码登入
3. 在本地使用ssh连接服务器
4. 切换至root用户，安装docker和nginx
5. 拉取`mzz2017/v2raya`镜像并创建容器
6. 配置nginx端口转发host:80端口到v2raya容器的2017端口
7. 访问服务器公网IP，设置节点订阅，并开启局域网代理，后续通过手动设置环境变量来启用
8. 注释nginx的host:80端口转发
9. 拉取带systemd的[ubuntu dockerfile](../Misc/systemd.dockerfile)，并创建容器，用作实际开发环境
10. 参照[set_up.sh](../Misc/set_up.sh)初始化容器
11. 设置nginx端口转发host端口到容器22端口，实现ssh远程连接容器