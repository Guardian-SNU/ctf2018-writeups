process.stdin.resume();
process.stdin.setEncoding("utf8");
console.log("What is the flag?");
process.stdin.on("data", (s) => {
  var f = s.trim();
  if (f.length === 33) {
    if (f.substr(0, 8) === "Guardian") {
      if (f.substr(8, 4) === "CTF{") {
          if (f.substr(12, 9) === "_nuf_3v4h".split("").reverse().join("")) {
            if (f.substr(21, 5) === "W17H_".toLowerCase()) {
              if (f.substr(26, 1) === (typeof null)[2]) {
                if (f.substr(27, 1) === String(1+2+2)) {
                  if (f.substr(28, 5) === 'fuck}') {
                    console.log("YES! That is the correct flag!");
                    process.exit();
                  }
                }
              }
            }
          }
        }
      }
    }
  console.log("wrong flag!");
  process.exit();
})