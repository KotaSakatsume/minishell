#!/bin/bash

# --- 一般的なテストケース（20個追加） ---
echo -e "\n-------------------一般テスト開始----------------------- "
echo -e "\n[一般テスト1] 基本的なechoコマンド"
echo "echo Hello World" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト2] 環境変数の展開"
echo "echo \$PWD" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト3] 複数の環境変数"
echo "echo \$USER \$HOME \$PATH" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト4] シングルクォート内の環境変数"
echo "echo '\$USER \$HOME'" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト5] ダブルクォート内の環境変数"
echo "echo \"\$USER \$HOME\"" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト6] 入力リダイレクト"
echo "cat < /etc/passwd | head -5" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト7] 出力リダイレクト"
echo "echo test > /tmp/testfile" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト8] 追記リダイレクト"
echo "echo append >> /tmp/testfile" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト9] ヒアドキュメント"
echo "cat << EOF
line1
line2
EOF" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト10] 複数のリダイレクト"
echo "echo input > /tmp/input && cat < /tmp/input" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト11] セミコロン区切り"
echo "echo first; echo second; echo third" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト12] AND演算子"
echo "echo success && echo also success" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト13] OR演算子"
echo "false || echo this should print" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト14] 複雑なパイプライン"
echo "ls -la | grep '^d' | wc -l" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト15] ネストしたクォート"
echo "echo \"'nested quotes'\" and 'more \"nested\" quotes'" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト16] エスケープ文字の処理"
echo "echo \"line1\\nline2\\tline3\"" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト17] 長いコマンドライン"
echo "echo this is a very long command line with many arguments that should test the tokenizer and parser thoroughly" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト18] 特殊文字の混在"
echo "echo 'special chars: !@#$%^&*()_+-=[]{}|;:,.<>?'" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト19] 空のコマンド"
echo "echo ''" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト20] 複雑な構文の組み合わせ"
echo "echo start && (echo middle | grep mid) || echo end" | valgrind --leak-check=full -q ./minishell

echo -e "\n[一般テスト21] リダイレクトのみ"
echo "> test" | valgrind --leak-check=full -q ./minishell

echo -e "\n-------------------一般テスト終了----------------------- "

echo -e "\n=== 総合メモリリーク・デバッグテスト開始 ==="

# --- 基本的なリークテスト ---
echo "\n[基本テスト1] 複数のパイプ文字"
echo "||||||||||||||||||||||||||||||||\\" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト2] 複数のコマンド"
echo "ls | grep test | wc -l" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト3] 複数のリダイレクト"
echo "echo test > file1 > file2 > file3" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト4] 複雑な構文"
echo "echo hello && echo world || echo error" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト5] 長い文字列"
echo "this_is_a_very_long_command_name_with_many_characters" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト6] 特殊文字"
echo "echo \$HOME \$PATH \$USER" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト7] クォート"
echo "echo 'hello world' \"test string\"" | valgrind --leak-check=full -q ./minishell

echo -e "\n[基本テスト8] エスケープ文字"
echo "echo \\n \\t \\r" | valgrind --leak-check=full -q ./minishell

# --- 詳細なリークテスト ---
echo -e "\n[詳細テスト1] 連続したパイプ文字（構文エラー）"
echo "||||||||||||||||||||||||||||||||" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト2] バックスラッシュで継続したパイプ文字"
echo "||||||||||||||||||||||||||||||||\\" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト3] 複数行のパイプ文字"
echo "||||||||||||||||||||||||||||||||\\
> |||||||||||||||||||||||||||||||||" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト4] パイプ文字の後にコマンド"
echo "||||||||||||||||||||||||||||||||\\
> echo test" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト5] 単純なコマンド"
echo "echo hello" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト6] パイプ付きコマンド"
echo "echo hello | grep o" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト7] 複数のパイプ"
echo "echo hello | grep o | wc -l" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト8] 空の入力"
echo "" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト9] スペースのみ"
echo "   " | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト10] バックスラッシュのみ"
echo "\\" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト11] バックスラッシュ + 改行"
echo "\\
" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト12] バックスラッシュ + スペース"
echo "\\ " | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト13] 不完全なリダイレクト"
echo "echo test >" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト14] 不完全なリダイレクト（継続行）"
echo "echo test >\\
> " | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト15] 不完全なクォート"
echo "echo 'unclosed quote" | valgrind --leak-check=full -q ./minishell

echo -e "\n[詳細テスト16] 不完全なクォート（継続行）"
echo "echo 'unclosed quote\\
> " | valgrind --leak-check=full -q ./minishell

# --- デバッグ用トークン出力テスト ---
echo -e "\n[デバッグテスト1] 連続したパイプ文字"
echo "||||||||||||||||||||||||||||||||" | valgrind --leak-check=full -q ./minishell

echo -e "\n[デバッグテスト2] 短いパイプ文字"
echo "|||" | valgrind --leak-check=full -q ./minishell

echo -e "\n[デバッグテスト3] パイプ文字 + コマンド"
echo "||| echo test" | valgrind --leak-check=full -q ./minishell

echo -e "\n[デバッグテスト4] コマンド + パイプ文字"
echo "echo test |||" | valgrind --leak-check=full -q ./minishell

echo -e "\n=== 総合テスト終了 ==