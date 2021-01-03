
# async
`async`关键字使得函数返回一个Promise
```js
async function hello(){return "Hello";};//返回非Promise对象时，将使用Promise包裹返回值
async function world(){return new Promise((resolve,reject)=>{resolve("World")})};//返回对象为Promise时不做处理
```
# await
`await`关键字使得async函数返回值从Promise变成PromiseResult
```js
async function hello() {
    console.log(new Promise((resolve, reject) => {
        resolve("world");
    }));
    console.log(await new Promise((resolve, reject) => {
        resolve("world");
    }));
}
```

# 匿名函数
函数会直接执行
`(()=>{})();`

# Web APIs SubtleCrypto
```js
/**
 * 
 * @param {String} message 明文
 * @param {String} key 密码
 * @param {CryptoKey} cryptoKey 
 * @returns {Promise} 返回一个Promise，,PromiseResult为加密后的生成的Array
 */
async function encrypt(message, key, cryptoKey) {
    let iv = Uint8Array.from(key, (e) => { return e.charCodeAt(); });
    return await window.crypto.subtle.encrypt(
        {
            name: "AES-GCM",
            iv: iv
        },
        cryptoKey,
        new TextEncoder().encode(message)
    ).then(e=>{
        return new Uint8Array(e);
    });
}

/**
 * 
 * @param {Uint8Array} cipherText 密文
 * @param {String} key 密钥
 * @param {CryptoKey} cryptoKey 
 * @returns {Promise} 返回一个Promise,PromiseResult为解密后的字符串
 */
async function decrypt(cipherText, key, cryptoKey) {
    let iv = Uint8Array.from(key, (e) => { return e.charCodeAt(); });
    return await window.crypto.subtle.decrypt(
        {
            name: "AES-GCM",
            iv: iv
        },
        cryptoKey,
        cipherText
    ).then(e=>{
        return new TextDecoder().decode(e);
    })
}

(()=>{
    let key="123";
    let cryptoKey = window.crypto.subtle.generateKey(
        {
            name: "AES-GCM",
            length: 256,
        },
        true,
        ["encrypt", "decrypt"]
    );
    cryptoKey.then(async (e)=>{
        const e_1 = await encrypt("Hello world!", key, e);
        console.log(e_1);
        const e_2 = await decrypt(e_1, key, e);
        console.log(e_2);
    });
})();
```

# JavaScript中的const、var和let
- 使用var声明的变量，其作用域为该语句所在的函数内，且存在变量提升现象；
    > 变量提升：  
    > 通常JS引擎会在正式执行之前先进行一次预编译，在这个过程中，首先将变量声明及函数声明提升至当前作用域的顶端，然后进行接下来的处理
- 使用let声明的变量，其作用域为该语句所在的代码块内，不存在变量提升；
    ```js
    function varTest() {
    var x = 1;
    if (true) {
        var x = 2;  // 同样的变量!
        console.log(x);  // 2
    }
    console.log(x);  // 2
    }

    function letTest() {
    let x = 1;
    if (true) {
        let x = 2;  // 不同的变量
        console.log(x);  // 2
    }
    console.log(x);  // 1
    }
    ```
- 使用const声明的是常量，在后面出现的代码中不能再修改该常量的值。
    ```js
    const a=1;
    a=2;//报错：Uncaught TypeError: Assignment to constant variable.
    const b={'a':1};
    b.a=2;//正常
    ```

# [Marked] 在页面上渲染Markdown
[Marked]:https://github.com/markedjs/marked
demo.html
```html
<!doctype html>
<html>
<head>
  <meta charset="utf-8"/>
  <title>Marked in the browser</title>
</head>
<body>
  <div id="content"></div>
  <script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>
  <script>
    document.getElementById('content').innerHTML =
      marked('# Marked in the browser\n\nRendered by **marked**.');
  </script>
</body>
</html>
```

