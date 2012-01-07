Arduino Script and Webservice to decide if the time is right for catching the next bus.

Author : Bastian Widmer (bastianwidmer.ch)

Inspired and Adapted from Christian Leu (leumund.ch)

Introduction
============
This script consists of two parts. A PHP-Webservice which gets the
timetable data for the public transport from fahrplan.search.ch and
a Arduino sketch which connects to the service and signals back to the
user if he can catch the next bus or not ;-)

The Webservice makes use of the [PHP Simple HTML DOM Parser](http://simplehtmldom.sourceforge.net/).

Needed Material
===============
* Arduino Board
* Arduino Ethernet Shield
* Red and Green Leds or a Led Matrix (if you want to go fancy)

Licence
=======

  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

