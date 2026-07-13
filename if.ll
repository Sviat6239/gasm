; ModuleID = 'if.c'
source_filename = "if.c"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-p:64:64-i32:32-i64:64-i128:128-n32:64-S128-Fn32"
target triple = "aarch64-w64-windows-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 8, ptr %2, align 4
  store i32 11, ptr %3, align 4
  store i32 -8, ptr %4, align 4
  %5 = load i32, ptr %2, align 4
  %6 = load i32, ptr %3, align 4
  %7 = icmp sge i32 %5, %6
  br i1 %7, label %8, label %10

8:                                                ; preds = %0
  %9 = load i32, ptr %2, align 4
  store i32 %9, ptr %1, align 4
  br label %36

10:                                               ; preds = %0
  %11 = load i32, ptr %2, align 4
  %12 = load i32, ptr %3, align 4
  %13 = icmp sle i32 %11, %12
  br i1 %13, label %14, label %16

14:                                               ; preds = %10
  %15 = load i32, ptr %3, align 4
  store i32 %15, ptr %1, align 4
  br label %36

16:                                               ; preds = %10
  %17 = load i32, ptr %2, align 4
  %18 = load i32, ptr %4, align 4
  %19 = icmp sge i32 %17, %18
  br i1 %19, label %20, label %22

20:                                               ; preds = %16
  %21 = load i32, ptr %2, align 4
  store i32 %21, ptr %1, align 4
  br label %36

22:                                               ; preds = %16
  %23 = load i32, ptr %2, align 4
  %24 = load i32, ptr %4, align 4
  %25 = icmp sle i32 %23, %24
  br i1 %25, label %26, label %28

26:                                               ; preds = %22
  %27 = load i32, ptr %4, align 4
  store i32 %27, ptr %1, align 4
  br label %36

28:                                               ; preds = %22
  %29 = load i32, ptr %3, align 4
  %30 = load i32, ptr %4, align 4
  %31 = icmp sge i32 %29, %30
  br i1 %31, label %32, label %34

32:                                               ; preds = %28
  %33 = load i32, ptr %4, align 4
  store i32 %33, ptr %1, align 4
  br label %36

34:                                               ; preds = %28
  %35 = load i32, ptr %3, align 4
  store i32 %35, ptr %1, align 4
  br label %36

36:                                               ; preds = %34, %32, %26, %20, %14, %8
  %37 = load i32, ptr %1, align 4
  ret i32 %37
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="reserved" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+fp-armv8,+neon,+v8a" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 22.1.7 (https://github.com/msys2/MINGW-packages b8f306ad57e0c8f3f15aed0dc809d7e3e8e2eee9)", isOptimized: false, runtimeVersion: 0, emissionKind: NoDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "if.c", directory: "C:/Users/svf12/CLionProjects/gasm")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 2}
!4 = !{i32 8, !"PIC Level", i32 2}
!5 = !{i32 7, !"uwtable", i32 2}
!6 = !{i32 7, !"frame-pointer", i32 3}
!7 = !{!"clang version 22.1.7 (https://github.com/msys2/MINGW-packages b8f306ad57e0c8f3f15aed0dc809d7e3e8e2eee9)"}
