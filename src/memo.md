# 今日のtips

### mcmodel

```
-mcmodel=kernel
```

カーネルコードモデルのためにコードを生成する。このモデルは、Linuxカーネルコードのコンパイルに使用される。

カーネルコードモデルってなんだよ...

### サフィックスルール

make内で

```
.c.o:
```

というターゲットを作ると、$< と $@ が対応するようになる。

```
.c.o:
	echo $<
	echo $@
```

とすると、`make sample.o` では、

```
sample.c
sample.o
```

という出力になる。気になるのは、load_addrとload_end_addr、bss_end_addrで、これは、リンカから指定している。リンカでVMA(うつされる前のアドレス)は、`VIRT_BASE = 0xFFFFFFFF80000000;`で指定されており、これが、LMA(= 0x100000;) にうつされると思われる。

