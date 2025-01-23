#!/bin/sh

curl -X POST \
     -H "Content-type: text/xml;charset=UTF-8" \
     --data-binary @input.qbeta \
     http://localhost:7913/evaluate
