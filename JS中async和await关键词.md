
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