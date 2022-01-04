# 匿名函数
函数会直接执行
`(()=>{})();`


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