#!/bin/bash

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

valgrind: query
    $(VALGRIND) query