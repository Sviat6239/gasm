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

    foreach ($data as $tokens){
        if ($tokens[0] == "let"){
            $fullToken = $tokens[1];

            $parts = explode(":", $fullToken);

            if (count($parts) == 3){
                $mutability = $parts[0];
                $name = $parts[1];
                $type = $parts[2];
                $value = $tokens[3];

                echo "$mutability:$name:$type:$value\n";
            }

        } elseif ($tokens[0] == "echo"){
            print_r("echo\n");
        }
    }
?>