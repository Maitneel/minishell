# minishell
minishell はshellの動作の理解、C言語におけるシステムコールの理解を目的にC言語によって作成された簡易的なshellです。学習目的で作成されたため、他のShellと比べると機能に制限があります

## システム要件
以下のソフトウェアがインストールされている必要があります。
- gcc (gcc以外でのCコンパイラでもコンパイルできると思いますが、未検証です)
- make

また、このプログラムでは以下のライブラリを使用するため、こちらもインストールされている必要があります。
- readline
  - MacOSでは`brew install readline` でインストールできます
  - ubuntuでは`apt install libreadline-dev`でインストールできます。

## ビルド方法
```
git clone git@github.com:ndmxjp/minishell.git
cd ./minishell
make
```

## minishellでできること
- `$PATH`を使用し、コマンドを検索し、そのコマンドの実行する
- 以下のbuild-inコマンドの実行(オプションが使用できない等の制限があります)
  - `echo`
  - `env`
  - `export`
  - `unset`
  - `pwd`
  - `cd`
  - `exit`
- single-quote`'`, double-quote`"`の解釈
- リダイレクト`<`, `>`, `>>`の解釈
- pipe`|`によるコマンド間の標準入出力の接続
- `Ctrl-C`, `Ctrl-D`, `Ctrl-\`のハンドル

## Docker環境
minishellの動作確認用にDocker環境を用意してあります。実行方法は下記の通りです
```
make docker
```





