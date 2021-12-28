# 从 jdk.java.net 下载指定版本的jdk
```sh
#解压
tar zxvf ${openjdk-filename}
#配置到用户目录下
mv ${jdk-dir} ~/.jvm/ 
```
# 配置环境变量 JAVA_HOME PATH CLASSPATH
```sh
#可以将配置修改在~/.bashrc中，这样只影响当前用户
JAVA_HOME=$HOME/.jvm/${jdk-dir}
PATH=$JAVA_HOME/bin:$PATH
CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
export JAVA_HOME
export PATH
export CLASSPATH
```