<?php
    $lines = file("code.as", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    $variables = [];
    $constants = [];
    $output_code = [];

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

            if ($tokens[1] == "umut"){
                $constants[$name] = ['type' => $type, 'value' => $value];
            } elseif ($tokens[1] == "mut"){
                $variables[$name] = ['type' => $type, 'value' => $value];
            }

        } elseif ($tokens[0] == "echo") {
            $startIndex = array_search('(', $tokens);
            $endIndex = array_search(')', $tokens);

            if ($startIndex !== false && $endIndex !== false && $endIndex > $startIndex) {
                $between = array_slice($tokens, $startIndex + 1, $endIndex - $startIndex - 1);

                $output = "";
                foreach ($between as $token) {
                    if (preg_match('/^["\'].*["\']$/', $token)) {
                        $output .= trim($token, "\"'") . " ";
                    } else {
                        if (isset($variables[$token])) {
                            $output .= $variables[$token]['value'] . " ";
                        } elseif (isset($constants[$token])) {
                            $output .= $constants[$token]['value'] . " ";
                        } else {
                            $output .= "[undefined] ";
                        }
                    }
                }
                echo trim($output) . "\n";
            }
        } elseif (isset($variables[$tokens[0]]) && ($tokens[1] ?? '') === '=') {
            $varName = $tokens[0];
            $newValue = $tokens[2];

            $variables[$varName]['value'] = $newValue;
        }
    }

    //print_r($variables);
    //print_r($constants);
?>