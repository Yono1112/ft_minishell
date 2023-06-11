# minishell
## General flow
- bashの大まかな処理の流れは1.input from readline 2. tokenize and parse 3. expand 4. exec commandの4つに分けられる
1. input from readline
	- ユーザーから任意のコマンドを受け取る。
	- 該当章
		- Step1. Readline Loop
		- Step12. Signal
1. tokenize and parse
	- 受け取った文字列をシェルが 1 単位とみなす文字の並び(token)に分割し(tokenize)、各トークンが全体としてどのような命令であるのかを解釈する(parse)。
	- 該当章
		- Step5. Tokenizer
		- Step6. Tokenize Error
		- Step7. Parser（Simple Command）
		- Step8. Parse Error
		- Step9. Redirection
		- Step10. Pipe
	1. tokenize
		- 単語(token)は、単純な文字列("echo"など)スペース(` `)やタブ(`\t`)などの単純な区切り文字や、セミコロンやアンパサンドなどの制御機能を持つトークン(`|| & && ; ;; ( ) | |& <newline>`など)、メタ文字で区切られた文字の連続(`| & ; ( ) < > space tab`)がある。
		- 例えば`echo "$PATH" | grep "bin" > test.txt`だった場合、`echo`,`"$PATH"`,`|`,`grep`,`"bin"`,`>`,`test.txt`に分割する
	1. parse
		- tokenizeで分割された各単語(token)がそれぞれどのように関連しているのかを解釈する
1. expand
	- 環境変数(`$PATH`など)や特殊パラメーター(`$?`など)を任意の文字列に変換する。囲まれているシングルクォーテーション、ダブルクォーテーションもここの処理で削除する
	- 該当章
		- Step11. Expand（Parameter）
1. exec command
	- 設定されているnodeリストの順番でcommandを処理する
	- 該当章
		- Step9. Redirection
		- Step10. Pipe
		- Step12. Signal
		- Step13. Environ/Hashmap
		- Step14. Builtin

## Code flow
1. input from readline
	1. readline中のsignalの動作を設定する(`set_signal()`)
	1. ユーザーから文字列を受け取るまで待機する(`readline()`)
	1. 受け取った文字列がNULLではなければ以降の処理に進む(`interpret()`)
1. tokenize
	1. blankがある場合はblankをスキップする(`skip_blank()`)
	1. operatorである場合はoperatorの種類としてt_tokenリストの最後の要素にt_token_kindをoperatorとして格納する(`add_operator_to_list()`)
	1. wordである場合はt_tokenリストの最後の要素にt_token_kindをwordとして格納する(`add_word_to_list()`)
	1. 入力された文字列の最後まで処理を続ける(文字列がまだある場合は1に戻る)
1. parse
	1. t_node_kindがpipelineのnodeリストを作成する(`pipeline()`)
	1. t_node_kindがcommandのnodeリストを作成する(`simple_command()`)
		1. tokenがwordである場合はcommadリストのargsリスト(これはtokenリスト)にwordを格納する(`add_token_to_node()`)
		1. tokenがredirectである場合はcommandリストにredirectを格納する(`add_operator_to-node()`)
		1. tokenリストの最後までor制御機能を持つトークン(pipeとか)が来るまで処理を続ける
	1. tokenの文字列がpipeである場合はparseの最初の処理に戻る
1. expand
	1. 変数や特殊パラメーターがあれば展開する(`expand_variable()`)
	1. シングルクォーテーション、ダブルクォーテーションがあれば削除する(`remove_quote`)
1. exec command(`exec()`)
	1. redirectがあればファイルをオープンする(`open_redirect_file`)
	1. コマンドが組み込みコマンド(builtin command)のみの場合は親プロセス上でそのコマンドを実行する(`exec_builtin_cmd()`)
	1. builtinではなければ子プロセス上でコマンドを実行する(`exec_cmd`)
		1. pipeがあればpipeを展開する(`prepare_pipe()`)
		1. forkして子プロセスを生成する(`fork()`)
		1. 子プロセスの場合かつbuiltinコマンドであれば、そのプロセス上でコマンドを実行した後にexitする(`exit(exec_builtin_cmd())`)
		1. 子プロセスでbuiltinコマンドでなければ、そのプロセス上でコマンドを実行する(コマンドの実行が成功すればexitする)(`exec_simple_cmd()`)
			1. tokenをargv(charのダブルポインタ型)に変換する(`add_token_to_argv()`)
			1. コマンドが絶対パスでなければパスをコマンドの前に連結する(`check_cmd_path()`)
			1. パスが通ったコマンドがあれば実行、なければ"command not found"を出力する(`execve()`)
	1. 親プロセスはnodeリストの最後まで処理を続ける(pipeがあれば3(`exec_cmd()`)に戻る)
	1. 親プロセスで子プロセスが全てコマンドを実行してexitするまで待機する(`wait_pipeline()`)
	1. コマンドの終了ステータス(コマンドは実行を終了したら終了ステータスを返す)をmainプロセスからreturnする

