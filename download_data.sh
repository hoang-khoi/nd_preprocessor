#!/bin/bash
mkdir wb1913
cd wb1913

for x in {a..z}
do
    wget "http://www.mso.anu.edu.au/~ralph/OPTED/v003/wb1913_$x.html"
done
