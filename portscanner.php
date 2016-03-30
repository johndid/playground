<?php
// Simple TCP connect port scanner in php using fsockopen and only php!
echo "<p>You've been port scanned! <pre>\nand we found: \n";
error_reporting(~E_ALL); // avoid warnings like this PHP Warning:  fsockopen(): unable to connect to 192.168.1.2:83 (Connection refused) in ... blah
$from = 1
$to = 6000;
$host = $client;
$start = time();
$open = 0;
$open_ports = array();
for($port = $from; $port <= $to ; $port++) {
  $fp = fsockopen($host , $port);
  if ($fp) {
    echo "port $port open \n";
    $open_ports[] = $port;
    $open++;
    fclose($fp);
  }	 
}
$stop = time();
$interval = $stop - $start;
$total_ports = $to - $from;
$closed_ports = $port - $open;
echo "\nScanned: (" . $total_ports . ") ports in ("  . $interval . ") Seconds\nOpen ports: (" .$open . ")\nClosed ports: (" . $total_ports . ")\n</pre></p>";
?>