<?php
    $lines = file("code.as", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    if ($lines === false){
        die("Cant open file");
    }

    $data = [];

    foreach ($lines as $line){
        $tokens = preg_split('/\s+/', trim($line));

        $data[] = $tokens;
    }

    print_r($data);
?>