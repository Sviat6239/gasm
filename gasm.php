<?php
    $lines = file("code.as", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    if ($lines === false){
        die("Cant open file");
    }

    $data = [];

foreach ($lines as $line) {
    preg_match_all('/[a-zA-Z0-9_.]+|[():=:]/', $line, $matches);
    $tokens = $matches[0];

    if (empty($tokens)) continue;
    $data[] = $tokens;
}

    print_r($data);

    foreach ($data as $tokens){
        if ($tokens[0] == "let"){
            $fullToken = $tokens[1];

            $mutability = $tokens[1];
            $name = $tokens[5];
            $type = $tokens[3];
            $value = $tokens[7];

            echo "$mutability:$name:$type:$value\n";


        } elseif ($tokens[0] == "echo"){
            $startIndex = array_search('(', $tokens);
            $endIndex = array_search(')', $tokens);

            if ($startIndex !== false && $endIndex !== false && $endIndex > $startIndex){
                $between = array_slice($tokens, $startIndex + 1, $endIndex - $startIndex - 1);

                echo implode(' ', $between) . "\n";
            }
        }
    }
?>