#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/mainframe_g $1&