# AJAX
> AJAX is Asynchronous JavaScript and XML, which is used on the client side as a group of interrelated web development techniques, in order to create asynchronous web applications.

```JavaScript
//初始化一个XMLHttpRequest  
const xhr = new XMLHttpRequest(),
    method = "GET",
    url = "https://developer.mozilla.org/";;
//打开请求
xhr.open(method, url, true);
//设置回调函数
xhr.onreadystatechange = function () {
  // In local files, status is 0 upon success in Mozilla Firefox
  if(xhr.readyState === XMLHttpRequest.DONE) {
    var status = xhr.status;
    if (status === 0 || (status >= 200 && status < 400)) {
      // The request has been completed successfully
      console.log(xhr.responseText);
    } else {
      // Oh no! There has been an error with the request!
    }
  }
};
//发送请求
xhr.send();
```
# [JSON]

[JSON]:https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON
[JSON.parse]:https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/parse
[JSON.stringify]:https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/JSON/stringify

> JSON or JavaScript Object Notation is a lightweight text-based open standard designed for human-readable data interchange
- JSON is a syntax for serializing objects, arrays, numbers, strings, booleans, and null.
- 不支持undefined、函数声明function(){}、symbol类型、0开头的数字、NaN、Infinity、BigInt……
- JSON结构的例子
    ```json
    {
        "browsers": {
            "firefox": {
                "name": "Firefox",
                "pref_url": "about:config",
                "releases": {
                    "1": {
                        "release_date": "2004-11-09",
                        "status": "retired",
                        "engine": "Gecko",
                        "engine_version": "1.7"
                    }
                }
            }
        }
    }
    ```
- 静态方法[JSON.parse]
    If a reviver is specified, the value computed by parsing is transformed before being
    >If the reviver only transforms some values and not others, be certain to return all untransformed values as-is, otherwise, they will be deleted from the resulting object.
    ```js
    //JSON.parse(text[, reviver]);
    JSON.parse('{"p": 5,"q":"3"}', (key, value) => {
        if (typeof value === Number) {
            value = value * 2;
        } else if (typeof value === String) {
            value = key + value;
        } else {
            /**
             * 只对需要处理的情况做修改，不做修改的value要直接返回，否则会导致格式错误
             * 因为函数传入的参数采用递归的形式，由内向外
             * 先传入{"p": 5}，然后传入{"q":"3"}，然后传入{(null):{"p": 5,"q":"3"}}
            */
        }
        return value;
    });
    ```
- 静态方法[JSON.stringify]
    - `JSON.stringify(value[, replacer[, space]])`
    - replacer可以是一个函数
    ```js
    //
    ```
    - replacer可以是一个数组

# c++17和gnu++17的区别
- -std=c++11 支持C++11标准
- -std=gnu++11 支持C++11标准和GNU扩展特性

# markdown中调整表格列宽
```markdown
|<div style="width:[指定宽度]">[文字内容]</div>|
|-|
|测试|
```

