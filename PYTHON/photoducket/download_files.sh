#!/bin/bash

while read url; do
    curl $url -O --referer "https://oi62.photobucket.com/"
done < fixed_links.txt

