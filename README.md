# GuardianCTF 2018 problems
## Layouts
In root directory, there's directories which names with each categories. Each directory must have layouts like below.
```
.
├── ...
├── {problemname}/
│   ├── README.md
│   ├── src/
│   ├── binary/
│   └── release/
└── ...
```

### `README.md`
File that explains all the information of problem. Contents need to contain author, difficulty(baby, easy, normal, hard), write up, and hints. If have dependencies, you also have to write here.

### `src/`
Directory that contains source codes which needed to be built. Examples will be C codes or shell script to compile.

### `binary/`
Directory that contains all the files which will given to users at competition.

### `release/`
Directory that contains all the files, scripts, environments which will be loaded to server. If we can just load src and run it, you can skip this directory with description in `README.md`.
