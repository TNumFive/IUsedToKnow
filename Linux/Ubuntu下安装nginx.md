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
>nginx配置参考 https://segmentfault.com/a/1190000013267839