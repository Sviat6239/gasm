define void @sys_print(i8* %str, i32 %len) {
  %stdout = call i64 @GetStdHandle(i32 -11)
  %bytes_written = alloca i32
  call i32 @WriteFile(i64 %stdout, i8* %str, i32 %len, i32* %bytes_written, i64 0)
  ret void
}