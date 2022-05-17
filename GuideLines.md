> 尝试通过文档的方式来记录一下自己的编码习惯，并在个人项目中应用；
# 格式化工具及配置方式
- default  
    clang-format，并优先使用.clang-format文件，fallback至设置的样式
    ```js
    {
        BasedOnStyle: LLVM,
        IndentWidth: 4,
        TabWidth: 4,
        AllowShortBlocksOnASingleLine: Always,
        AllowShortCaseLabelsOnASingleLine: true,
        AllowShortIfStatementsOnASingleLine: AllIfsAndElse,
        AllowShortLoopsOnASingleLine: true,
        ColumnLimit: 0
    }
    ```
- Python  
    autopen8，目前尚未固定，尝试过后感觉还可以
- Java  
    预计使用idea进行开发，使用idea默认的格式化工具及样式即可
- Javascript  
    预计使用vscode，使用默认的格式化工具及样式即可
# 命名规则
- 非常见缩略不使用，不依赖“缩写规则”  
- README等特殊文件名采用常用命名
- 文档名若为英文则采用UpperCamelCase
- 代码文件名命名方式与对应语言的类名保持一致  
- C和C++  
    原则上使用小写字母，使用C++风格命名（下划线分割单词；不使用下划线打头，留给编译器及标准库使用；全大写下划线连接用于宏变量）
- Java和JavaScript  
    类使用名词，UpperCamelCase，拼写完整；方法使用动词，lowerCamelCase；本地变量、临时变量使用lowerCamelCase；常量使用大写字母，下划线隔开
- Python  
    类名使用UpperCamelCase；常量使用大写字母，下划线隔开；其它采用小写，下划线隔开
