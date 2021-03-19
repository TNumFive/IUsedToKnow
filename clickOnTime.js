function clickOnTime(dateStr, querySelector) {
    var deadline = (new Date(dateStr)).getTime();
    var ele = document.querySelector(querySelector);
    window.setTimeout(
        () => {
            while (true) {
                var now = new Date();
                if (now.getTime() > deadline) {
                    ele.click();
                    console.log("点击时间：", now);
                    console.log("时间戳：", now.getTime());
                    console.log("偏差毫秒数：", now.getTime() - deadline);
                    break;
                }
            }
        }
        ,
        deadline - (new Date()).getTime() - 10
    )
    console.log("大约", (deadline - (new Date()).getTime()) / 1000, "秒后执行");
}