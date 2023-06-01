# Socket Sample

* Socket Sample Program

# 実行ファイル作成

* gcc -socket.c -o socketSample

# TCP ポート番号1234で受けまち

* nc -l 1234

# client プログラム実行

* ./socketSample 127.0.0.1 hello 1234

# ポート1234でメッセージ受信

* > nc -l 1234
* hello

# ポート1234からメッセージ送信

* > nc -l 1234
* hi

# client ポート番号1234からのメッセージ受信

* > ./socket 127.0.0.1 abcabc 1234
* Receive:hi

