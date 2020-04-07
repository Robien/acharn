#!/bin/bash
cat $1 | sed "s/\.\.\/Downloads\/blender-2.49b-win64-python26(2)\/.blender\//\.\/tex\//g" | sed "s/\/home\/ecadic\/irrb\//\.\/tex\//g" | sed "s/\.\.\/\.\.\/\.\.\/users\/ecadic\/irrb\/tex\//\.\/tex\//g"
