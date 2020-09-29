#!/bin/bash
ansible-playbook eks.yml -vv --extra-vars="state=present"

