target triple = "aarch64-w64-windows-gnu"

declare i32 @printf(i8*, ...)
@.str.d = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str.f = private unnamed_addr constant [4 x i8] c"%f\0A\00"
@.str.s = private unnamed_addr constant [3 x i8] c"%s\00"

@.str.0 = private unnamed_addr constant [12 x i8] c"Hello World\00"
@.str.1 = private unnamed_addr constant [20 x i8] c"Welcome, dear User!\00"

define i32 @main() {
  %number = alloca i32
  store i32 54, i32* %number
  %float_num = alloca double
  store double 5.14, double* %float_num
  %pi = alloca double
  store double 3.14, double* %pi
  %msg = alloca i8*
  store i8* getelementptr ([12 x i8], [12 x i8]* @.str.0, i32 0, i32 0), i8** %msg
  %tmp0 = load i32, i32* %number
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), i32 %tmp0)
  %tmp1 = load float, float* %float_num
  %ext1 = fpext float %tmp1 to double
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.f, i32 0, i32 0), double %ext1)
  %tmp2 = load double, double* %pi
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.f, i32 0, i32 0), double %tmp2)
  %tmp3 = load i8*, i8** %msg
  call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %tmp3)
  %tmp4 = load i32, i32* %number
  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), i32 %tmp4)
  %greet = alloca i8*
  store i8* getelementptr ([20 x i8], [20 x i8]* @.str.1, i32 0, i32 0), i8** %greet
  %tmp5 = load i8*, i8** %greet
  call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %tmp5)
  ret i32 0
}