# 链路层以太帧结构
- 以太网帧的整体大小为64~1518字节，附加7字节的前同步码，1字节的帧开始界定符，部分系统支持更大的帧，最大为9000字节。
- 以太网帧结构  
    |<div style="width:90px">字段</div>|<div style="width:68px">长度(字节)</div>|含义|
    |:-:|:-:|-|
    |前同步码|7|用来使接收端的适配器在接收 MAC 帧时能够迅速调整时钟频率，使它和发送端的频率相同。前同步码为 7 个字节，1 和 0 交替。
    |帧开始定界符|1|帧的起始符，为 1 个字节。前 6 位 1 和 0 交替，最后的两个连续的 1 表示告诉接收端适配器：“帧信息要来了，准备接收”。
    |目的地址|6|接收帧的网络适配器的物理地址（MAC 地址），为 6 个字节（48 比特）。作用是当网卡接收到一个数据帧时，首先会检查该帧的目的地址，是否与当前适配器的物理地址相同，如果相同，就会进一步处理；如果不同，则直接丢弃。
    |源地址|6|发送帧的网络适配器的物理地址（MAC 地址），为 6 个字节（48 比特）。
    |类型|2|上层协议的类型。由于上层协议众多，所以在处理数据的时候必须设置该字段，标识数据交付哪个协议处理。例如，字段为 0x0800 时，表示将数据交付给 IP 协议。
    |数据|46|也称为效载荷，表示交付给上层的数据。以太网帧数据长度最小为 46 字节，最大为 1500 字节。如果不足 46 字节时，会填充到最小长度。最大值也叫最大传输单元（MTU）。在 Linux 中，使用 ifconfig 命令可以查看该值，通常为 1500。
    |帧检验序列 FCS|4|检测该帧是否出现差错，占 4 个字节（32 比特）。发送方计算帧的循环冗余码校验（CRC）值，把这个值写到帧里。接收方计算机重新计算 CRC，与 FCS 字段的值进行比较。如果两个值不相同，则表示传输过程中发生了数据丢失或改变。这时，就需要重新传输这一帧。

