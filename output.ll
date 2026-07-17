target triple = "aarch64-w64-windows-gnu"

declare i32 @printf(i8*, ...)
@.str.d = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str.f = private unnamed_addr constant [4 x i8] c"%f\0A\00"
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00"


define i32 @main() {
  %num1 = alloca i32
  store i32 52, i32* %num1
  %num2 = alloca i32
  store i32 25, i32* %num2
  %num3 = alloca i32
  store i32 -12, i32* %num3
  %tmp0 = load i32, i32* %num1
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), i32 %tmp0)
  %tmp1 = load i32, i32* %num1
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), i32 %tmp1)
  %tmp2 = load i32, i32* %num2
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), i32 %tmp2)
  ret i32 0
}
