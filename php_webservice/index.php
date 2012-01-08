<?php

/* *
 * PHP Webservice for the Arduino Busstop Light
 *
 * Written by Bastian Widmer (bastianwidmer.ch)
 *
 * Just change the $url $walkingtime and $offtime to your needs.
 *
 * */


include('simple_html_dom.php');

$walkingtime = 180;	// Define walking Time to the Bus Stop
$offtime = 300;		// Signal an OFF Event if time is more than 5 minutes
$url ='http://fahrplan.search.ch/bern,aeussere-enge/bern'; // Get the timetable data url from fahrplan.search.ch

$html = file_get_html($url);

// calculate next busstop
foreach($html->find('span.oev_printbold') as $e)	//Get the First DIV with StartData
{
$nextbus = strtotime(substr(trim($e->innertext),0,5));	// Strip unneccesary data and convert to a timestamp

$now = strtotime(date("G:i"));				// Create a timestamp reflecting the current time

$diff = $nextbus - $now;				// calculate the difference for the events


if ($diff < $walkingtime) {
	if ($diff < 0) {continue;}			// if we get a negative value of time (can happen if the server time is not 100% accurate) skip this result and wait for the next bus
  echo "red - " . $diff;
}
  else
{
  if ($diff > $offtime) {
    echo "off - " .$diff;
  }
    else
  {
    echo "green - ".$diff;
  }
}
echo "\n";
exit;
}
