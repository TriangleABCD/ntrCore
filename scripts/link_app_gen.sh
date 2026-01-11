#!/usr/bin/env bash
set -e

# 路径常量
USER_OUT_DIR="$(dirname "$0")/../user/out"
OUTPUT="$(dirname "$0")/../src/link_app.S"

# 收集所有 bin 文件，按自然序号排序
mapfile -t bins < <(find "$USER_OUT_DIR" -name '*.bin' | sort -V)

count=${#bins[@]}

# 开始生成
exec > "$OUTPUT"          # 后续 echo 全部写进 $OUTPUT

echo "    .align 3"
echo "    .section .data"
echo "    .global _num_app"
echo "_num_app:"
echo "    .quad $count"
for ((i=0;i<count;i++)); do
  echo "    .quad app_${i}_start"
done
echo "    .quad app_$((count-1))_end"
echo ""

for ((i=0;i<count;i++)); do
  f=${bins[i]}
  f_abs="$(realpath "$f")"
  name=$(basename "$f")
  echo "    .section .data"
  echo "    .global app_${i}_start"
  echo "    .global app_${i}_end"
  echo "app_${i}_start:"
  echo "    .incbin \"$f_abs\""
  echo "app_${i}_end:"
  echo ""
done
