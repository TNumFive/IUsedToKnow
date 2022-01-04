
# JS中的const,var和let
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
