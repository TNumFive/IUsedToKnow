
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

# 链路层以太帧结构
- 以太网帧的整体大小为64~1518字节，附加7字节的前同步码，1字节的帧开始界定符，部分系统支持更大的帧，最大为9000字节。
- 以太网帧结构
    |字段|含义|
    |-|-|
    |前同步码|用来使接收端的适配器在接收 MAC 帧时能够迅速调整时钟频率，使它和发送端的频率相同。前同步码为 7 个字节，1 和 0 交替。
    |帧开始定界符|帧的起始符，为 1 个字节。前 6 位 1 和 0 交替，最后的两个连续的 1 表示告诉接收端适配器：“帧信息要来了，准备接收”。
    |目的地址|接收帧的网络适配器的物理地址（MAC 地址），为 6 个字节（48 比特）。作用是当网卡接收到一个数据帧时，首先会检查该帧的目的地址，是否与当前适配器的物理地址相同，如果相同，就会进一步处理；如果不同，则直接丢弃。
    |源地址|发送帧的网络适配器的物理地址（MAC 地址），为 6 个字节（48 比特）。
    |类型|上层协议的类型。由于上层协议众多，所以在处理数据的时候必须设置该字段，标识数据交付哪个协议处理。例如，字段为 0x0800 时，表示将数据交付给 IP 协议。
    |数据|也称为效载荷，表示交付给上层的数据。以太网帧数据长度最小为 46 字节，最大为 1500 字节。如果不足 46 字节时，会填充到最小长度。最大值也叫最大传输单元（MTU）。在 Linux 中，使用 ifconfig 命令可以查看该值，通常为 1500。
    |帧检验序列FCS|检测该帧是否出现差错，占 4 个字节（32 比特）。发送方计算帧的循环冗余码校验（CRC）值，把这个值写到帧里。接收方计算机重新计算 CRC，与 FCS 字段的值进行比较。如果两个值不相同，则表示传输过程中发生了数据丢失或改变。这时，就需要重新传输这一帧。