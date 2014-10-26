
MICROCHIP 社製 A/D コンバータ MCP3202 を RaspberryPi で動かすプログラムです．
Wiring Pi SPI ライブラリを使用しています．

このプログラムはテストプログラムレベルで，main() で1秒おきに MCP3202 の値を読みます．

RaspberryPi は A/D コンバータがないので，MCP3202 は手軽に繋げられるので利便が良いかもです．

コンパイルするには，Raspberry Pi で単純に以下のようにします．

$ gcc -Wall -Wextra RasPi_MCP3202.c -lwiringPi

実行プログラム(a.out) は root 権限で動かします．これは Wiring Pi SPI ライブラリが /dev/mem を参照するためです．

