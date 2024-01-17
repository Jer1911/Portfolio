#!/bin/bash

while read url; do
    curl $url -O --referer "https://REDACTED.photobucket.com/"
done < fixed_links.txt