## Note for each step
- step.1 Readline Loop
	- readline
		- `char *readline(const char str*);`
		- strを出力し、プロンプトを開いて標準入力で文字列を入力します。改行(Enter)を受け取ると、今まで入力された文字列を返します。
		- ubuntu上で`apt install -y libreadline-dev`
	- add_history
		- `int add_history(const char *);`
		- 引数に入れた文字列をhistoryとして保存します。プロンプトが開いている状態でキーボードの方向キー上下で今までプロンプトに入力した文字列を呼び出すことができます。
	- rl_outstream
		- bashのコマンドプロンプトはデフォルトだとstderrに対して出力している(実際に`exec 2>&-`してからbashを開くとプロンプトが表示されなくなる)。minishellでも同じ挙動にするために、readline関数で出力するプロンプト(今回は"minishell$ ")をrl_outstream = stderrでstderrに設定している。rl_outstreamを記述しないと標準出力に設定されている
- step.2 Build and Test
- step.3 Exec Path
	- fork
		- プロセスを複製するコマンド
	- wait
		- `pid_t wait(int *wstatus)`
		- 呼び出し元プロセスの子プロセスの状態変化を待ちます。子プロセスの状態変化がすでに発生していた場合は、wait関数はすぐに復帰します。それ以外の場合は、子プロセスの状態変化が起こるか、シグナルハンドラによりシステムコールが中断されるまで呼び出し元プロセスは停止します。
		- *statusは子プロセスからの終了ステータスを格納する変数を指定します。
		- 返り値は成功すると、終了した子プロセスのプロセスID を返す。 エラーの場合 -1 を返す。 
		- WEXITSATUS
			- 子プロセスの終了ステータスを返す。
	- execve
		- 指定したコマンドを呼び出し元のプロセスで実行するコマンド
