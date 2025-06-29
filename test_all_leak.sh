#!/bin/bash

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