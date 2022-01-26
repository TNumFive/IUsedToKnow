# 使用nvm进行安装并管理版本
```sh
wget https://raw.githubusercontent.com/nvm-sh/nvm/master/install.sh | bash
```  
> 无需在root用户下安装，安装路径为${HOME}/.nvm，使用root用户将导致非root用户不可用（默认在用户home目录下安装，而root用户home目录其它用户不可访问）  
> 如果无法拉去到git文件，可以手动打开，拷入虚拟机后再执行，sh执行本身并不会被拦截
# 安装lts版本的nodejs和npm
```sh
nvm install --lts
```