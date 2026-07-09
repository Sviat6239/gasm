define i32 @main() {
  %number = alloca i32
  store i32 54, ptr %number
  %float_num = alloca i32
  store i32 5.14, ptr %float_num
  %pi = alloca i32
  store i32 3.14, ptr %pi
  %msg = alloca i32
  store i32 "Hello World", ptr %msg
  %1 = load i32, ptr %number
  %2 = add i32 %1, 11
  store i32 %2, ptr %number
  ret i32 0
}