- step.4 Exec Filename
	- access
		- `int access(const char *pathname, int mode);`
		- 呼び出し元プロセスがファイル pathname にアクセスできるかどうかをチェックする
		- mode はチェックを行うアクセス権を指定するもので、F_OK はファイルが存在するかどうかのみを,R_OK, W_OK, X_OK は、ファイルが存在して、それぞれ読み込み、書き込み、実行の許可があるか を検査する。
	- PATHについて
		- [環境変数PATHとは？](https://otomosa.com/linux/envpath/)
- step.5 tokenizer
	- tokenizer(lexer)とは
		- テキストをトークン(最小限に分割された単語)に分割すること
	- operator(制御演算子)
		- 制御演算子とはシェルにおいてプログラムの制御フローを制御するために用いられる特別な文字列で、一般的にシェルが特別な意味を持つ文字列を検出すると、それに応じた動作を実行する。
		- || (or)：左側のコマンドが失敗した場合にのみ、右側のコマンドを実行します。
		- & (background)：コマンドをバックグラウンドで実行します。バックグラウンドで実行されたコマンドは、現在のシェルの制御を返します。
		- && (and)：左側のコマンドが成功した場合にのみ、右側のコマンドを実行します。
		- ; (separator)：左側のコマンドを実行し、その後右側のコマンドを実行します。
		- ;; (end of command)：case文で使用され、現在のパターンに一致するコマンドを実行し、case文を終了します。
		- ( と ) (parentheses)：コマンドをサブシェル内で実行します。サブシェルは現在のシェルとは異なる環境で実行されます。
		- | (pipe)：左側のコマンドの出力を、右側のコマンドの入力に渡します。
		- \n (newline)：コマンドラインを終了し、実行可能なコマンドとして解釈します。
	- metacharcter(メタ文字)
		- コマンドやシェルスクリプト内で特別な意味を持つ文字のことで、ワードの区切りや引用符の扱い、リダイレクションの指定などに使われる。
	- メタ文字は文字列の解釈に関わる特別な意味を持つ文字であり、オペレータはシェルコマンドや構文の構成要素となる記号やキーワードであるという違いがある。
- step.6 tokenizer error
- step.7 parser
- step.8 parser error
- step.9 redirection
	- dup2
		- `int dup2(int oldfd, int newfd)`
		- 
	- openのフラグとパーミッション
		- O_CREAT
			- ファイルが存在しない場合は新しく作成します。存在する場合は、他のフラグに従って開きます。
		- O_WRONLY
			- ファイルを書き込み専用モードで開きます。これにより、ファイルへの読み取りアクセスは許可されません。
		- O_TRUNC
			- ファイルを開く際に、そのサイズを0に切り詰めます。これは、新しいデータを書き込む前に、既存のデータを消去するために使用されます。
		- O_APPEND
			- 既存のデータが上書きされず、新しいデータがファイルの末尾に追加されることが保証されます。
		- 0644(パーミッション)
			- 所有者に対して読み書きの権限を、グループおよび他のユーザーに対しては読み取りのみの権限を与えることを意味します。
- step10 pipe
- step11 expand
	- 展開 (expansion) とは変数などの中身をそれが使われてる場所に入れ込むこと。
	- 今回は変数展開(環境変数使用時に必要？)とパラメータ展開の$?を実装する。
	- $は展開したいときにしか使用しない。そのためexportやdeclareなどの変数宣言時には不必要。
	- $?(special parametar)
		- $?は直前のコマンドの終了ステータスを確認できます。
		- 終了ステータスは基本的に0が成功(正常)、それ以外が失敗(異常)になります。
	- heredoc時のexpand
		- delimiter(cat << EOFでいうとEOFがdelimiter)がquoteに囲まれていた場合は、heredoc時に入力されるlineに変数($から始まる変数)が入ったとしても展開されない
		- 逆にdelimiterがquoteに囲まれていなかったら、変数はexpandされる
	- word splitting(単語の分割)
		- TEST="a     b         c"の場合、`echo $TEST`と実行したら`"a b c"`となり、`echo "$TEST"`と実行したら`"a     b        c"`とそのまま出力される。

| 名前 | 展開・置換の意味 |
| --- | ------------- |
| ブレース展開 |  {1..10} を展開すること |
| チルダ展開 |  ~/.bash_profile の ~ を展開すること |
| パラメータ展開 |  $?、$@、$1、${1:-word} 等を展開すること |
| 変数展開 | 上記とほぼ同じだが展開対象が変数名の場合 |
| コマンド置換 |  $(cmd) を置換すること |
| 算術式展開 |  $((var + 1)) を展開すること |
| パス名展開 |  *.txt を展開すること |
| クォート削除 | "test.txt"の"を表示しない |
- step12 signal
	- 今回実装するのはCtrl + CとCtrl + \の2つ、Ctrl + Dは特に何も実装しなくても良い？
	- Ctrl + C
		- SIGINT（割り込みシグナル）を現在のフォアグラウンドプロセスに送信します。通常は、実行中のプロセスを中断するために使用されます。
	- Ctrl + D
		- これは EOF（End-Of-File）を意味します。キーボードからの入力が終了したことをシェルやプログラムに通知します。bashシェル(プロンプト)でCtrl + Dを押すと、シェルは入力が終了したと判断し、ログアウト（シェルの終了）します。ただし、プログラムが標準入力から読み込みを待っている場合(heredocやcatコマンドなど)、そのプログラムは入力の終了を検知します。
	- Ctrl + \
		- SIGQUIT（終了シグナル）を現在のフォアグラウンドプロセスに送信します。デフォルトの挙動としては、プロセスを終了させるだけでなく、コアダンプ（メモリの内容を含むデバッグ情報）を生成します。
	- シグナル受信時の動作 (シグナルアクション) 
		- シグナル受信時の動作 (シグナルアクション) には、次の 3 種類があります。この動作は後述の sigaction() などから変更できます。ただし、SIGKILL と SIGSTOP は標準動作以外にはできません。
		1. 無視
			- シグナルを受信しても何もしません。
			- (設定するには、後述の sigaction() などで sa_handler に SIG_IGN を指定する)
		1. 標準動作
			- シグナル受信すると、シグナル毎に定義された標準動作 (後述の Term, Ign, Core, Stop, Cont) を実行します。
			- (設定するには、後述の sigaction() などで sa_handler に SIG_DFL を指定 (デフォルト) する)
			- 標準動作は、シグナル毎に定義されており、次の 5 種類があります。
				1. Term プロセス終了
				1. Ign 何もしない (sigaction() で設定できる SIG_IGN と同じ)
				1. Core プロセス終了とコアダンプ生成 2 
				1. Stop プロセス一時停止 (TASK_STOPPED 状態に遷移させる)
				1. Cont 一時停止したプロセスの再開 (TASK_STOPPED 状態からの復帰)
			- 1 から 31 番までの標準シグナルは、各々に紐づく標準動作を持ちます。(使用頻度の高いものだけ記述)
		1. シグナルハンドラ
			- シグナル受信すると、ユーザが定義した動作を実行します。
			- (設定するには、後述の sigaction() などで sa_handler へユーザ定義の関数を指定する)
	- _rl_echo_control_chars
		- _rl_echo_control_charsは、readlineライブラリが提供する変数の一つで、受信したシグナルに対応する文字を表示するかどうかを制御します。この変数が非ゼロの場合、ユーザーが表示を希望する限り、対応する文字が表示されます​。

| シグナル名 | シグナル番号 (x86_64) | 標準動作 | 意味 |
| -------- | ------------------- | ------- | --- |
| SIGINT | 2 | Term | キーボードからの割り込み (Ctrl + C) |
| SIGQUIT | 3 | Core | キーボードからの終了 (Ctrl + Q) |
| SIGUSR1 | 10 | Term | ユーザ定義のシグナル (その1) |
| SIGSEGV | 11 | Core | 不正なメモリ参照 |
| SIGUSR2 | 12 | Term | ユーザ定義のシグナル (その2) |
| SIGTSTP | 20 | Stop | 制御端末からの停止 (Ctrl + Z) |

\
- step13 environ
- step14 builtin
	- builtinコマンド(組み込みコマンド)はPATHからファイルを探して実行する外部コマンドとは違って、シェル自身の一部として組み込まれているもので。シェルからコマンドが実行される。そのため新たなプロセスは立ち上げないでコマンドが実行される。
	- builtinコマンドと外部コマンドの2つに別れている理由として、builtinコマンドはシェルの内部状態を変更したり、保持する必要性があるから。外部コマンドは通常子プロセス上で実行されるため、シェルの内部状態を変更しようと思ってもその状態は親プロセスに引き継がれない。例えばcdコマンドを子プロセスで実行してもカレントディレクトリの状態は親プロセスに引き継がれない。なので、builtinコマンドは親プロセス上で実行することでシェルの内部状態を変更することができる。
	- builtinコマンドのみの実行の場合(例えば`exit 42`や`echo 42Tokyo`など)では親プロセスでコマンドが実行される。一方、builtinコマンド以外にもコマンドがある場合(例えば`exit | exit`や`cd | ls`など)ではbuiltinコマンドも子プロセス上で実行される。そのためシェル自身の状態を変更することはない。例えば、exitコマンドを実行してもシェルは終了しない、なぜなら子プロセス上で実行しているので、親プロセスでは引き継がれないから。
	- 今回実装するbuiltinは`echo`,`exit`,`cd`,`pwd`,`export`,`unset`,`env`。
	- exit
		- 引数で与えられる数値の範囲はLONG_MAXまで
		- 引数であたられる数値はマイナスの値も受け付ける。ただし`exit --42`や`exit ++42`など`-`か`+`が2つ以上続く場合はerrorになる。
		- exit関数の終了ステータスは0~255の範囲内でなければならないため、`与えられた数値 % 256`を計算しているっぽい。負の数の場合は`256 - 与えられた引数`で計算しているっぽい

## doc
- minishell
	- [man bash](https://linuxjm.osdn.jp/html/GNU_bash/man1/bash.1.html)
	- [minishellの作り方(usami-sanのminishell解説)](https://usatie.notion.site/minishell-29921d3ea13447ad897349acd5733d5e)
	- [minishellの作り方で出てくるコード例のrepository](https://github.com/usatie/minishell_v2/tree/livecoding)
	- [The Architecture of Open Source Applications (Volume 1) The Bourne-Again Shell](https://aosabook.org/en/v1/bash.html)
	- [シェル実装の課題を完走した by jtanaka-san](https://jun-networks.hatenablog.com/entry/2021/07/02/034002)
	- [bash再実装の課題振り返り](https://nafuka.hatenablog.com/entry/2021/03/29/194200)
	- [Lv4minishell(1/3)](https://note.com/syamashi/n/na31efe927b41?magazine_key=m385b3208115b)
	- [readlineとsignal by 42soul](https://intrepidgeeks.com/tutorial/minishell-readline)
	- [minishellの概要 by 42soul](https://techdebt.tistory.com/33?category=833728)
	- [シェルスクリプトの $ は･･･変数の接頭辞ではなく展開するときの記号(expand解説)](https://qiita.com/ko1nksm/items/1864aa2db8ce7bcf332d)
	- [Bashの$@,$#などの$から始まる特殊な変数について](https://linuxcommand.net/bash-special-parameters/)
	- [Linux シグナルの基本と仕組み (カーネル v5.5 時点) ](https://qiita.com/Kernel_OGSun/items/e96cef5487e25517a576#3-%E3%82%B7%E3%82%B0%E3%83%8A%E3%83%AB%E7%95%AA%E5%8F%B7%E3%81%A8%E3%82%B7%E3%82%B0%E3%83%8A%E3%83%AB%E5%90%8D)
	- [readlineライブラリの関数一覧](https://web.mit.edu/gnu/doc/html/rlman_2.html)
	- [sig_atomic_t](https://programming-place.net/ppp/contents/c/appendix/reference/sig_atomic_t.html)
	- [【C言語】volatileの使いどころについて](https://tubasa-blog.com/about-volatile/)
	- [【C言語】printfで文字の色や背景色を変更する](https://daeudaeu.com/c-printf-color/)
- git
	- [個人開発でGithubのissue,プルリクを活用する方法](https://qiita.com/usayamadausako/items/375bdae07e381745e6eb)
	- [git clone の際に submodule の clone を忘れたときの対処法](https://qiita.com/kentarosasaki/items/3e670567c0512b9d411e)
	- [git reset 解説](https://qiita.com/forest1/items/f7c821565a7a7d64d60f)
	- [DiscordのチャンネルにGitHubの通知を送るには？](https://mekurun.com/tips/discord-github/)
	- [［GitHub］一人開発でもissueベース/セルフプルリクエストを使って開発する](https://qiita.com/braveryk7/items/5208263cd06a8878f0c2)
- vim
	- [Vim + Markdown](https://qiita.com/iwataka/items/5355bdf03d0afd82e7a7)
	- [42 Header Plugin](https://github.com/42Paris/42header)


## Todo, Issue
- exec filenameでstrdupしたのをまだfreeしてない
- ~~ubuntuで動かすとreadlineのヘッダファイルが無いとerrorが出る~~
	- done
		- readlineのリンクを一番後ろにすると解決した。順序があるっぽい。
- 標準ライブラリをlibftにする
- ~~cat fileでsegvする(usashellはしない)~~
	- done.だけど最後の行にプロンプトが表示されてしまう
- ~~echo にスペースだけだとsegvする(usahsellはしない)~~
	- tokenizerでスペースをwordと認識されているのが原因、usashellはwordと認識されてない
	- done!
		- tokenizerのblankとoperator以下のif文を別々に分けていたがelse ifで全ての条件式を一つにしたら解決した。
- ~~redirect outputが複数個の時にファイルが一つしか開かない~~
	- done
		- parserでtokenのポインタが正しく動いていなかったのが原因だった
- reset_redirectを自作する(現状usashellのをコピペしている)
- ~~redirect inputでcat < fileをするも`cat: stdin: Bad file descriptor`と表示され読み込めない~~
	- done
		- create_new_redirect_inのt_node_kindがND_REDIR_OUTになっていたのが原因だった
- ~~pipeを実装したらredirect_inputとredirect_heredocを実行してもfcntlでerrorになってしまう~~
	- done
		- なぜかpushしたら上手くいくようになった。原因不明

