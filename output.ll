declare i32 @printf(i8*, ...)
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%number = alloca i32
store i32 54, i32* %number
%float_num = alloca float
store float 5.14, float* %float_num
%pi = alloca double
store double 3.14, double* %pi
%msg = alloca i64
store i64 Hello World, i64* %msg
%tmp = load i32, i32* %number
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %tmp)
%tmp = load float, float* %float_num
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), float %tmp)
%tmp = load double, double* %pi
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), double %tmp)
%tmp = load i8*, i8** %msg
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* %tmp)
%tmp = load i32, i32* %number
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %tmp)
  ret i32 0
}