# 使用sock_raw捕获以太帧时存在长度为54字节或者60字节的帧
- 以太帧的数据长度最小为46字节，若小于46字节，则填充至46字节
- 填充至46字节的操作由设备驱动程序完成
- 帧捕获时会去除4字节的FCS，因而存在60字节的帧
- [数据长度不足时填充的0并不被视为IP报文的一部分，IP报头中不会记录这个长度，而获取数据帧长度时需要依赖于IP报文中对于数据报长度的描述，使得实际上捕获到的数据长度小于46字节](https://stackoverflow.com/questions/5543326/what-is-the-total-length-of-pure-tcp-ack-sent-over-ethernet)
    >Found Answer: The minimum length of the data field of a packet sent over an Ethernet is 46 octets. If necessary, the data field should be padded (with octets of zero) to meet the Ethernet minimum frame size. This padding is not part of the IP packet and is not included in the total length field of the IP header. http://www.ietf.org/rfc/rfc0894.txt  
- *有线网络的帧和无限网络的帧遵循的协议不同，格式也有所不同*

# 当前以太帧中IP报文的数据长度
- MTU最大传输单元包含IP报头的长度和当前帧中IP报文的数据长度
- ihl表示报头长度，tot_len表示报文数据长度
- 同一个IP报文的报头长度一定
- 片偏移以8个字节为单位，每个分片的长度一定是8字节的整数倍
    分片长度=floor((MTU-ihl)/8)*8
- MF=1表示后面还有分片，DF=1表示禁止分片
```C
if(MF==0||DF==1){//后面没有分片或者不允许分片
    dataLen=tot_len-floor(tot_len/分片长度)*分片长度
}else{//后面还有分片
    dataLen=分片长度
}
```

# C语言中的 __attribute__
__attribute__可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute），[看看这个](https://www.jianshu.com/p/dda61084f9b5)

# 使用struct结构体时需要考虑对齐的问题
```c
struct EthIPHeader{
    unsigned char dst_mac[6];
    unsigned char src_mac[6];
    __be16 eth_type;
    unsigned char ver_ihl;
    unsigned char tos;   //服务类型
    unsigned short tot_len; //总长度
    unsigned short id;    //标志
    unsigned short frag_off; //分片偏移
    unsigned char ttl;   //生存时间
    unsigned char protocol; //协议
    unsigned short chk_sum; //检验和
    unsigned char sa[4];//源IP地址
    //struct in_addr src_addr; //由于字节对齐的问题导致此处无法正确取到地址，需使用char代替
    unsigned char da[4];//目的IP地址
    //struct in_addr dst_addr;
};
union{
    unsigned char sa[4];//源IP地址
    struct in_addr src_addr; //使用union也无法解决对齐问题
};
```

# C/C++语言下printf函数
- \r需要配合\n实现\n的功能，简而言之就是，没用。。。。
- 需要使用类似Unicode形式的控制字符
- printf遇到'\0'时输出为空
    ```C
    printf("|\n");
    printf("|\0|\n");
    printf("|\n");
    printf("-");
    printf("\0");
    printf("-\n");
    printf("|\n");
    /*
    |
    ||
    --
    |
    */
    ```

# C语言运算符优先级
>值得注意的是在有位运算参与时，位运算的优先级较低需使用"("，")"提升优先级  
0x5200 - 0x45 & 0x0f * 0x4 = 0x38 = 56(d)  
0x5200 - (0x45 & 0x0f) * 0x4 = 0x51ec = 20972(d)

运算符等级从高到低
|类别|运算符|结合性
|-|-|-|
|后缀|() [] -> . ++ -- |从左到右 
|一元|+ - ! ~ ++ - - (type)* & sizeof|从右到左 
|乘除|* / %|从左到右 
|加减|+ -|从左到右 
|移位|<< >>|从左到右 
|关系|< <= > >=|从左到右 
|相等|== !=|从左到右 
|位与 AND|&|从左到右 
|位异或 XOR|^|从左到右 
|位或 OR|\||从左到右 
|逻辑与 AND|&&|从左到右 
|逻辑或 OR|\|\||从左到右 
|条件|?:|从右到左 
|赋值|= += -= *= /= %= >>= <<= &= ^= \|=|从右到左 
|逗号|,|从左到右 

# C/C++默认参数
- C语言不支持默认参数，通过宏定义来实现
- C++支持默认参数，但是，默认参数只能出现在声明或者定义，不能两边都出现，会编译报错

# linux [capabilities]
[capabilities]:(https://man7.org/linux/man-pages/man7/capabilities.7.html)
[sparkdev's blog]:(https://www.cnblogs.com/sparkdev/p/11417781.html)
    
    For the purpose of performing permission checks, traditional UNIX implementations distinguish two categories of processes: privileged processes (whose effective user ID is 0, referred to as superuser or root), and unprivileged processes (whose effective UID is nonzero).  Privileged processes bypass all kernel permission checks, while unprivileged processes are subject to full permission checking based on the process's credentials (usually: effective UID, effective GID, and supplementary group list).  

    Starting with kernel 2.2, Linux divides the privileges traditionally associated with superuser into distinct units, known as capabilities, which can be independently enabled and disabled.  Capabilities are a per-thread attribute.

    分解root用户的权限为各个小单元，可以给某一个必须使用root用户执行的可执行文件添加权限，使其获得部分root用户的权限，防止部分应用权限过大。

- CAP_NET_ADMIN  
    Perform various network-related operations:
    * interface configuration;
    * administration of IP firewall, masquerading, and
    accounting;
    * modify routing tables;
    * bind to any address for transparent proxying;
    * set type-of-service (TOS);
    * clear driver statistics;
    * set promiscuous mode;
    * enabling multicasting;
    * use setsockopt(2) to set the following socket options:
    SO_DEBUG, SO_MARK, SO_PRIORITY (for a priority outside
    the range 0 to 6), SO_RCVBUFFORCE, and SO_SNDBUFFORCE.
- CAP_NET_RAW
    * Use RAW and PACKET sockets;
    * bind to any address for transparent proxying.
- ...

- setcap和getcap（[sparkdev's blog]）
    ```sh
        sudo setcap cap_net_admin,cap_net_raw+ep /bin/ping #设置权限
        getcap /bin/ping # 查看权限
        sudo setcap cap_net_admin,cap_net_raw-ep /bin/ping #去除权限
    ```
    - “+”代表添加，“-”代表去除
    - 对于程序文件 e：Effective，p：Permitted，i:Inheritable
    - 对于进程 e：Effective，p：Permitted，i:Inheritable，b：Bounding，a：Ambient