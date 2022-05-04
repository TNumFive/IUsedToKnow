# Web APIs SubtleCrypto
```js
/**
 * 
 * @param {String} message 明文
 * @param {String} key 密码
 * @param {CryptoKey} cryptoKey 
 * @returns {Promise} 返回一个Promise，PromiseResult为加密后的生成的Array
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