
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