<html>
<head>
</head>
<body>
<?php
$temp = array();
$result;
exec("/opt/local/bin/fortune",$temp,$result);
echo "<pre>\n";
foreach ($temp as $value) {
    echo "$value\n";
}
echo "</pre>";
?>
</body>
</html>