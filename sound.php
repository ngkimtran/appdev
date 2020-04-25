<?php
$peaks = $_POST['peaks'];
$max = $_POST['max'];
$today = date("Y-m-d H:i:s");
$record = $today.", number of peaks: ".$peaks.", maximum decibel: ".$max."\n";

$file = "sound.log";
if(file_exists($file))
	$fp = fopen($file, "a");
else
	$fp = fopen($file, "w");
fwrite($fp, $record);
fclose($fp);
?>
