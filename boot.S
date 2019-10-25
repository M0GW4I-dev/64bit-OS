.code 32
/*
Multiboot2 Header
Offset	Type	Field			Note
0		u32		magic			required
4		u32		architecture	required
8		u32		header_length	required
12		u32		checksum		required

#### magic
マジックナンバー。Multibootとは違い、0xE85250D6

#### architecture
ISA(Instruction Set Architecture)の指定みたい。マジックナンバーは、回文(palindrome)ではないので、この時、すでにエンディアンは決まっていて、ここが 0 だと、'i386', '4' だとMIPSを表す

#### header_length
ヘッダーの長さを表す。この部分は、マジックフィールドを含んだヘッダーの長さを表している。
この前のコードは、ラベルを使って大きさを測定してた。gnu-asでもできるかな。

#### checksum
上の 3 つを足した和らしい。ゼロにならないといけない？

次に続くのが、タグというものらしい。

タグは、typeごとに別れていて、そのtypeというのは、この部分の先頭にu16で確保されている。
この前見たやつでは、type=2が指定されていた。
したがって、

```
        +-------------------+
u16     | type = 2          |
u16     | flags             |
u32     | size              |
u32     | header_addr       |
u32     | load_addr         |
u32     | load_end_addr     |
u32     | bss_end_addr      |
        +-------------------+
```

これになる。気になるのは、load_addrとload_end_addr、bss_end_addrで、これは、リンカから指定している。リンカでVMA(うつされる前のアドレス)は、`VIRT_BASE = 0xFFFFFFFF80000000;`で指定されており、これが、LMA(= 0x100000;) にうつされるものと思われる。

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

という出力になる。


# palindrome ... 回文
