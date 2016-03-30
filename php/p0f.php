<html>
<head>
</head>
<body>
<h1> Us3 b33|\| p0ff3d </h1>
<?php
$temp = array();
$result;
exec("/opt/local/bin/p0f -i en1",$temp,$result);
echo "<pre>\n";
foreach ($temp as $value) {
    echo "$value\n";
}
echo "</pre>";
?>
</body>
</html>