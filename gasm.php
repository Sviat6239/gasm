<?php
    $file = fopen("code.as", "r") or die("Unable to open file!");
    echo fread($file, filesize("code.as"));
    fclose($file);
?>