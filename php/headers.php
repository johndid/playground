<html>
<head>
</head>
<body>
<h1>Get client stuff</h1>
<?php

$client = $_SERVER['REMOTE_ADDR'];

echo "<p>Fetch the remote Address <pre>\nHello: " .$client . "\n</pre></p><p>Here's your HTTP header<pre>\n";
foreach (getallheaders() as $name => $value) {
    echo "$name: $value\n";
}
echo "</pre></p>";


$from = 1;
//$to = 6000;
//$to = 81;
$to=500;
$open=0;
$ports = array();
$start = time();
echo "<p>Netcat found these open ports:<pre>\n";
exec("/usr/bin/nc -z -w1 $client $from-$to 2>&1",$services,$ret);
foreach($services as $service){
    echo "$service\n";
    $open++;
    $x = explode(' ', $service);
    $ports[] = "$x[4]";

}
$stop = time();
$interval = $stop - $start;
$closed = $to - $open;
echo "Scanned: (" . $to . ") ports in ("  . $interval . ") Seconds, Open: (" . $open . ") Closed: (" . $closed . ")\n</pre></p>";
echo "</pre></p>";

// get open service banners
// just for fun create a <iframe> object that graps the machines webpage if available!
// and a takes picture of their samba share *gg*, etc!!!!
echo "<p>Attempting to get banner information:";
$index=0;
foreach($ports as $p ) {
    $banner=0;
    exec("echo ' ' | /usr/bin/nc -v -n -w1 $client $p",$banner,$ret);
    $x = explode(' ', $service[$index]);
    echo "<pre>" . $x[2] . ":" . $x[4] ."\n";
    foreach($banner as $line){
        if(!ereg('[<]',$line) && ereg('[:]',$line)) {
           echo "$line\n";
        }
    }
    echo "</pre><hr>";
}
echo "</p>";
?>
</body>
</html>