%stdout = call i64 @GetStdHandle(i32 -11) 
%write_result = call i32 @WriteFile(
    i64 %stdout, 
    i8* getelementptr ([{LEN} x i8], [{LEN} x i8]* {STRING_CONST}, i32 0, i32 0), 
    i32 {LEN}, 
    i32* %tmp_bytes_written, 
    i64 0
)