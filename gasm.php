<?php
    $lines = file("code.as", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    echo PHP_OS;
    $isWindows = strtoupper(substr(PHP_OS, 0, 3)) === 'WIN';
    $isLinux = strtoupper(substr(PHP_OS, 0, 3)) === 'LINUX';
    $isFreeBSD = strtoupper(substr(PHP_OS, 0, 3)) === 'FreeBSD';
    $isOpenBSD = strtoupper(substr(PHP_OS, 0, 3)) === 'OpenBSD';
    $isNetBSD = strtoupper(substr(PHP_OS, 0, 3)) === 'NetBSD';
    $isMacOS = strtoupper(substr(PHP_OS, 0, 3)) === 'MacOS';

    $variables = [];
    $constants = [];
    $output_code = [];
    $reg_count = 1;

    $output_code[] = "define i32 @main() {";

    if ($lines === false){
        die("Cant open file");
    }

    $data = [];

    foreach ($lines as $line) {
        preg_match_all('/[a-zA-Z0-9_.]+|[():=+\-:]|"[^"]*"|\'[^\']*\'/', $line, $matches);
        $tokens = $matches[0];

        if (empty($tokens)) continue;
        $data[] = $tokens;
    }

    //print_r($data);
    function getOperand($token, &$variables, &$reg_count, &$output_code) {
        if (is_numeric($token)) {
            return $token;
        } else {
            $reg = "%" . ($reg_count++);
            $output_code[] = "  $reg = load i32, ptr %$token";
            return $reg;
        }
    }

    function compileExpression($tokens, &$variables, &$reg_count, &$output_code) {
        $last_reg = getOperand($tokens[0], $variables, $reg_count, $output_code);

        for ($i = 1; $i < count($tokens); $i += 2) {
            $op = $tokens[$i];
            $val = $tokens[$i + 1];

            $next_val = getOperand($val, $variables, $reg_count, $output_code);

            $res_reg = "%" . ($reg_count++);
            if ($op == '+') $output_code[] = "  $res_reg = add i32 $last_reg, $next_val";
            elseif ($op == '-') $output_code[] = "  $res_reg = sub i32 $last_reg, $next_val";

            $last_reg = $res_reg;
        }
        return $last_reg;
    }

    foreach ($data as $tokens){
        if ($tokens[0] == "let") {
            $mutability = $tokens[1];
            $type = $tokens[3];
            $name = $tokens[5];
            $value = $tokens[7];

            $output_code[] = "  %$name = alloca i32";

            $output_code[] = "  store i32 $value, ptr %$name";

            if ($mutability == "umut") {
                $constants[$name] = ['type' => $type, 'value' => $value];
            } elseif ($mutability == "mut") {
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
            $expression = array_slice($tokens, 2);
            $result_reg = compileExpression($expression, $variables, $reg_count, $output_code);
            $output_code[] = "  store i32 $result_reg, ptr %$varName";
        }
    }

    //print_r($variables);
    //print_r($constants);

    $output_code[] = "  ret i32 0";
    $output_code[] = "}";
    file_put_contents("output.ll", implode("\n", $output_code));
?>